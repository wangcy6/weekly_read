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

#ifndef OB_VAR_EXPR_H
#define OB_VAR_EXPR_H

#include <stdint.h>
#include "common/object/ob_object.h"
#include "sql/resolver/expr/ob_expr.h"

namespace oceanbase {
namespace jit {
namespace expr {

// OceanBase constant expression.
class ObVarExpr : virtual public ObExpr {
public:
  ObVarExpr()
  {
    set_expr_class(EXPR_VAR);
  }
  virtual ~ObVarExpr()
  {}
};

}  // namespace expr
}  // namespace jit
}  // namespace oceanbase

#endif /* OB_VAR_EXPR_H */
