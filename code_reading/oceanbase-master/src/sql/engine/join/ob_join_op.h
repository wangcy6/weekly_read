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

#ifndef OCEANBASE_SQL_ENGINE_JOIN_OB_JOIN_OP_
#define OCEANBASE_SQL_ENGINE_JOIN_OB_JOIN_OP_

#include "sql/engine/ob_operator.h"

namespace oceanbase {
namespace sql {
class ObJoinSpec : public ObOpSpec {
  OB_UNIS_VERSION_V(1);

public:
  ObJoinSpec(common::ObIAllocator& alloc, const ObPhyOperatorType type)
      : ObOpSpec(alloc, type), join_type_(UNKNOWN_JOIN), other_join_conds_(alloc)
  {}

public:
  ObJoinType join_type_;
  common::ObFixedArray<ObExpr*, common::ObIAllocator> other_join_conds_;

private:
  DISALLOW_COPY_AND_ASSIGN(ObJoinSpec);
};

class ObJoinOp : public ObOperator {
public:
  ObJoinOp(ObExecContext& exec_ctx, const ObOpSpec& spec, ObOpInput* input)
      : ObOperator(exec_ctx, spec, input), output_row_produced_(false), left_row_joined_(false)
  {}
  virtual ~ObJoinOp()
  {}

  virtual int inner_open() override
  {
    return ObOperator::inner_open();
  }
  virtual int rescan() override;
  virtual void destroy() override
  {
    ObOperator::destroy();
  }
  virtual int inner_close() override
  {
    return ObOperator::inner_close();
  }

  int blank_left_row();
  int blank_right_row();

  inline bool need_left_join() const;
  inline bool need_right_join() const;

  int calc_other_conds(bool& is_match);

  virtual int get_next_left_row();
  virtual int get_next_right_row();

  const ObJoinSpec& get_spec() const
  {
    return static_cast<const ObJoinSpec&>(spec_);
  }

public:
  bool output_row_produced_;
  bool left_row_joined_;

private:
  DISALLOW_COPY_AND_ASSIGN(ObJoinOp);
};

inline bool ObJoinOp::need_left_join() const
{
  return (LEFT_OUTER_JOIN == get_spec().join_type_ || FULL_OUTER_JOIN == get_spec().join_type_);
}

inline bool ObJoinOp::need_right_join() const
{
  return (RIGHT_OUTER_JOIN == get_spec().join_type_ || FULL_OUTER_JOIN == get_spec().join_type_);
}

}  // end namespace sql
}  // end namespace oceanbase
#endif
