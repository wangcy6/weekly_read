/**
 * Copyright (c) 2021 OceanBase
 * OceanBase CE is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan PubL v2.
 * You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PubL v2 for more details.
 */

#define USING_LOG_PREFIX SQL_ENG

#include "lib/ob_name_def.h"
#include "sql/engine/expr/ob_expr_to_multi_byte.h"
#include "sql/session/ob_sql_session_info.h"
#include "sql/engine/expr/ob_expr_result_type_util.h"

namespace oceanbase {
using namespace common;
using namespace share;
namespace sql {

ObExprToMultiByte::ObExprToMultiByte(ObIAllocator& alloc)
    : ObFuncExprOperator(alloc, T_FUN_SYS_TO_MULTI_BYTE, N_TO_MULTI_BYTE, 1, NOT_ROW_DIMENSION)
{}
ObExprToMultiByte::~ObExprToMultiByte()
{}

int ObExprToMultiByte::calc_result_type1(ObExprResType& type, ObExprResType& type1, ObExprTypeCtx& type_ctx) const
{
  int ret = OB_SUCCESS;
  ObLength length = 0;
  ObArray<ObExprResType*> params;
  CK(OB_NOT_NULL(type_ctx.get_session()));
  OZ(params.push_back(&type1));
  OZ(aggregate_string_type_and_charset_oracle(*type_ctx.get_session(), params, type, true));
  if (OB_SUCC(ret) && type1.is_clob()) {
    type.set_varchar();
    type.set_length_semantics(LS_BYTE);
  }
  CK(LS_CHAR == type.get_length_semantics() || LS_BYTE == type.get_length_semantics());
  OZ(ObExprResultTypeUtil::deduce_max_string_length_oracle(
      *type_ctx.get_session(), type1, type.get_length_semantics(), length));
  if (OB_SUCC(ret)) {
    if (type1.is_clob()) {
      type.set_length(length);
    } else if (LS_BYTE == type.get_length_semantics()) {
      type.set_length(length * 4);
    } else if (LS_CHAR == type.get_length_semantics()) {
      type.set_length(length);
    }
  }
  OZ(deduce_string_param_calc_type_and_charset(*type_ctx.get_session(), type, params));
  return ret;
}

int ObExprToMultiByte::calc_result1(ObObj& result, const ObObj& obj, ObExprCtx& expr_ctx) const
{
  int ret = OB_SUCCESS;
  ObString src_string;
  ObString dst_string;
  ObCollationType src_collation = obj.get_collation_type();
  int64_t min_char_width = 0;

  if (obj.is_null_oracle()) {
    result.set_null();
  } else {
    CK(OB_NOT_NULL(expr_ctx.calc_buf_));
    OZ(obj.get_string(src_string));
    char* buff = NULL;
    int64_t buff_len = src_string.length() * 4;
    if (OB_SUCC(ret)) {
      if (OB_ISNULL(buff = static_cast<char*>(expr_ctx.calc_buf_->alloc(buff_len)))) {
        ret = OB_ALLOCATE_MEMORY_FAILED;
        LOG_WARN("fail to allocate buffer", K(ret), K(buff_len));
      } else {
        dst_string.assign_buffer(buff, buff_len);
      }
    }
    OZ(ObCharset::get_mbminlen_by_coll(src_collation, min_char_width));

    if (min_char_width > 1) {
      OX(dst_string.write(src_string.ptr(), src_string.length()));
      OX(result.set_nvarchar2(dst_string));
    } else {
      const char* src_ptr = src_string.ptr();
      int64_t src_pos = 0;
      char* dst_ptr = buff;
      int64_t dst_pos = 0;

      int32_t length = 0;
      int32_t wc = 0;
      while (OB_SUCC(ret) && src_pos < src_string.length()) {
        OZ(ObCharset::mb_wc(src_collation, src_ptr + src_pos, src_string.length() - src_pos, length, wc));
        OX(src_pos += length);
        int32_t wc_before_process = wc;
        if (wc == 0x20) {
          wc = 0x3000;
          // smart quote not support https://gerry.lamost.org/blog/?p=295757
          //} else if (wc == 0x22) { //" --> " smart double quote
          //  wc = 0x201D;
          //} else if (wc == 0x27) { //' --> ' smart single quote
          //  wc = 0x2019;
        } else if (wc >= 0x21 && wc <= 0x7E) {
          wc += 65248;
        } else {
          // do nothing
        }
        LOG_DEBUG("process char", K(ret), K(src_pos), K(wc_before_process), K(wc));
        OZ(ObCharset::wc_mb(src_collation, wc, dst_ptr + dst_pos, buff_len - dst_pos, length));
        OX(dst_pos += length);
      }
      OX(dst_string.assign_ptr(dst_ptr, dst_pos));
      OX(result.set_varchar(dst_string));
    }
    OX(result.set_collation(result_type_));
  }
  return ret;
}

}  // namespace sql
}  // namespace oceanbase
