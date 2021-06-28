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

#include <gtest/gtest.h>
#include "sql/engine/expr/ob_expr_and.h"
#include "ob_expr_test_utils.h"

using namespace oceanbase::common;
using namespace oceanbase::sql;

class ObExprAndTest : public ::testing::Test {
public:
  ObExprAndTest();
  virtual ~ObExprAndTest();
  virtual void SetUp();
  virtual void TearDown();

private:
  // disallow copy
  ObExprAndTest(const ObExprAndTest& other);
  ObExprAndTest& operator=(const ObExprAndTest& other);

protected:
  // data members
};

ObExprAndTest::ObExprAndTest()
{}

ObExprAndTest::~ObExprAndTest()
{}

void ObExprAndTest::SetUp()
{}

void ObExprAndTest::TearDown()
{}

// calc result
#define R2(t1, v1, t2, v2, rtype, res) LOGIC_EXPECT2(ObExprAnd, &buf, calc_result2, t1, v1, t2, v2, rtype, res)
#define R3(t1, v1, t2, v2, t3, v3, rtype, res) \
  LOGIC_EXPECT3(ObExprAnd, &buf, calc_result3, t1, v1, t2, v2, t3, v3, rtype, res)
#define RN(num, rtype, res, ...) LOGIC_EXPECTN(ObExprAnd, num, rtype, res, __VA_ARGS__)

// calc result error
#define E2(t1, v1, t2, v2) LOGIC_ERROR2(ObExprAnd, calc_result2, t1, v1, t2, v2)
#define E3(t1, v1, t2, v2, t3, v3) LOGIC_ERROR3(ObExprAnd, calc_result3, t1, v1, t2, v2, t3, v3)
#define EN(num, ...) LOGIC_ERRORN(ObExprAnd, num, __VA_ARGS__)

// calc type
#define T2(t1, t2, res) LOGIC_EXPECT_TYPE2(ObExprAnd, calc_result_type2, t1, t2, res)
#define T3(t1, t2, t3, res) LOGIC_EXPECT_TYPE3(ObExprAnd, calc_result_type3, t1, t2, t3, res)
#define TN(num, res, ...) LOGIC_EXPECT_TYPEN(ObExprAnd, num, res, __VA_ARGS__)

//#define TE2(t1, t2, res) LOGIC_EXPECT_TYPE_WITH_ROW(ObExprAnd, calc_result_type2, t1, t2, res)
//#define TE3(t1, t2, t3, res) LOGIC_EXPECT_TYPE_WITH_ROW(ObExprAnd, calc_result_type2, t1, t2, t3, res)
//#define TEN(t1, t2, res) LOGIC_EXPECT_TYPE_WITH_ROW(ObExprAnd, calc_result_type2, t1, t2, res)

TEST_F(ObExprAndTest, type_test)
{
  T2(ObNullType, ObNullType, ObNullType);
  T2(ObNullType, ObIntType, ObNullType);
  T2(ObNullType, ObFloatType, ObNullType);
  T2(ObNullType, ObDoubleType, ObNullType);
  T2(ObNullType, ObDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObNullType, ObPreciseDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObNullType, ObVarcharType, ObNullType);
  T2(ObNullType, ObUnknownType, ObNullType);
  T2(ObNullType, ObCreateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObNullType, ObModifyTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObNullType, ObExtendType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObNullType, ObBoolType, ObNullType);

  T2(ObIntType, ObNullType, ObNullType);
  T2(ObIntType, ObIntType, ObBoolType);
  T2(ObIntType, ObFloatType, ObBoolType);
  T2(ObIntType, ObDoubleType, ObBoolType);
  T2(ObIntType, ObDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObIntType, ObPreciseDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObIntType, ObVarcharType, ObBoolType);
  T2(ObIntType, ObUnknownType, ObBoolType);
  T2(ObIntType, ObCreateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObIntType, ObModifyTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObIntType, ObExtendType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObIntType, ObBoolType, ObBoolType);

  T2(ObFloatType, ObNullType, ObNullType);
  T2(ObFloatType, ObIntType, ObBoolType);
  T2(ObFloatType, ObFloatType, ObBoolType);
  T2(ObFloatType, ObDoubleType, ObBoolType);
  T2(ObFloatType, ObDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObFloatType, ObPreciseDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObFloatType, ObVarcharType, ObBoolType);
  T2(ObFloatType, ObUnknownType, ObBoolType);
  T2(ObFloatType, ObCreateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObFloatType, ObModifyTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObFloatType, ObExtendType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObFloatType, ObBoolType, ObBoolType);

  T2(ObDoubleType, ObNullType, ObNullType);
  T2(ObDoubleType, ObIntType, ObBoolType);
  T2(ObDoubleType, ObFloatType, ObBoolType);
  T2(ObDoubleType, ObDoubleType, ObBoolType);
  T2(ObDoubleType, ObDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObDoubleType, ObPreciseDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObDoubleType, ObVarcharType, ObBoolType);
  T2(ObDoubleType, ObUnknownType, ObBoolType);
  T2(ObDoubleType, ObCreateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObDoubleType, ObModifyTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObDoubleType, ObExtendType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObDoubleType, ObBoolType, ObBoolType);

  T2(ObVarcharType, ObNullType, ObNullType);
  T2(ObVarcharType, ObIntType, ObBoolType);
  T2(ObVarcharType, ObFloatType, ObBoolType);
  T2(ObVarcharType, ObDoubleType, ObBoolType);
  T2(ObVarcharType, ObDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObVarcharType, ObPreciseDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObVarcharType, ObVarcharType, ObBoolType);
  T2(ObVarcharType, ObUnknownType, ObBoolType);
  T2(ObVarcharType, ObCreateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObVarcharType, ObModifyTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObVarcharType, ObExtendType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObVarcharType, ObBoolType, ObBoolType);

  T2(ObUnknownType, ObNullType, ObNullType);
  T2(ObUnknownType, ObIntType, ObBoolType);
  T2(ObUnknownType, ObFloatType, ObBoolType);
  T2(ObUnknownType, ObDoubleType, ObBoolType);
  T2(ObUnknownType, ObDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObUnknownType, ObPreciseDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObUnknownType, ObVarcharType, ObBoolType);
  T2(ObUnknownType, ObUnknownType, ObBoolType);
  T2(ObUnknownType, ObCreateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObUnknownType, ObModifyTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObUnknownType, ObExtendType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObUnknownType, ObBoolType, ObBoolType);

  T2(ObExtendType, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObExtendType, ObIntType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObExtendType, ObFloatType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObExtendType, ObDoubleType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObExtendType, ObDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObExtendType, ObPreciseDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObExtendType, ObVarcharType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObExtendType, ObUnknownType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObExtendType, ObCreateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObExtendType, ObModifyTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObExtendType, ObExtendType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObExtendType, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);

  T2(ObBoolType, ObNullType, ObNullType);
  T2(ObBoolType, ObIntType, ObBoolType);
  T2(ObBoolType, ObFloatType, ObBoolType);
  T2(ObBoolType, ObDoubleType, ObBoolType);
  T2(ObBoolType, ObDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObBoolType, ObPreciseDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObBoolType, ObVarcharType, ObBoolType);
  T2(ObBoolType, ObUnknownType, ObBoolType);
  T2(ObBoolType, ObCreateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObBoolType, ObModifyTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObBoolType, ObExtendType, OB_ERR_INVALID_TYPE_FOR_OP);
  T2(ObBoolType, ObBoolType, ObBoolType);

  T3(ObIntType, ObNullType, ObNullType, ObNullType);
  T3(ObIntType, ObNullType, ObIntType, ObNullType);
  T3(ObIntType, ObNullType, ObFloatType, ObNullType);
  T3(ObIntType, ObNullType, ObDoubleType, ObNullType);
  T3(ObIntType, ObNullType, ObDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObIntType, ObNullType, ObPreciseDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObIntType, ObNullType, ObVarcharType, ObNullType);
  T3(ObIntType, ObNullType, ObUnknownType, ObNullType);
  T3(ObIntType, ObNullType, ObCreateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObIntType, ObNullType, ObModifyTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObIntType, ObNullType, ObExtendType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObIntType, ObNullType, ObBoolType, ObNullType);

  T3(ObFloatType, ObIntType, ObNullType, ObNullType);
  T3(ObFloatType, ObIntType, ObIntType, ObBoolType);
  T3(ObFloatType, ObIntType, ObFloatType, ObBoolType);
  T3(ObFloatType, ObIntType, ObDoubleType, ObBoolType);
  T3(ObFloatType, ObIntType, ObDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObFloatType, ObIntType, ObPreciseDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObFloatType, ObIntType, ObVarcharType, ObBoolType);
  T3(ObFloatType, ObIntType, ObUnknownType, ObBoolType);
  T3(ObFloatType, ObIntType, ObCreateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObFloatType, ObIntType, ObModifyTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObFloatType, ObIntType, ObExtendType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObFloatType, ObIntType, ObBoolType, ObBoolType);

  T3(ObDoubleType, ObFloatType, ObNullType, ObNullType);
  T3(ObDoubleType, ObFloatType, ObIntType, ObBoolType);
  T3(ObDoubleType, ObFloatType, ObFloatType, ObBoolType);
  T3(ObDoubleType, ObFloatType, ObDoubleType, ObBoolType);
  T3(ObDoubleType, ObFloatType, ObDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDoubleType, ObFloatType, ObPreciseDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDoubleType, ObFloatType, ObVarcharType, ObBoolType);
  T3(ObDoubleType, ObFloatType, ObUnknownType, ObBoolType);
  T3(ObDoubleType, ObFloatType, ObCreateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDoubleType, ObFloatType, ObModifyTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDoubleType, ObFloatType, ObExtendType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDoubleType, ObFloatType, ObBoolType, ObBoolType);

  T3(ObDateTimeType, ObDoubleType, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDateTimeType, ObDoubleType, ObIntType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDateTimeType, ObDoubleType, ObFloatType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDateTimeType, ObDoubleType, ObDoubleType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDateTimeType, ObDoubleType, ObDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDateTimeType, ObDoubleType, ObPreciseDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDateTimeType, ObDoubleType, ObVarcharType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDateTimeType, ObDoubleType, ObUnknownType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDateTimeType, ObDoubleType, ObCreateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDateTimeType, ObDoubleType, ObModifyTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDateTimeType, ObDoubleType, ObExtendType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDateTimeType, ObDoubleType, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);

  T3(ObUnknownType, ObVarcharType, ObNullType, ObNullType);
  T3(ObUnknownType, ObVarcharType, ObIntType, ObBoolType);
  T3(ObUnknownType, ObVarcharType, ObFloatType, ObBoolType);
  T3(ObUnknownType, ObVarcharType, ObDoubleType, ObBoolType);
  T3(ObUnknownType, ObVarcharType, ObDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObUnknownType, ObVarcharType, ObPreciseDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObUnknownType, ObVarcharType, ObVarcharType, ObBoolType);
  T3(ObUnknownType, ObVarcharType, ObUnknownType, ObBoolType);
  T3(ObUnknownType, ObVarcharType, ObCreateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObUnknownType, ObVarcharType, ObModifyTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObUnknownType, ObVarcharType, ObExtendType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObUnknownType, ObVarcharType, ObBoolType, ObBoolType);

  T3(ObIntType, ObUnknownType, ObNullType, ObNullType);
  T3(ObIntType, ObUnknownType, ObIntType, ObBoolType);
  T3(ObIntType, ObUnknownType, ObFloatType, ObBoolType);
  T3(ObIntType, ObUnknownType, ObDoubleType, ObBoolType);
  T3(ObIntType, ObUnknownType, ObDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObIntType, ObUnknownType, ObPreciseDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObIntType, ObUnknownType, ObVarcharType, ObBoolType);
  T3(ObIntType, ObUnknownType, ObUnknownType, ObBoolType);
  T3(ObIntType, ObUnknownType, ObCreateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObIntType, ObUnknownType, ObModifyTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObIntType, ObUnknownType, ObExtendType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObIntType, ObUnknownType, ObBoolType, ObBoolType);

  T3(ObBoolType, ObExtendType, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObBoolType, ObExtendType, ObIntType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObBoolType, ObExtendType, ObFloatType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObBoolType, ObExtendType, ObDoubleType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObBoolType, ObExtendType, ObDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObBoolType, ObExtendType, ObPreciseDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObBoolType, ObExtendType, ObVarcharType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObBoolType, ObExtendType, ObUnknownType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObBoolType, ObExtendType, ObCreateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObBoolType, ObExtendType, ObModifyTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObBoolType, ObExtendType, ObExtendType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObBoolType, ObExtendType, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);

  T3(ObDoubleType, ObBoolType, ObNullType, ObNullType);
  T3(ObDoubleType, ObBoolType, ObIntType, ObBoolType);
  T3(ObDoubleType, ObBoolType, ObFloatType, ObBoolType);
  T3(ObDoubleType, ObBoolType, ObDoubleType, ObBoolType);
  T3(ObDoubleType, ObBoolType, ObDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDoubleType, ObBoolType, ObPreciseDateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDoubleType, ObBoolType, ObVarcharType, ObBoolType);
  T3(ObDoubleType, ObBoolType, ObUnknownType, ObBoolType);
  T3(ObDoubleType, ObBoolType, ObCreateTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDoubleType, ObBoolType, ObModifyTimeType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDoubleType, ObBoolType, ObExtendType, OB_ERR_INVALID_TYPE_FOR_OP);
  T3(ObDoubleType, ObBoolType, ObBoolType, ObBoolType);

  TN(2, ObNullType, ObNullType, ObNullType);
  TN(2, ObNullType, ObIntType, ObNullType);
  TN(2, ObNullType, ObFloatType, ObNullType);
  TN(2, ObNullType, ObDoubleType, ObNullType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObDateTimeType, ObNullType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObPreciseDateTimeType, ObNullType);
  TN(2, ObNullType, ObVarcharType, ObNullType);
  TN(2, ObNullType, ObUnknownType, ObNullType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObCreateTimeType, ObNullType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObModifyTimeType, ObNullType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObExtendType, ObNullType);
  TN(2, ObNullType, ObBoolType, ObNullType);

  TN(2, ObNullType, ObNullType, ObNullType);
  TN(2, ObBoolType, ObIntType, ObBoolType);
  TN(2, ObBoolType, ObFloatType, ObBoolType);
  TN(2, ObBoolType, ObDoubleType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObDateTimeType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObPreciseDateTimeType, ObBoolType);
  TN(2, ObBoolType, ObVarcharType, ObBoolType);
  TN(2, ObBoolType, ObUnknownType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObCreateTimeType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObModifyTimeType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObExtendType, ObBoolType);
  TN(2, ObBoolType, ObBoolType, ObBoolType);

  TN(2, ObNullType, ObNullType, ObNullType);
  TN(2, ObBoolType, ObIntType, ObBoolType);
  TN(2, ObBoolType, ObFloatType, ObBoolType);
  TN(2, ObBoolType, ObDoubleType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObDateTimeType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObPreciseDateTimeType, ObBoolType);
  TN(2, ObBoolType, ObVarcharType, ObBoolType);
  TN(2, ObBoolType, ObUnknownType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObCreateTimeType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObModifyTimeType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObExtendType, ObBoolType);
  TN(2, ObBoolType, ObBoolType, ObBoolType);

  TN(2, ObNullType, ObNullType, ObNullType);
  TN(2, ObBoolType, ObIntType, ObBoolType);
  TN(2, ObBoolType, ObFloatType, ObBoolType);
  TN(2, ObBoolType, ObDoubleType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObDateTimeType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObPreciseDateTimeType, ObBoolType);
  TN(2, ObBoolType, ObVarcharType, ObBoolType);
  TN(2, ObBoolType, ObUnknownType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObCreateTimeType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObModifyTimeType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObExtendType, ObBoolType);
  TN(2, ObBoolType, ObBoolType, ObBoolType);

  TN(2, ObNullType, ObNullType, ObNullType);
  TN(2, ObBoolType, ObIntType, ObBoolType);
  TN(2, ObBoolType, ObFloatType, ObBoolType);
  TN(2, ObBoolType, ObDoubleType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObDateTimeType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObPreciseDateTimeType, ObBoolType);
  TN(2, ObBoolType, ObVarcharType, ObBoolType);
  TN(2, ObBoolType, ObUnknownType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObCreateTimeType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObModifyTimeType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObExtendType, ObBoolType);
  TN(2, ObBoolType, ObBoolType, ObBoolType);

  TN(2, ObNullType, ObNullType, ObNullType);
  TN(2, ObBoolType, ObIntType, ObBoolType);
  TN(2, ObBoolType, ObFloatType, ObBoolType);
  TN(2, ObBoolType, ObDoubleType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObDateTimeType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObPreciseDateTimeType, ObBoolType);
  TN(2, ObBoolType, ObVarcharType, ObBoolType);
  TN(2, ObBoolType, ObUnknownType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObCreateTimeType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObModifyTimeType, ObBoolType);
  TN(2, OB_ERR_INVALID_TYPE_FOR_OP, ObExtendType, ObBoolType);
  TN(2, ObBoolType, ObBoolType, ObBoolType);

  TN(3, ObNullType, ObIntType, ObNullType, ObNullType);
  TN(3, ObNullType, ObIntType, ObIntType, ObNullType);
  TN(3, ObNullType, ObIntType, ObFloatType, ObNullType);
  TN(3, ObNullType, ObIntType, ObDoubleType, ObNullType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObDateTimeType, ObNullType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObPreciseDateTimeType, ObNullType);
  TN(3, ObNullType, ObIntType, ObVarcharType, ObNullType);
  TN(3, ObNullType, ObIntType, ObUnknownType, ObNullType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObCreateTimeType, ObNullType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObModifyTimeType, ObNullType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObExtendType, ObNullType);
  TN(3, ObNullType, ObIntType, ObBoolType, ObNullType);
  TN(3, ObNullType, ObIntType, ObNullType, ObNullType);
  TN(3, ObBoolType, ObIntType, ObIntType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObFloatType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObDoubleType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObDateTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObPreciseDateTimeType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObVarcharType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObUnknownType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObCreateTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObModifyTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObExtendType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObBoolType, ObBoolType);
  TN(3, ObNullType, ObIntType, ObNullType, ObNullType);
  TN(3, ObBoolType, ObIntType, ObIntType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObFloatType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObDoubleType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObDateTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObPreciseDateTimeType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObVarcharType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObUnknownType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObCreateTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObModifyTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObExtendType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObBoolType, ObBoolType);
  TN(3, ObNullType, ObIntType, ObNullType, ObNullType);
  TN(3, ObBoolType, ObIntType, ObIntType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObFloatType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObDoubleType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObDateTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObPreciseDateTimeType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObVarcharType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObUnknownType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObCreateTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObModifyTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObExtendType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObBoolType, ObBoolType);
  TN(3, ObNullType, ObIntType, ObNullType, ObNullType);
  TN(3, ObBoolType, ObIntType, ObIntType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObFloatType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObDoubleType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObDateTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObPreciseDateTimeType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObVarcharType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObUnknownType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObCreateTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObModifyTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObExtendType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObBoolType, ObBoolType);
  TN(3, ObNullType, ObIntType, ObNullType, ObNullType);
  TN(3, ObBoolType, ObIntType, ObIntType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObFloatType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObDoubleType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObDateTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObPreciseDateTimeType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObVarcharType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObUnknownType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObCreateTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObModifyTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObExtendType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObBoolType, ObBoolType);
  TN(3, ObNullType, ObIntType, ObNullType, ObNullType);
  TN(3, ObBoolType, ObIntType, ObIntType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObFloatType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObDoubleType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObDateTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObPreciseDateTimeType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObVarcharType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObUnknownType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObCreateTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObModifyTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObExtendType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObBoolType, ObBoolType);
  TN(3, ObNullType, ObIntType, ObNullType, ObNullType);
  TN(3, ObBoolType, ObIntType, ObIntType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObFloatType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObDoubleType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObDateTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObPreciseDateTimeType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObVarcharType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObUnknownType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObCreateTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObModifyTimeType, ObBoolType);
  TN(3, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObExtendType, ObBoolType);
  TN(3, ObBoolType, ObIntType, ObBoolType, ObBoolType);

  TN(4, ObNullType, ObIntType, ObFloatType, ObNullType, ObNullType);
  TN(4, ObNullType, ObIntType, ObFloatType, ObIntType, ObNullType);
  TN(4, ObNullType, ObIntType, ObFloatType, ObFloatType, ObNullType);
  TN(4, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObNullType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDateTimeType, ObNullType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObPreciseDateTimeType, ObNullType);
  TN(4, ObNullType, ObIntType, ObFloatType, ObVarcharType, ObNullType);
  TN(4, ObNullType, ObIntType, ObFloatType, ObUnknownType, ObNullType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObCreateTimeType, ObNullType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObModifyTimeType, ObNullType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObExtendType, ObNullType);
  TN(4, ObNullType, ObIntType, ObFloatType, ObBoolType, ObNullType);
  TN(4, ObNullType, ObIntType, ObFloatType, ObNullType, ObNullType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObIntType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObFloatType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDateTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObPreciseDateTimeType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObVarcharType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObUnknownType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObCreateTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObModifyTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObExtendType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObBoolType, ObBoolType);
  TN(4, ObNullType, ObIntType, ObFloatType, ObNullType, ObNullType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObIntType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObFloatType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDateTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObPreciseDateTimeType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObVarcharType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObUnknownType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObCreateTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObModifyTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObExtendType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObBoolType, ObBoolType);
  TN(4, ObNullType, ObIntType, ObFloatType, ObNullType, ObNullType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObIntType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObFloatType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDateTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObPreciseDateTimeType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObVarcharType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObUnknownType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObCreateTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObModifyTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObExtendType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObBoolType, ObBoolType);
  TN(4, ObNullType, ObIntType, ObFloatType, ObNullType, ObNullType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObIntType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObFloatType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDateTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObPreciseDateTimeType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObVarcharType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObUnknownType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObCreateTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObModifyTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObExtendType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObBoolType, ObBoolType);
  TN(4, ObNullType, ObIntType, ObFloatType, ObNullType, ObNullType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObIntType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObFloatType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDateTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObPreciseDateTimeType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObVarcharType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObUnknownType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObCreateTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObModifyTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObExtendType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObBoolType, ObBoolType);
  TN(4, ObNullType, ObIntType, ObFloatType, ObNullType, ObNullType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObIntType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObFloatType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDateTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObPreciseDateTimeType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObVarcharType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObUnknownType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObCreateTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObModifyTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObExtendType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObBoolType, ObBoolType);
  TN(4, ObNullType, ObIntType, ObFloatType, ObNullType, ObNullType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObIntType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObFloatType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDateTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObPreciseDateTimeType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObVarcharType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObUnknownType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObCreateTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObModifyTimeType, ObBoolType);
  TN(4, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObExtendType, ObBoolType);
  TN(4, ObBoolType, ObIntType, ObFloatType, ObBoolType, ObBoolType);

  TN(5, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObNullType, ObNullType);
  TN(5, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObIntType, ObNullType);
  TN(5, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObFloatType, ObNullType);
  TN(5, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObDoubleType, ObNullType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObDateTimeType, ObNullType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObPreciseDateTimeType, ObNullType);
  TN(5, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObVarcharType, ObNullType);
  TN(5, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObNullType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObCreateTimeType, ObNullType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObModifyTimeType, ObNullType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObExtendType, ObNullType);
  TN(5, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObBoolType, ObNullType);
  TN(5, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObNullType, ObNullType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObIntType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObFloatType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObDoubleType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObDateTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObPreciseDateTimeType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObVarcharType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObCreateTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObModifyTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObExtendType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObBoolType, ObBoolType);
  TN(5, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObNullType, ObNullType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObIntType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObFloatType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObDoubleType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObDateTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObPreciseDateTimeType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObVarcharType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObCreateTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObModifyTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObExtendType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObBoolType, ObBoolType);
  TN(5, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObNullType, ObNullType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObIntType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObFloatType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObDoubleType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObDateTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObPreciseDateTimeType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObVarcharType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObCreateTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObModifyTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObExtendType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObBoolType, ObBoolType);
  TN(5, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObNullType, ObNullType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObIntType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObFloatType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObDoubleType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObDateTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObPreciseDateTimeType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObVarcharType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObCreateTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObModifyTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObExtendType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObBoolType, ObBoolType);
  TN(5, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObNullType, ObNullType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObIntType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObFloatType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObDoubleType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObDateTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObPreciseDateTimeType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObVarcharType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObCreateTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObModifyTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObExtendType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObBoolType, ObBoolType);
  TN(5, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObNullType, ObNullType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObIntType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObFloatType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObDoubleType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObDateTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObPreciseDateTimeType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObVarcharType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObCreateTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObModifyTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObExtendType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObBoolType, ObBoolType);
  TN(5, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObNullType, ObNullType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObIntType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObFloatType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObDoubleType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObDateTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObPreciseDateTimeType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObVarcharType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObCreateTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObModifyTimeType, ObBoolType);
  TN(5, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObExtendType, ObBoolType);
  TN(5, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObBoolType, ObBoolType);

  TN(6, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObNullType, ObNullType);
  TN(6, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObIntType, ObNullType);
  TN(6, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObFloatType, ObNullType);
  TN(6, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObDoubleType, ObNullType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObDateTimeType, ObNullType);
  TN(6,
      OB_ERR_INVALID_TYPE_FOR_OP,
      ObIntType,
      ObFloatType,
      ObDoubleType,
      ObUnknownType,
      ObPreciseDateTimeType,
      ObNullType);
  TN(6, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObVarcharType, ObNullType);
  TN(6, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObUnknownType, ObNullType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObCreateTimeType, ObNullType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObModifyTimeType, ObNullType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObExtendType, ObNullType);
  TN(6, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObBoolType, ObNullType);
  TN(6, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObNullType, ObNullType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObIntType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObFloatType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObDoubleType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObDateTimeType, ObBoolType);
  TN(6,
      OB_ERR_INVALID_TYPE_FOR_OP,
      ObIntType,
      ObFloatType,
      ObDoubleType,
      ObUnknownType,
      ObPreciseDateTimeType,
      ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObVarcharType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObUnknownType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObCreateTimeType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObModifyTimeType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObExtendType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObBoolType, ObBoolType);
  TN(6, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObNullType, ObNullType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObIntType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObFloatType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObDoubleType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObDateTimeType, ObBoolType);
  TN(6,
      OB_ERR_INVALID_TYPE_FOR_OP,
      ObIntType,
      ObFloatType,
      ObDoubleType,
      ObUnknownType,
      ObPreciseDateTimeType,
      ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObVarcharType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObUnknownType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObCreateTimeType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObModifyTimeType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObExtendType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObBoolType, ObBoolType);
  TN(6, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObNullType, ObNullType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObIntType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObFloatType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObDoubleType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObDateTimeType, ObBoolType);
  TN(6,
      OB_ERR_INVALID_TYPE_FOR_OP,
      ObIntType,
      ObFloatType,
      ObDoubleType,
      ObUnknownType,
      ObPreciseDateTimeType,
      ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObVarcharType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObUnknownType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObCreateTimeType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObModifyTimeType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObExtendType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObBoolType, ObBoolType);
  TN(6, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObNullType, ObNullType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObIntType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObFloatType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObDoubleType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObDateTimeType, ObBoolType);
  TN(6,
      OB_ERR_INVALID_TYPE_FOR_OP,
      ObIntType,
      ObFloatType,
      ObDoubleType,
      ObUnknownType,
      ObPreciseDateTimeType,
      ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObVarcharType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObUnknownType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObCreateTimeType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObModifyTimeType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObExtendType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObBoolType, ObBoolType);
  TN(6, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObNullType, ObNullType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObIntType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObFloatType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObDoubleType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObDateTimeType, ObBoolType);
  TN(6,
      OB_ERR_INVALID_TYPE_FOR_OP,
      ObIntType,
      ObFloatType,
      ObDoubleType,
      ObUnknownType,
      ObPreciseDateTimeType,
      ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObVarcharType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObUnknownType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObCreateTimeType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObModifyTimeType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObExtendType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObBoolType, ObBoolType);
  TN(6, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObNullType, ObNullType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObIntType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObFloatType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObDoubleType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObDateTimeType, ObBoolType);
  TN(6,
      OB_ERR_INVALID_TYPE_FOR_OP,
      ObIntType,
      ObFloatType,
      ObDoubleType,
      ObUnknownType,
      ObPreciseDateTimeType,
      ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObVarcharType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObUnknownType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObCreateTimeType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObModifyTimeType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObExtendType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObBoolType, ObBoolType);
  TN(6, ObNullType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObNullType, ObNullType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObIntType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObFloatType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObDoubleType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObDateTimeType, ObBoolType);
  TN(6,
      OB_ERR_INVALID_TYPE_FOR_OP,
      ObIntType,
      ObFloatType,
      ObDoubleType,
      ObUnknownType,
      ObPreciseDateTimeType,
      ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObVarcharType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObUnknownType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObCreateTimeType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObModifyTimeType, ObBoolType);
  TN(6, OB_ERR_INVALID_TYPE_FOR_OP, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObExtendType, ObBoolType);
  TN(6, ObBoolType, ObIntType, ObFloatType, ObDoubleType, ObUnknownType, ObBoolType, ObBoolType);
}

TEST_F(ObExprAndTest, result2_test)
{
  // calc result2
  // null type
  /* lt   lv  rt   rv  restype     res.get_bool()*/
  ObExprStringBuf buf;
  R2(null, 0, null, 0, ObNullType, OB_OBJ_TYPE_ERROR);
  R2(null, 0, int, 1, ObNullType, OB_OBJ_TYPE_ERROR);
  R2(null, 0, float, 1.0, ObNullType, OB_OBJ_TYPE_ERROR);
  R2(null, 0, double, 2.0, ObNullType, OB_OBJ_TYPE_ERROR);
  R2(null, 0, datetime, 2, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(null, 0, precise_datetime, 2, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(null, 0, varchar, "hello", ObNullType, OB_ERR_CAST_VARCHAR_TO_BOOL);
  R2(null, 0, ctime, 2, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(null, 0, mtime, 2, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(null, 0, ext, 0, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(null, 0, bool, 0, ObBoolType, 0);
  R2(null, 0, unknown, 0, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  // int type
  R2(int, 0, null, 0, ObBoolType, 0);
  R2(int, 1, null, 0, ObNullType, OB_OBJ_TYPE_ERROR);
  R2(int, 0, int, 0, ObBoolType, 0);
  R2(int, 0, int, 1, ObBoolType, 0);
  R2(int, 1, int, 0, ObBoolType, 0);
  R2(int, 1, int, 1, ObBoolType, 1);
  R2(int, 0, float, 0.0, ObBoolType, 0);
  R2(int, 0, float, 1.0, ObBoolType, 0);
  R2(int, 1, float, 0.0, ObBoolType, 0);
  R2(int, 1, float, 1.0, ObBoolType, 1);
  R2(int, 0, double, 0.0, ObBoolType, 0);
  R2(int, 0, double, 1.0, ObBoolType, 0);
  R2(int, 1, double, 0.0, ObBoolType, 0);
  R2(int, 1, double, 1.0, ObBoolType, 1);
  R2(int, 0, datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 0, datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 1, datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 1, datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 0, precise_datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 0, precise_datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 1, precise_datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 1, precise_datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 0, varchar, "0", ObBoolType, 0);
  R2(int, 0, varchar, "1", ObBoolType, 0);
  R2(int, 1, varchar, "0", ObBoolType, 0);
  R2(int, 1, varchar, "1", ObBoolType, 1);
  R2(int, 0, unknown, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 1, unknown, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 0, ctime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 0, ctime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 1, ctime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 1, ctime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 0, mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 0, mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 1, mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 1, mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 0, ext, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 0, ext, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 1, ext, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 1, ext, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(int, 0, bool, 0, ObBoolType, 0);
  R2(int, 0, bool, 1, ObBoolType, 0);
  R2(int, 1, bool, 0, ObBoolType, 0);
  R2(int, 1, bool, 1, ObBoolType, 1);

  // float type
  R2(float, float(0.0), null, 0, ObBoolType, 0);
  R2(float, float(0.1), null, 0, ObNullType, OB_OBJ_TYPE_ERROR);
  R2(float, float(0.0), int, 0, ObBoolType, 0);
  R2(float, float(0.0), int, 1, ObBoolType, 0);
  R2(float, float(0.1), int, 0, ObBoolType, 0);
  R2(float, float(0.1), int, 1, ObBoolType, 1);
  R2(float, float(0.0), float, 0.0, ObBoolType, 0);
  R2(float, float(0.0), float, 1.0, ObBoolType, 0);
  R2(float, float(0.1), float, 0.0, ObBoolType, 0);
  R2(float, float(0.1), float, 1.0, ObBoolType, 1);
  R2(float, float(0.0), double, 0.0, ObBoolType, 0);
  R2(float, float(0.0), double, 1.0, ObBoolType, 0);
  R2(float, float(0.1), double, 0.0, ObBoolType, 0);
  R2(float, float(0.1), double, 1.0, ObBoolType, 1);
  R2(float, float(0.0), datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.0), datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.1), datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.1), datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.0), precise_datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.0), precise_datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.1), precise_datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.1), precise_datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.0), varchar, "0", ObBoolType, 0);
  R2(float, float(0.0), varchar, "1", ObBoolType, 0);
  R2(float, float(0.1), varchar, "0", ObBoolType, 0);
  R2(float, float(0.1), varchar, "1", ObBoolType, 1);
  R2(float, float(0.0), unknown, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.1), unknown, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.0), ctime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.0), ctime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.1), ctime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.1), ctime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.0), mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.0), mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.1), mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.1), mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.0), ext, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.0), ext, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.1), ext, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.1), ext, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(float, float(0.0), bool, 0, ObBoolType, 0);
  R2(float, float(0.0), bool, 1, ObBoolType, 0);
  R2(float, float(0.1), bool, 0, ObBoolType, 0);
  R2(float, float(0.1), bool, 1, ObBoolType, 1);

  // double
  R2(double, 0.0, null, 0, ObBoolType, 0);
  R2(double, 1.0, null, 0, ObNullType, OB_OBJ_TYPE_ERROR);
  R2(double, 0.0, int, 0, ObBoolType, 0);
  R2(double, 0.0, int, 1, ObBoolType, 0);
  R2(double, 1.0, int, 0, ObBoolType, 0);
  R2(double, 1.0, int, 1, ObBoolType, 1);
  R2(double, 0.0, float, 0.0, ObBoolType, 0);
  R2(double, 0.0, float, 1.0, ObBoolType, 0);
  R2(double, 1.0, float, 0.0, ObBoolType, 0);
  R2(double, 1.0, float, 1.0, ObBoolType, 1);
  R2(double, 0.0, double, 0.0, ObBoolType, 0);
  R2(double, 0.0, double, 1.0, ObBoolType, 0);
  R2(double, 1.0, double, 0.0, ObBoolType, 0);
  R2(double, 1.0, double, 1.0, ObBoolType, 1);
  R2(double, 0.0, datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 0.0, datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 1.0, datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 1.0, datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 0.0, precise_datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 0.0, precise_datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 1.0, precise_datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 1.0, precise_datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 0.0, varchar, "0", ObBoolType, 0);
  R2(double, 0.0, varchar, "1", ObBoolType, 0);
  R2(double, 1.0, varchar, "0", ObBoolType, 0);
  R2(double, 1.0, varchar, "1", ObBoolType, 1);
  R2(double, 0.0, unknown, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 1.0, unknown, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 0.0, ctime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 0.0, ctime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 1.0, ctime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 1.0, ctime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 0.0, mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 0.0, mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 1.0, mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 1.0, mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 0.0, ext, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 0.0, ext, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 1.0, ext, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 1.0, ext, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(double, 0.0, bool, 0, ObBoolType, 0);
  R2(double, 0.0, bool, 1, ObBoolType, 0);
  R2(double, 1.0, bool, 0, ObBoolType, 0);
  R2(double, 1.0, bool, 1, ObBoolType, 1);

  R2(datetime, 0, null, 0, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, null, 0, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, int, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, int, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, int, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, int, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, float, 0.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, float, 1.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, float, 0.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, float, 1.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, double, 0.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, double, 1.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, double, 0.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, double, 1.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, precise_datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, precise_datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, precise_datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, precise_datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, varchar, "0", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, varchar, "1", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, varchar, "0", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, varchar, "1", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, unknown, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, unknown, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, ctime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, ctime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, ctime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, ctime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, ext, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, ext, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, ext, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, ext, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, bool, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 0, bool, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, bool, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(datetime, 1, bool, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);

  R2(precise_datetime, 0, null, 0, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, null, 0, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, int, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, int, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, int, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, int, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, float, 0.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, float, 1.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, float, 0.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, float, 1.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, double, 0.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, double, 1.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, double, 0.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, double, 1.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, precise_datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, precise_datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, precise_datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, precise_datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, varchar, "0", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, varchar, "1", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, varchar, "0", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, varchar, "1", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, unknown, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, unknown, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, ctime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, ctime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, ctime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, ctime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, ext, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, ext, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, ext, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, ext, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, bool, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 0, bool, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, bool, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(precise_datetime, 1, bool, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);

  R2(varchar, "0", null, 0, ObBoolType, 0);
  R2(varchar, "1", null, 0, ObNullType, OB_OBJ_TYPE_ERROR);
  R2(varchar, "0", int, 0, ObBoolType, 0);
  R2(varchar, "0", int, 1, ObBoolType, 0);
  R2(varchar, "1", int, 0, ObBoolType, 0);
  R2(varchar, "1", int, 1, ObBoolType, 1);
  R2(varchar, "0", float, 0.0, ObBoolType, 0);
  R2(varchar, "0", float, 1.0, ObBoolType, 0);
  R2(varchar, "1", float, 0.0, ObBoolType, 0);
  R2(varchar, "1", float, 1.0, ObBoolType, 1);
  R2(varchar, "0", double, 0.0, ObBoolType, 0);
  R2(varchar, "0", double, 1.0, ObBoolType, 0);
  R2(varchar, "1", double, 0.0, ObBoolType, 0);
  R2(varchar, "1", double, 1.0, ObBoolType, 1);
  R2(varchar, "0", datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "0", datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "1", datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "1", datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "0", precise_datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "0", precise_datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "1", precise_datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "1", precise_datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "0", varchar, "0", ObBoolType, 0);
  R2(varchar, "0", varchar, "1", ObBoolType, 0);
  R2(varchar, "1", varchar, "0", ObBoolType, 0);
  R2(varchar, "1", varchar, "1", ObBoolType, 1);
  R2(varchar, "0", unknown, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "1", unknown, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "0", ctime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "0", ctime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "1", ctime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "1", ctime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "0", mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "0", mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "1", mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "1", mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "0", ext, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "0", ext, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "1", ext, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "1", ext, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(varchar, "0", bool, 0, ObBoolType, 0);
  R2(varchar, "0", bool, 1, ObBoolType, 0);
  R2(varchar, "1", bool, 0, ObBoolType, 0);
  R2(varchar, "1", bool, 1, ObBoolType, 1);

  R2(ctime, 0, null, 0, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, null, 0, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, int, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, int, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, int, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, int, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, float, 0.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, float, 1.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, float, 0.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, float, 1.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, double, 0.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, double, 1.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, double, 0.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, double, 1.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, precise_datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, precise_datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, precise_datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, precise_datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, varchar, "0", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, varchar, "1", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, varchar, "0", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, varchar, "1", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, unknown, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, unknown, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, ctime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, ctime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, ctime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, ctime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, ext, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, ext, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, ext, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, ext, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, bool, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 0, bool, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, bool, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ctime, 1, bool, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);

  R2(mtime, 0, null, 0, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, null, 0, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, int, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, int, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, int, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, int, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, float, 0.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, float, 1.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, float, 0.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, float, 1.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, double, 0.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, double, 1.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, double, 0.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, double, 1.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, precise_datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, precise_datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, precise_datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, precise_datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, varchar, "0", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, varchar, "1", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, varchar, "0", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, varchar, "1", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, unknown, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, unknown, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, ctime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, ctime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, ctime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, ctime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, ext, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, ext, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, ext, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, ext, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, bool, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 0, bool, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, bool, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(mtime, 1, bool, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);

  R2(ext, 0, null, 0, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, null, 0, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, int, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, int, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, int, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, int, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, float, 0.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, float, 1.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, float, 0.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, float, 1.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, double, 0.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, double, 1.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, double, 0.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, double, 1.0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, precise_datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, precise_datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, precise_datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, precise_datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, varchar, "0", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, varchar, "1", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, varchar, "0", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, varchar, "1", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, unknown, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, unknown, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, ctime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, ctime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, ctime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, ctime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, ext, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, ext, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, ext, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, ext, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, bool, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 0, bool, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, bool, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(ext, 1, bool, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);

  R2(bool, 0, null, 0, ObBoolType, 0);
  R2(bool, 1, null, 0, ObNullType, OB_OBJ_TYPE_ERROR);
  R2(bool, 0, int, 0, ObBoolType, 0);
  R2(bool, 0, int, 1, ObBoolType, 0);
  R2(bool, 1, int, 0, ObBoolType, 0);
  R2(bool, 1, int, 1, ObBoolType, 1);
  R2(bool, 0, float, 0.0, ObBoolType, 0);
  R2(bool, 0, float, 1.0, ObBoolType, 0);
  R2(bool, 1, float, 0.0, ObBoolType, 0);
  R2(bool, 1, float, 1.0, ObBoolType, 1);
  R2(bool, 0, double, 0.0, ObBoolType, 0);
  R2(bool, 0, double, 1.0, ObBoolType, 0);
  R2(bool, 1, double, 0.0, ObBoolType, 0);
  R2(bool, 1, double, 1.0, ObBoolType, 1);
  R2(bool, 0, datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 0, datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 1, datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 1, datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 0, precise_datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 0, precise_datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 1, precise_datetime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 1, precise_datetime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 0, varchar, "0", ObBoolType, 0);
  R2(bool, 0, varchar, "1", ObBoolType, 0);
  R2(bool, 1, varchar, "0", ObBoolType, 0);
  R2(bool, 1, varchar, "1", ObBoolType, 1);
  R2(bool, 1, varchar, "he", ObBoolType, OB_ERR_CAST_VARCHAR_TO_BOOL);
  R2(bool, 0, unknown, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 1, unknown, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 0, ctime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 0, ctime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 1, ctime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 1, ctime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 0, mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 0, mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 1, mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 1, mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 0, ext, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 0, ext, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 1, ext, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 1, ext, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R2(bool, 0, bool, 0, ObBoolType, 0);
  R2(bool, 0, bool, 1, ObBoolType, 0);
  R2(bool, 1, bool, 0, ObBoolType, 0);
  R2(bool, 1, bool, 1, ObBoolType, 1);
}

TEST_F(ObExprAndTest, result3_test)
{
  // calc result3
  // null type
  /* at   av  bt   bv  ct   cv    restype     res.get_bool()*/
  ObExprStringBuf buf;
  R3(null, 0, null, 0, bool, 1, ObNullType, OB_OBJ_TYPE_ERROR);
  R3(null, 0, int, 1, ext, 2, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(null, 0, float, 1.0, mtime, 2, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(null, 0, double, 2.0, ctime, 2, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(null, 0, datetime, 2, mtime, 3, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(null, 0, precise_datetime, 2, double, 2.0, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(null, 0, varchar, "hello", datetime, 2, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(null, 0, ctime, 2, double, 2.0, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(null, 0, mtime, 2, float, 1.0, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(null, 0, ext, 0, int, 1, ObNullType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(null, 0, bool, 0, null, 0, ObBoolType, 0);

  R3(int, 0, null, 0, int, 1, ObBoolType, 0);
  R3(int, 1, null, 0, int, 1, ObNullType, OB_OBJ_TYPE_ERROR);
  R3(int, 0, int, 0, int, 1, ObBoolType, 0);
  R3(int, 0, int, 1, int, 1, ObBoolType, 0);
  R3(int, 1, int, 0, int, 1, ObBoolType, 0);
  R3(int, 1, int, 1, int, 1, ObBoolType, 1);
  R3(int, 0, float, float(0.0), int, 1, ObBoolType, 0);
  R3(int, 0, float, float(1.0), int, 1, ObBoolType, 0);
  R3(int, 1, float, float(0.0), int, 1, ObBoolType, 0);
  R3(int, 1, float, float(1.0), int, 1, ObBoolType, 1);
  R3(int, 0, double, 0.0, ctime, 2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(int, 0, double, 1.0, ctime, 2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(int, 1, double, 0.0, ctime, 2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(int, 1, double, 1.0, ctime, 2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(double, 0.0, datetime, 0, varchar, "1", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(double, 0.0, datetime, 1, varchar, "1", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(double, 1.0, datetime, 0, varchar, "1", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(double, 1.0, datetime, 1, varchar, "1", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(ctime, 0, precise_datetime, 0, float, float(2.2), ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(ctime, 0, precise_datetime, 1, float, float(2.2), ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(ctime, 1, precise_datetime, 0, float, float(2.2), ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(ctime, 1, precise_datetime, 1, float, float(2.2), ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(varchar, "0", varchar, "0", varchar, "0", ObBoolType, 0);
  R3(varchar, "0", varchar, "1", varchar, "1", ObBoolType, 0);
  R3(varchar, "1", varchar, "0", varchar, "0", ObBoolType, 0);
  R3(varchar, "1", varchar, "1", varchar, "1", ObBoolType, 1);
  R3(int, 0, unknown, 0, varchar, "0", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(int, 1, unknown, 0, varchar, "1", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(int, 0, ctime, 0, varchar, "0", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(int, 0, ctime, 1, varchar, "1", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(int, 1, ctime, 0, varchar, "0", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(int, 1, ctime, 1, varchar, "1", ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(varchar, "0", int, 0, mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(varchar, "1", int, 0, mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(varchar, "0", int, 1, mtime, 0, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(varchar, "1", int, 1, mtime, 1, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP);
  R3(int, 0, varchar, "0", int, 0, ObBoolType, 0);
  R3(int, 0, varchar, "1", int, 1, ObBoolType, 0);
  R3(int, 1, varchar, "0", int, 0, ObBoolType, 0);
  R3(int, 1, varchar, "1", int, 1, ObBoolType, 1);
  R3(int, 0, varchar, "0", bool, 0, ObBoolType, 0);
  R3(int, 0, varchar, "1", bool, 1, ObBoolType, 0);
  R3(int, 1, varchar, "0", bool, 0, ObBoolType, 0);
  R3(int, 1, varchar, "1", bool, 1, ObBoolType, 1);
}

TEST_F(ObExprAndTest, resultN_test)
{
  // calc result3
  // null type
  // num, rtype, res, at av  bt bv  ct cv dt dv...
  ObExprStringBuf buf;
  RN(2, ObNullType, OB_OBJ_TYPE_ERROR, null, 0, null, 0);
  RN(2, ObNullType, OB_OBJ_TYPE_ERROR, null, 0, int, 1);

  RN(2, ObBoolType, 0, int, 0, int, 0);
  RN(2, ObBoolType, 0, int, 0, int, 1);
  RN(2, ObBoolType, 0, int, 1, int, 0);
  RN(2, ObBoolType, 0, int, 0, float, 0.0);
  RN(2, ObBoolType, 0, int, 0, float, 1.0);
  RN(2, ObBoolType, 0, int, 1, float, 0.0);
  RN(2, ObBoolType, 1, int, 1, float, 1.0);
  RN(2, ObBoolType, 0, int, 0, double, 1.0);
  RN(2, ObBoolType, 0, int, 1, double, 0.0);
  RN(2, ObBoolType, 1, int, 1, double, 1.0);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, datetime, 0);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, datetime, 1);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, datetime, 0);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, datetime, 1);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, precise_datetime, 0);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, precise_datetime, 1);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, precise_datetime, 0);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, precise_datetime, 1);
  RN(2, ObBoolType, 0, int, 0, varchar, "0");
  RN(2, ObBoolType, 0, int, 0, varchar, "1");
  RN(2, ObBoolType, 0, int, 1, varchar, "0");
  RN(2, ObBoolType, 1, int, 1, varchar, "1");
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, unknown, 0);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, unknown, 0);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, ctime, 0);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, ctime, 1);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, ctime, 0);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, ctime, 1);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, mtime, 0);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, mtime, 1);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, mtime, 0);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, mtime, 1);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, ext, 0);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, ext, 1);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, ext, 0);
  RN(2, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, ext, 1);
  RN(2, ObBoolType, 0, int, 0, bool, 0);
  RN(2, ObBoolType, 0, int, 0, bool, 1);
  RN(2, ObBoolType, 0, int, 1, bool, 0);
  RN(2, ObBoolType, 1, int, 1, bool, 1);

  // RN3
  RN(3, ObBoolType, 0, null, 0, null, 0, int, 0);
  RN(3, ObNullType, OB_OBJ_TYPE_ERROR, null, 0, int, 1, int, 1);
  RN(3, ObBoolType, 0, int, 0, int, 0, int, 1);
  RN(3, ObBoolType, 0, int, 0, int, 1, int, 1);
  RN(3, ObBoolType, 0, int, 1, int, 0, int, 1);
  RN(3, ObBoolType, 0, int, 0, float, 0.0, int, 1);
  RN(3, ObBoolType, 0, int, 0, float, 1.0, int, 1);
  RN(3, ObBoolType, 0, int, 1, float, 0.0, int, 1);
  RN(3, ObBoolType, 1, int, 1, float, 1.0, int, 1);
  RN(3, ObBoolType, 0, int, 0, double, 1.0, float, float(1));
  RN(3, ObBoolType, 0, int, 1, double, 0.0, float, float(1));
  RN(3, ObBoolType, 1, int, 1, double, 1.0, float, float(1));
  RN(3, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, datetime, 0, float, float(1));
  RN(3, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, datetime, 1, float, float(1));
  RN(3, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, datetime, 0, float, float(1));
  RN(3, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, datetime, 1, float, float(1));
  RN(3, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, precise_datetime, 0, datetime, 2);
  RN(3, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, precise_datetime, 1, datetime, 2);
  RN(3, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, precise_datetime, 0, datetime, 2);
  RN(3, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, precise_datetime, 1, datetime, 2);
  RN(3, ObBoolType, 0, int, 0, varchar, "0", int, 2);
  RN(3, ObBoolType, 0, int, 0, varchar, "1", int, 2);
  RN(3, ObBoolType, 0, int, 1, varchar, "0", int, 2);
  RN(3, ObBoolType, 1, int, 1, varchar, "1", int, 2);
  RN(3, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, unknown, 0, datetime, 2);
  RN(3, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, unknown, 0, datetime, 2);
  RN(3, ObBoolType, 0, int, 0, int, 0, varchar, "1");
  RN(3, ObBoolType, 0, int, 0, int, 1, varchar, "1");
  RN(3, ObBoolType, 0, int, 1, int, 0, varchar, "1");
  RN(3, ObBoolType, 1, int, 1, int, 1, varchar, "1");
  RN(3, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, mtime, 0, varchar, "1");
  RN(3, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, mtime, 1, varchar, "1");
  RN(3, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, mtime, 0, varchar, "1");
  RN(3, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, mtime, 1, varchar, "1");
  RN(3, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, ext, 0, bool, 1);
  RN(3, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, ext, 1, bool, 1);
  RN(3, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, ext, 0, bool, 1);
  RN(3, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, ext, 1, bool, 1);
  RN(3, ObBoolType, 0, int, 0, bool, 0, bool, 1);
  RN(3, ObBoolType, 0, int, 0, bool, 1, bool, 1);
  RN(3, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, bool, 0, ext, 1);
  RN(3, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, bool, 1, ext, 2);

  // RN4
  RN(4, ObBoolType, 0, null, 0, null, 0, int, 0, double, 0.0);
  RN(4, ObNullType, OB_OBJ_TYPE_ERROR, null, 0, int, 1, int, 1, double, 3.0);
  RN(4, ObBoolType, 0, int, 0, int, 0, int, 1, float, float(1));
  RN(4, ObBoolType, 0, int, 0, int, 1, int, 1, float, float(1));
  RN(4, ObBoolType, 0, int, 1, int, 0, int, 1, float, float(1));
  RN(4, ObBoolType, 0, int, 0, float, 0.0, int, 1, float, float(1));
  RN(4, ObBoolType, 0, int, 0, float, 1.0, int, 1, float, float(1));
  RN(4, ObBoolType, 0, int, 1, float, 0.0, int, 1, float, float(1));
  RN(4, ObBoolType, 1, int, 1, float, 1.0, int, 1, float, float(1));
  RN(4, ObBoolType, 0, int, 0, double, 1.0, float, float(1), double, 2.0);
  RN(4, ObBoolType, 0, int, 1, double, 0.0, float, float(1), double, 2.0);
  RN(4, ObBoolType, 1, int, 1, double, 1.0, float, float(1), double, 2.0);
  RN(4, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, datetime, 0, float, float(1), double, 2.0);
  RN(4, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, datetime, 1, float, float(1), ext, 1);
  RN(4, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, datetime, 0, float, float(1), ext, 1);
  RN(4, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, datetime, 1, float, float(1), ext, 1);
  RN(4, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, precise_datetime, 0, datetime, 2, ext, 1);
  RN(4, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, precise_datetime, 1, datetime, 2, ext, 1);
  RN(4, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, precise_datetime, 0, datetime, 2, ext, 1);
  RN(4, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, precise_datetime, 1, datetime, 2, ext, 1);
  RN(4, ObBoolType, OB_ERR_CAST_VARCHAR_TO_BOOL, int, 0, varchar, "0", int, 2, varchar, "2hello");
  RN(4, ObBoolType, OB_ERR_CAST_VARCHAR_TO_BOOL, int, 0, varchar, "1", int, 2, varchar, "2hello");
  RN(4, ObBoolType, OB_ERR_CAST_VARCHAR_TO_BOOL, int, 1, varchar, "0", int, 2, varchar, "2hello");
  RN(4, ObBoolType, OB_ERR_CAST_VARCHAR_TO_BOOL, int, 1, varchar, "1", int, 2, varchar, "2hello");
  RN(4, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, unknown, 0, datetime, 2, varchar, "2hello");
  RN(4, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, unknown, 0, datetime, 2, varchar, "2hello");
  RN(4, ObBoolType, 0, int, 0, int, 0, varchar, "1", int, 2);
  RN(4, ObBoolType, 0, int, 0, int, 1, varchar, "1", int, 2);
  RN(4, ObBoolType, 0, int, 1, int, 0, varchar, "1", int, 2);
  RN(4, ObBoolType, 1, int, 1, int, 1, varchar, "1", int, 2);
  RN(4, ObBoolType, 0, int, 0, int, 0, varchar, "1", int, 3);
  RN(4, ObBoolType, 0, int, 0, int, 1, varchar, "1", int, 3);
  RN(4, ObBoolType, 0, int, 1, int, 0, varchar, "1", int, 3);
  RN(4, ObBoolType, 1, int, 1, int, 1, varchar, "1", int, 3);
  RN(4, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, ext, 0, bool, 1, double, 3.4);
  RN(4, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, ext, 1, bool, 1, double, 3.4);
  RN(4, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, ext, 0, bool, 1, double, 3.4);
  RN(4, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, ext, 1, bool, 1, double, 3.4);
  RN(4, ObBoolType, 0, int, 0, bool, 0, bool, 1, double, 3.4);
  RN(4, ObBoolType, 0, int, 0, bool, 1, bool, 1, double, 3.4);
  RN(4, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, bool, 0, ext, 1, double, 3.4);
  RN(4, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, bool, 1, ext, 2, double, 3.4);

  // RN5
  RN(5, ObBoolType, 0, null, 0, null, 0, int, 0, double, 2.0, int, 2);
  RN(5, ObNullType, OB_OBJ_TYPE_ERROR, null, 0, int, 1, int, 1, double, 3.0, int, 3);
  RN(5, ObBoolType, 0, int, 0, int, 0, int, 1, float, float(1), int, 4);
  RN(5, ObBoolType, 0, int, 0, int, 1, int, 1, float, float(1), int, 4);
  RN(5, ObBoolType, 0, int, 1, int, 0, int, 1, float, float(1), int, 4);
  RN(5, ObBoolType, 0, int, 0, float, 0.0, int, 1, float, float(1), int, 4);
  RN(5, ObBoolType, 0, int, 0, float, 1.0, int, 1, float, float(1), int, 4);
  RN(5, ObBoolType, 0, int, 1, float, 0.0, int, 1, float, float(1), int, 4);
  RN(5, ObBoolType, 1, int, 1, float, 1.0, int, 1, float, float(1), int, 4);
  RN(5, ObBoolType, OB_ERR_CAST_VARCHAR_TO_BOOL, int, 0, double, 1.0, float, float(1), double, 2.0, varchar, "1he");
  RN(5, ObBoolType, OB_ERR_CAST_VARCHAR_TO_BOOL, int, 1, double, 0.0, float, float(1), double, 2.0, varchar, "1he");
  RN(5, ObBoolType, OB_ERR_CAST_VARCHAR_TO_BOOL, int, 1, double, 1.0, float, float(1), double, 2.0, varchar, "1he");
  RN(5, ObBoolType, OB_ERR_CAST_VARCHAR_TO_BOOL, int, 0, int, 0, float, float(1), double, 2.0, varchar, "1he");
  RN(5, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, datetime, 1, float, float(1), ext, 1, varchar, "1he");
  RN(5, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, datetime, 0, float, float(1), ext, 1, varchar, "1he");
  RN(5, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, datetime, 1, float, float(1), ext, 1, varchar, "1he");
  RN(5, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, precise_datetime, 0, datetime, 2, ext, 1, double, 3.4);
  RN(5, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, precise_datetime, 1, datetime, 2, ext, 1, double, 3.4);
  RN(5, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, precise_datetime, 0, datetime, 2, ext, 1, double, 3.4);
  RN(5, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, precise_datetime, 1, datetime, 2, ext, 1, double, 3.4);
  RN(5, ObBoolType, 0, int, 0, varchar, "0", int, 2, varchar, "true", double, 3.4);
  RN(5, ObBoolType, 0, int, 0, varchar, "1", int, 2, varchar, "true", double, 3.4);
  RN(5, ObBoolType, 0, int, 1, varchar, "0", int, 2, varchar, "true", double, 3.4);
  RN(5, ObBoolType, 1, int, 1, varchar, "1", int, 2, varchar, "true", double, 3.4);
  RN(5, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, unknown, 0, datetime, 2, varchar, "2hello", double, 3.4);
  RN(5, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, unknown, 0, datetime, 2, varchar, "2hello", double, 3.4);
  RN(5, ObBoolType, 0, int, 0, int, 0, varchar, "1", int, 2, float, float(2.3));
  RN(5, ObBoolType, 0, int, 0, int, 1, varchar, "1", int, 2, float, float(2.3));
  RN(5, ObBoolType, 0, int, 1, int, 0, varchar, "1", int, 2, float, float(2.3));
  RN(5, ObBoolType, 1, int, 1, int, 1, varchar, "1", int, 2, float, float(2.3));
  RN(5, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, mtime, 0, varchar, "1", ctime, 3, float, float(2.3));
  RN(5, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, mtime, 1, varchar, "1", ctime, 3, float, float(2.3));
  RN(5, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, mtime, 0, varchar, "1", ctime, 3, float, float(2.3));
  RN(5, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, mtime, 1, varchar, "1", ctime, 3, float, float(2.3));
  RN(5, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, ext, 0, bool, 1, double, 3.4, int, 3);
  RN(5, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, ext, 1, bool, 1, double, 3.4, int, 3);
  RN(5, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, ext, 0, bool, 1, double, 3.4, int, 3);
  RN(5, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, ext, 1, bool, 1, double, 3.4, int, 3);
  RN(5, ObBoolType, 0, int, 0, bool, 0, bool, 1, double, 3.4, int, 3);
  RN(5, ObBoolType, 0, int, 0, bool, 1, bool, 1, double, 3.4, int, 3);
  RN(5, ObBoolType, 0, int, 1, bool, 0, int, 1, double, 3.4, int, 3);
  RN(5, ObBoolType, 1, int, 1, bool, 1, int, 2, double, 3.4, int, 3);

  // RN6
  RN(6, ObBoolType, 0, null, 0, null, 0, int, 0, double, 2.0, int, 2, varchar, "1");
  RN(6, ObNullType, OB_OBJ_TYPE_ERROR, null, 0, int, 1, int, 1, double, 3.0, int, 3, varchar, "true");
  RN(6, ObBoolType, 0, int, 0, int, 0, int, 1, float, float(1), int, 4, varchar, "1");
  RN(6, ObBoolType, 0, int, 0, int, 1, int, 1, float, float(1), int, 4, varchar, "1");
  RN(6, ObBoolType, 0, int, 1, int, 0, int, 1, float, float(1), int, 4, varchar, "1");
  RN(6,
      ObBoolType,
      OB_ERR_INVALID_TYPE_FOR_OP,
      int,
      0,
      float,
      0.0,
      int,
      1,
      float,
      float(1),
      ctime,
      4,
      varchar,
      "1hello");
  RN(6,
      ObBoolType,
      OB_ERR_INVALID_TYPE_FOR_OP,
      int,
      0,
      float,
      1.0,
      int,
      1,
      float,
      float(1),
      ctime,
      4,
      varchar,
      "1hello");
  RN(6,
      ObBoolType,
      OB_ERR_INVALID_TYPE_FOR_OP,
      int,
      1,
      float,
      0.0,
      int,
      1,
      float,
      float(1),
      ctime,
      4,
      varchar,
      "1hello");
  RN(6,
      ObBoolType,
      OB_ERR_INVALID_TYPE_FOR_OP,
      int,
      1,
      float,
      1.0,
      int,
      1,
      float,
      float(1),
      ctime,
      4,
      varchar,
      "1hello");
  RN(6, ObBoolType, 0, int, 0, double, 1.0, float, float(1), double, 2.0, varchar, "true", int, 2);
  RN(6, ObBoolType, 0, int, 1, double, 0.0, float, float(1), double, 2.0, varchar, "true", int, 2);
  RN(6, ObBoolType, 1, int, 1, double, 1.0, float, float(1), double, 2.0, varchar, "true", int, 2);
  RN(6, ObBoolType, 0, int, 0, int, 0, float, float(1), double, 2.0, varchar, "true", int, 2);
  RN(6, ObBoolType, 0, int, 0, int, 1, float, float(1), int, 1, varchar, "1", int, 2);
  RN(6, ObBoolType, 0, int, 1, int, 0, float, float(1), int, 1, varchar, "1", int, 2);
  RN(6, ObBoolType, 1, int, 1, int, 1, float, float(1), int, 1, varchar, "1", int, 2);
  RN(6,
      ObBoolType,
      OB_ERR_INVALID_TYPE_FOR_OP,
      int,
      0,
      precise_datetime,
      0,
      datetime,
      2,
      ext,
      1,
      double,
      3.4,
      varchar,
      "time");
  RN(6,
      ObBoolType,
      OB_ERR_INVALID_TYPE_FOR_OP,
      int,
      0,
      precise_datetime,
      1,
      datetime,
      2,
      ext,
      1,
      double,
      3.4,
      varchar,
      "time");
  RN(6,
      ObBoolType,
      OB_ERR_INVALID_TYPE_FOR_OP,
      int,
      1,
      precise_datetime,
      0,
      datetime,
      2,
      ext,
      1,
      double,
      3.4,
      varchar,
      "time");
  RN(6,
      ObBoolType,
      OB_ERR_INVALID_TYPE_FOR_OP,
      int,
      1,
      precise_datetime,
      1,
      datetime,
      2,
      ext,
      1,
      double,
      3.4,
      varchar,
      "time");
  RN(6, ObBoolType, OB_ERR_CAST_VARCHAR_TO_BOOL, int, 0, varchar, "0", int, 2, varchar, "2hello", double, 3.4, int, 0);
  RN(6, ObBoolType, OB_ERR_CAST_VARCHAR_TO_BOOL, int, 0, varchar, "1", int, 2, varchar, "2hello", double, 3.4, int, 0);
  RN(6, ObBoolType, OB_ERR_CAST_VARCHAR_TO_BOOL, int, 1, varchar, "0", int, 2, varchar, "2hello", double, 3.4, int, 0);
  RN(6, ObBoolType, OB_ERR_CAST_VARCHAR_TO_BOOL, int, 1, varchar, "1", int, 2, varchar, "2hello", double, 3.4, int, 0);
  RN(6,
      ObBoolType,
      OB_ERR_INVALID_TYPE_FOR_OP,
      int,
      0,
      unknown,
      0,
      datetime,
      2,
      varchar,
      "2hello",
      double,
      3.4,
      int,
      0);
  RN(6,
      ObBoolType,
      OB_ERR_INVALID_TYPE_FOR_OP,
      int,
      1,
      unknown,
      0,
      datetime,
      2,
      varchar,
      "2hello",
      double,
      3.4,
      int,
      0);
  RN(6,
      ObBoolType,
      OB_ERR_INVALID_TYPE_FOR_OP,
      int,
      0,
      int,
      0,
      varchar,
      "1",
      precise_datetime,
      2,
      float,
      float(2.3),
      mtime,
      4);
  RN(6,
      ObBoolType,
      OB_ERR_INVALID_TYPE_FOR_OP,
      int,
      0,
      int,
      1,
      varchar,
      "1",
      precise_datetime,
      2,
      float,
      float(2.3),
      mtime,
      4);
  RN(6,
      ObBoolType,
      OB_ERR_INVALID_TYPE_FOR_OP,
      int,
      1,
      int,
      0,
      varchar,
      "1",
      precise_datetime,
      2,
      float,
      float(2.3),
      mtime,
      4);
  RN(6,
      ObBoolType,
      OB_ERR_INVALID_TYPE_FOR_OP,
      int,
      1,
      int,
      1,
      varchar,
      "1",
      precise_datetime,
      2,
      float,
      float(2.3),
      mtime,
      4);
  RN(6, ObBoolType, 0, int, 0, int, 0, varchar, "1", int, 3, float, float(2.3), double, 0.00);
  RN(6, ObBoolType, 0, int, 0, int, 1, varchar, "1", int, 3, float, float(2.3), double, 0.00);
  RN(6, ObBoolType, 0, int, 1, int, 0, varchar, "1", int, 3, float, float(2.3), double, 0.00);
  RN(6, ObBoolType, 0, int, 1, int, 1, varchar, "1", int, 3, float, float(2.3), double, 0.00);
  RN(6, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, ext, 0, bool, 1, double, 3.4, int, 3, double, 0.00);
  RN(6, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 0, ext, 1, bool, 1, double, 3.4, int, 3, double, 0.00);
  RN(6, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, ext, 0, bool, 1, double, 3.4, int, 3, double, 0.00);
  RN(6, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, ext, 1, bool, 1, double, 3.4, int, 3, double, 0.00);
  RN(6, ObBoolType, 0, int, 0, bool, 0, bool, 1, double, 3.4, int, 3, varchar, "true");
  RN(6, ObBoolType, 0, int, 0, bool, 1, bool, 1, double, 3.4, int, 3, varchar, "true");
  RN(6, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, bool, 0, ext, 1, double, 3.4, int, 3, varchar, "3hello");
  RN(6, ObBoolType, OB_ERR_INVALID_TYPE_FOR_OP, int, 1, bool, 1, ext, 2, double, 3.4, int, 3, varchar, "3hello");
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
