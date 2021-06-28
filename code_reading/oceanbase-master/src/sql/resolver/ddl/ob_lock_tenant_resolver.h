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

#ifndef _OB_LOCK_TENANT_RESOLVER_H
#define _OB_LOCK_TENANT_RESOLVER_H 1
#include "sql/resolver/ddl/ob_lock_tenant_stmt.h"
#include "sql/resolver/ddl/ob_ddl_resolver.h"
#include "lib/container/ob_se_array.h"
namespace oceanbase {
namespace sql {
class ObLockTenantResolver : public ObDDLResolver {
public:
  explicit ObLockTenantResolver(ObResolverParams& params);
  virtual ~ObLockTenantResolver();

  virtual int resolve(const ParseNode& parse_tree);

private:
  // types and constants
private:
  // disallow copy
  DISALLOW_COPY_AND_ASSIGN(ObLockTenantResolver);

private:
  // data members
};

}  // end namespace sql
}  // end namespace oceanbase

#endif /* _OB_LOCK_TENANT_RESOLVER_H */
