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

#include "sql/engine/aggregate/ob_groupby_op.h"
#include "sql/engine/ob_physical_plan.h"
#include "sql/engine/ob_exec_context.h"
//#include "sql/engine/expr/ob_sql_expression.h"
//#include "sql/ob_sql_utils.h"

namespace oceanbase {
namespace sql {

using namespace oceanbase::common;
using namespace oceanbase::share::schema;

OB_SERIALIZE_MEMBER((ObGroupBySpec, ObOpSpec), aggr_infos_);

DEF_TO_STRING(ObGroupBySpec)
{
  int64_t pos = 0;
  J_OBJ_START();
  J_NAME("op_spec");
  J_COLON();
  pos += ObOpSpec::to_string(buf + pos, buf_len - pos);
  J_COMMA();
  J_KV(K_(aggr_infos));
  J_OBJ_END();
  return pos;
}

int ObGroupByOp::inner_open()
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(ObOperator::inner_open())) {
    LOG_WARN("failed to inner_open", K(ret));
  } else if (OB_FAIL(aggr_processor_.init())) {
    LOG_WARN("failed to init", K(ret));
  } else {
    LOG_DEBUG("finish inner_open");
  }
  return ret;
}

int ObGroupByOp::rescan()
{
  int ret = OB_SUCCESS;
  aggr_processor_.reuse();
  if (OB_FAIL(ObOperator::rescan())) {
    LOG_WARN("failed to rescan", K(ret));
  } else if (OB_FAIL(aggr_processor_.init())) {
    LOG_WARN("failed to init", K(ret));
  } else {
    LOG_DEBUG("finish rescan");
  }
  return ret;
}

int ObGroupByOp::switch_iterator()
{
  int ret = OB_SUCCESS;
  aggr_processor_.reuse();
  if (OB_FAIL(ObOperator::switch_iterator())) {
    LOG_WARN("failed to switch_iterator", K(ret));
  } else if (OB_FAIL(aggr_processor_.init())) {
    LOG_WARN("failed to init", K(ret));
  } else {
    LOG_DEBUG("finish switch_iterator");
  }
  return ret;
}

int ObGroupByOp::inner_close()
{
  int ret = OB_SUCCESS;
  aggr_processor_.reuse();
  if (OB_FAIL(ObOperator::inner_close())) {
    LOG_WARN("failed to inner_close", K(ret));
  } else {
    LOG_DEBUG("finish inner_close");
  }
  return ret;
}

void ObGroupByOp::destroy()
{
  aggr_processor_.~ObAggregateProcessor();
  ObOperator::destroy();
}

}  // end namespace sql
}  // end namespace oceanbase
