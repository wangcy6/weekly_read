

@所有人 有木有细心的小伙伴发现咱们的第五期课程已经上线啦！本节课程主题为：DDL 性能优化。

课程概要：
1. TiDB DDL 模块架构概览
2. DDL 性能优化——并行化
3. DDL 性能优化——即时化


视频链接在这里~ 欢迎享用~
https://www.bilibili.com/video/BV1X5411b7ri/

另外是不是有小伙伴对如何认领作业以及提交作业还有疑惑？答应你们的演示视频也同步上线啦！请大家戳这个链接了解详情：https://www.bilibili.com/video/BV1zA411E7t8/











### 预习

#### TiDB 源码阅读系列文章（十七）DDL 源码解析

https://pingcap.com/blog-cn/tidb-source-code-reading-17/

https://segmentfault.com/a/1190000023514267

![TiDB 中 DDL SQL 的处理流程](https://download.pingcap.com/images/blog-cn/tidb-source-code-reading-17/1.png)

- 阅读 理解 Google F1: Schema 变更算法

> F1 是 Google 开发的分布式关系数据库，主要服务于 Google 的广告系统，它提供强一致性、高可用性，
>
> 并支持传统 SQL 查询，近来也常常被称之为所谓的 NewSQL。
>
> F1 是构建于 Spanner 之上的。Spanner 是 Google 开发的全球级数据存储引擎，它保证了数据存储的一致性和可用性，还通过 2PC（两阶段提交）提供了分布式事务读写。
>
> 在分析 F1 时，我们可以简单地认为 Spanner 是一个全球分布的 kv 数据库



- 代码：https://github.com/pingcap/tidb/tree/source-code
- onCreateTable

![img](https://picb.zhimg.com/80/v2-6b88067473e2e6254b3b8cf922b0de11_720w.jpg)

~~~verilog
[2020/09/10 15:41:23.911 +08:00] [INFO] [conn.go:869] [dispatch] [conn=1] [data:="create table tt (a int, b int ,key(a))"]
[2020/09/10 15:41:23.911 +08:00] [INFO] [session.go:2257] ["CRUCIAL OPERATION"] [conn=1] 
[schemaVersion=188] [cur_db=test] [sql="create table tt (a int, b int ,key(a))"] [user=root@127.0.0.1]

[2020/09/10 15:41:23.933 +08:00] [WARN] [2pc.go:1006] ["schemaLeaseChecker is not set for this transaction, schema check skipped"] [connID=0] [startTS=419357965389922307] [commitTS=419357965389922308]

[2020/09/10 15:41:23.948 +08:00] [WARN] [2pc.go:1006] ["schemaLeaseChecker is not set for this transaction, schema check skipped"] [connID=0] [startTS=419357965402505217] [commitTS=419357965402505218]

[2020/09/10 15:41:23.951 +08:00] [INFO] [ddl_worker.go:260] ["[ddl] add DDL jobs"] ["batch count"=1] [jobs="ID:153, Type:create table, State:none, SchemaState:none, SchemaID:1, TableID:152, RowCount:0, ArgLen:1, start time: 2020-09-10 15:41:23.939 +0800 CST, Err:<nil>, ErrCount:0, SnapshotVersion:0; "]

[2020/09/10 15:41:23.951 +08:00] [INFO] [ddl.go:475] ["[ddl] start DDL job"] [job="ID:153, Type:create table, State:none, SchemaState:none, SchemaID:1, TableID:152, RowCount:0, ArgLen:1, start time: 2020-09-10 15:41:23.939 +0800 CST, Err:<nil>, ErrCount:0, SnapshotVersion:0"] [query="create table tt (a int, b int ,key(a))"]

[2020/09/10 15:41:23.955 +08:00] [INFO] [ddl_worker.go:589] ["[ddl] run DDL job"] [worker="worker 1, tp general"] [job="ID:153, Type:create table, State:none, SchemaState:none, SchemaID:1, TableID:152, RowCount:0, ArgLen:0, start time: 2020-09-10 15:41:23.939 +0800 CST, Err:<nil>, ErrCount:0, SnapshotVersion:0"]

[2020/09/10 15:41:23.993 +08:00] [WARN] [2pc.go:1006] ["schemaLeaseChecker is not set for this transaction, schema check skipped"] [connID=0] [startTS=419357965402505220] [commitTS=419357965415612417]

[2020/09/10 15:41:24.010 +08:00] [INFO] [domain.go:127] ["diff load InfoSchema success"] [usedSchemaVersion=188] [neededSchemaVersion=189] ["start time"=4.297325ms] [phyTblIDs="[152]"] [actionTypes="[8]"]

[2020/09/10 15:41:24.056 +08:00] [INFO] [ddl_worker.go:783] ["[ddl] wait latest schema version changed"] [worker="worker 1, tp general"] [ver=189] ["take time"=55.661518ms] [job="ID:153, Type:create table, State:done, SchemaState:public, SchemaID:1, TableID:152, RowCount:0, ArgLen:1, start time: 2020-09-10 15:41:23.939 +0800 CST, Err:<nil>, ErrCount:0, SnapshotVersion:0"]

[2020/09/10 15:41:24.061 +08:00] [INFO] [ddl_worker.go:366] ["[ddl] finish DDL job"] [worker="worker 1, tp general"] [job="ID:153, Type:create table, State:synced, SchemaState:public, SchemaID:1, TableID:152, RowCount:0, ArgLen:0, start time: 2020-09-10 15:41:23.939 +0800 CST, Err:<nil>, ErrCount:0, SnapshotVersion:0"]

[2020/09/10 15:41:24.069 +08:00] [WARN] [2pc.go:1006] ["schemaLeaseChecker is not set for this transaction, schema check skipped"] [connID=0] [startTS=419357965428719617] [commitTS=419357965428719618]


[2020/09/10 15:41:24.081 +08:00] [INFO] [ddl.go:507] ["[ddl] DDL job is finished"] [jobID=153]


[2020/09/10 15:41:24.084 +08:00] [INFO] [domain.go:643] ["performing DDL change, must reload"]
[2020/09/10 15:41:24.086 +08:00] [INFO] [split_region.go:59] ["split batch regions request"] ["split key count"=1] ["batch count"=1] ["first batch, region ID"=2] ["first split key"=748000000000000098]
[2020/09/10 15:41:24.095 +08:00] [INFO] [split_region.go:156] ["batch split regions complete"] ["batch region ID"=2] ["first at"=748000000000000098] ["first new region left"="{Id:2011 StartKey:7480000000000000ff9500000000000000f8 EndKey:7480000000000000ff9800000000000000f8 RegionEpoch:{ConfVer:1 Version:56} Peers:[id:2012 store_id:1 ]}"] ["new region count"=1]
[2020/09/10 15:41:24.095 +08:00] [INFO] [split_region.go:205] ["split regions complete"] ["region count"=1] ["region IDs"="[2011]"]

~~~





- add column

![img](https://pic3.zhimg.com/80/v2-de4c148aff1c3ed3f886bcce72f5ebc5_720w.jpg)



。假设系统中只有两个节点，TiDB Server 1 和 TiDB Server 2。

  其中 TiDB Server 1 是 DDL 操作的接收节点， 

![图2 TiDB Server 1流程图](https://github.com/ngaut/builddatabase/raw/master/f1/2.jpg)



TiDB Server 2 是 owner





~~~verilog
[2020/09/10 19:07:55.830 +08:00] [INFO] [conn.go:869] [dispatch] [conn=2] [data:="alter table tt add index(a,b)"]

[2020/09/10 19:07:55.832 +08:00] [INFO] [session.go:2257] ["CRUCIAL OPERATION"] [conn=2] 
[schemaVersion=189] [cur_db=test] [sql="alter table tt add index(a,b)"] [user=root@127.0.0.1]

[2020/09/10 19:07:55.864 +08:00] [WARN] [2pc.go:1006] ["schemaLeaseChecker is not set for this transaction, schema check skipped"] [connID=0] [startTS=419361213851631623] [commitTS=419361213865000961]

// addBatchDDLJobs gets global job IDs and puts the DDL jobs in the DDL queue.
//func (d *ddl) addBatchDDLJobs(tasks []*limitJobTask) {


[2020/09/10 19:07:55.871 +08:00] [INFO] [ddl_worker.go:260] ["[ddl] add DDL jobs"] ["batch count"=1] [jobs="ID:154, Type:add index, State:none, SchemaState:none, SchemaID:1, TableID:152, RowCount:0, ArgLen:5, start time: 2020-09-10 19:07:55.789 +0800 CST, Err:<nil>, ErrCount:0, SnapshotVersion:0; "]
[2020/09/10 19:07:55.871 +08:00] [INFO] [ddl.go:475] ["[ddl] start DDL job"] [job="ID:154, Type:add index, State:none, SchemaState:none, SchemaID:1, TableID:152, RowCount:0, ArgLen:5, start time: 2020-09-10 19:07:55.789 +0800 CST, Err:<nil>, ErrCount:0, SnapshotVersion:0"] [query="alter table tt add index(a,b)"]

//执行job
[2020/09/10 19:07:55.876 +08:00] [INFO] [ddl_worker.go:589] ["[ddl] run DDL job"] [worker="worker 2, tp add index"] [job="ID:154, Type:add index, State:none, SchemaState:none, SchemaID:1, TableID:152, RowCount:0, ArgLen:0, start time: 2020-09-10 19:07:55.789 +0800 CST, Err:<nil>, ErrCount:0, SnapshotVersion:0"]


[2020/09/10 19:07:55.880 +08:00] [INFO] [index.go:494] ["[ddl] run add index job"] [job="ID:154, Type:add index, State:running, SchemaState:none, SchemaID:1, TableID:152, RowCount:0, ArgLen:5, start time: 2020-09-10 19:07:55.789 +0800 CST, Err:<nil>, ErrCount:0, SnapshotVersion:0"] [indexInfo="{\"id\":2,\"idx_name\":{\"O\":\"a_2\",\"L\":\"a_2\"},\"tbl_name\":{\"O\":\"\",\"L\":\"\"},\"idx_cols\":[{\"name\":{\"O\":\"a\",\"L\":\"a\"},\"offset\":0,\"length\":-1},{\"name\":{\"O\":\"b\",\"L\":\"b\"},\"offset\":1,\"length\":-1}],\"state\":0,\"comment\":\"\",\"index_type\":1,\"is_unique\":false,\"is_primary\":false,\"is_invisible\":false,\"is_global\":false}"]


[2020/09/10 19:07:55.898 +08:00] [WARN] [2pc.go:1006] ["schemaLeaseChecker is not set for this transaction, schema check skipped"] [connID=0] [startTS=419361213865000963] [commitTS=419361213877846017]

[2020/09/10 19:07:55.922 +08:00] [INFO] [domain.go:127] ["diff load InfoSchema success"] [usedSchemaVersion=189] [neededSchemaVersion=190] ["start time"=2.577252ms] [phyTblIDs="[152]"] [actionTypes="[128]"]

[2020/09/10 19:07:55.969 +08:00] [INFO] [ddl_worker.go:783] ["[ddl] wait latest schema version changed"] [worker="worker 2, tp add index"] [ver=190] ["take time"=53.603813ms] [job="ID:154, Type:add index, State:running, SchemaState:delete only, SchemaID:1, TableID:152, RowCount:0, ArgLen:5, start time: 2020-09-10 19:07:55.789 +0800 CST, Err:<nil>, ErrCount:0, SnapshotVersion:0"]

[2020/09/10 19:07:55.971 +08:00] [INFO] [ddl_worker.go:589] ["[ddl] run DDL job"] [worker="worker 2, tp add index"] [job="ID:154, Type:add index, State:running, SchemaState:delete only, SchemaID:1, TableID:152, RowCount:0, ArgLen:0, start time: 2020-09-10 19:07:55.789 +0800 CST, Err:<nil>, ErrCount:0, SnapshotVersion:0"]


[2020/09/10 19:07:55.995 +08:00] [WARN] [2pc.go:1006] ["schemaLeaseChecker is not set for this transaction, schema check skipped"] [connID=0] [startTS=419361213890953217] [commitTS=419361213904322561]

[2020/09/10 19:07:56.022 +08:00] [INFO] [domain.go:127] ["diff load InfoSchema success"] [usedSchemaVersion=190] [neededSchemaVersion=191] ["start time"=3.679702ms] [phyTblIDs="[152]"] [actionTypes="[128]"]

[2020/09/10 19:07:56.067 +08:00] [INFO] [ddl_worker.go:783] ["[ddl] wait latest schema version changed"] [worker="worker 2, tp add index"] [ver=191] ["take time"=53.617313ms] [job="ID:154, Type:add index, State:running, SchemaState:write only, SchemaID:1, TableID:152, RowCount:0, ArgLen:5, start time: 2020-09-10 19:07:55.789 +0800 CST, Err:<nil>, ErrCount:0, SnapshotVersion:0"]
[2020/09/10 19:07:56.071 +08:00] [INFO] [ddl_worker.go:589] ["[ddl] run DDL job"] [worker="worker 2, tp add index"] [job="ID:154, Type:add index, State:running, SchemaState:write only, SchemaID:1, TableID:152, RowCount:0, ArgLen:0, start time: 2020-09-10 19:07:55.789 +0800 CST, Err:<nil>, ErrCount:0, SnapshotVersion:0"]

[2020/09/10 19:07:56.099 +08:00] [WARN] [2pc.go:1006] ["schemaLeaseChecker is not set for this transaction, schema check skipped"] [connID=0] [startTS=419361213917167617] [commitTS=419361213931061249]

[2020/09/10 19:07:56.119 +08:00] [INFO] [domain.go:127] ["diff load InfoSchema success"] [usedSchemaVersion=191] [neededSchemaVersion=192] ["start time"=3.587235ms] [phyTblIDs="[152]"] [actionTypes="[128]"]

[2020/09/10 19:07:56.171 +08:00] [INFO] [ddl_worker.go:783] 
["[ddl] wait latest schema version changed"] 
[worker="worker 2, tp add index"] 
[ver=192] 
["take time"=58.973371ms] 
[job="ID:154, Type:add index, State:running, SchemaState:write reorganization, SchemaID:1, TableID:152, RowCount:0, ArgLen:5, start time: 2020-09-10 19:07:55.789 +0800 CST, Err:<nil>, ErrCount:0, SnapshotVersion:0"]


[2020/09/10 19:07:56.175 +08:00] [INFO] [ddl_worker.go:589] ["[ddl] run DDL job"] [worker="worker 2, tp add index"] [job="ID:154, Type:add index, State:running, SchemaState:write reorganization, SchemaID:1, TableID:152, RowCount:0, ArgLen:0, start time: 2020-09-10 19:07:55.789 +0800 CST, Err:<nil>, ErrCount:0, SnapshotVersion:0"]

[2020/09/10 19:07:56.193 +08:00] [INFO] [reorg.go:420] ["[ddl] get table range, endHandle < startHandle"] [table="&{152 tt utf8mb4 utf8mb4_bin [int(11) int(11)] [0xc000ded050 0xc000ded0e0] [] [] public false false  0 0 0 2 2 0 419361213917167617 0 0 0 0 0 <nil>  <nil> <nil> <nil> 3 <nil>}"] ["table/partition ID"=152] [endHandle=<nil>] [startHandle=<nil>]
    
[2020/09/10 19:07:56.193 +08:00] [INFO] [reorg.go:465] ["[ddl] job get table range"] [jobID=154] [physicalTableID=152] [startHandle=<nil>] [endHandle=<nil>]
    
[2020/09/10 19:07:56.200 +08:00] [WARN] [2pc.go:1006] ["schemaLeaseChecker is not set for this transaction, schema check skipped"] [connID=0] [startTS=419361213943382017] [commitTS=419361213956489217]
    
[2020/09/10 19:07:56.204 +08:00] [INFO] [ddl_worker.go:755] ["[ddl] schema version doesn't change"] [worker="worker 2, tp add index"]
    
[2020/09/10 19:07:56.205 +08:00] [INFO] [ddl_worker.go:589] ["[ddl] run DDL job"] [worker="worker 2, tp add index"] [job="ID:154, Type:add index, State:running, SchemaState:write reorganization, SchemaID:1, TableID:152, RowCount:0, ArgLen:0, start time: 2020-09-10 19:07:55.789 +0800 CST, Err:<nil>, ErrCount:0, SnapshotVersion:419361213943382018"]
    
[2020/09/10 19:07:56.209 +08:00] [INFO] [index.go:1411] ["[ddl] start to add table index"] [job="ID:154, Type:add index, State:running, SchemaState:write reorganization, SchemaID:1, TableID:152, RowCount:0, ArgLen:5, start time: 2020-09-10 19:07:55.789 +0800 CST, Err:<nil>, ErrCount:0, SnapshotVersion:419361213943382018"] [reorgInfo=StartHandle:<nil>,EndHandle:<nil>,first:false,PhysicalTableID:152]
[2020/09/10 19:07:56.209 +08:00] [INFO] [reorg.go:158] ["[ddl] run reorg job done"] ["handled rows"=0]
[2020/09/10 19:07:56.218 +08:00] [WARN] [2pc.go:1006] ["schemaLeaseChecker is not set for this transaction, schema check skipped"] [connID=0] [startTS=419361213956489218] [commitTS=419361213956489219]
[2020/09/10 19:07:56.227 +08:00] [INFO] [domain.go:127] ["diff load InfoSchema success"] [usedSchemaVersion=192] [neededSchemaVersion=193] ["start time"=2.157282ms] [phyTblIDs="[152]"] [actionTypes="[128]"]
[2020/09/10 19:07:56.275 +08:00] [INFO] [ddl_worker.go:783] ["[ddl] wait latest schema version changed"] [worker="worker 2, tp add index"] [ver=193] ["take time"=53.11361ms] [job="ID:154, Type:add index, State:done, SchemaState:public, SchemaID:1, TableID:152, RowCount:0, ArgLen:5, start time: 2020-09-10 19:07:55.789 +0800 CST, Err:<nil>, ErrCount:0, SnapshotVersion:419361213943382018"]
[2020/09/10 19:07:56.281 +08:00] [INFO] [ddl_worker.go:366] ["[ddl] finish DDL job"] [worker="worker 2, tp add index"] [job="ID:154, Type:add index, State:synced, SchemaState:public, SchemaID:1, TableID:152, RowCount:0, ArgLen:0, start time: 2020-09-10 19:07:55.789 +0800 CST, Err:<nil>, ErrCount:0, SnapshotVersion:419361213943382018"]
[2020/09/10 19:07:56.290 +08:00] [WARN] [2pc.go:1006] ["schemaLeaseChecker is not set for this transaction, schema check skipped"] [connID=0] [startTS=419361213969596417] [commitTS=419361213982703617]
    
    
[2020/09/10 19:07:56.297 +08:00] [INFO] [ddl.go:507] ["[ddl] DDL job is finished"] [jobID=154]
    
[2020/09/10 19:07:56.297 +08:00] [INFO] [domain.go:643] ["performing DDL change, must reload"
                                                         
~~~



- CREATE TABLE t11(a INT,b INT,C INT,KEY 12333(a,b) );

~~~verilog

[2020/09/11 14:07:26.992 +08:00] [INFO] [conn.go:869] [dispatch] [conn=3] [data:="CREATE TABLE t11(a INT,b INT,C INT,KEY 12333(a,b) )"]
[2020/09/11 14:07:26.992 +08:00] [WARN] [session.go:1099] ["parse SQL failed"] [conn=3] [error="line 1 column 44 near \"12333(a,b) )\" "] [SQL="CREATE TABLE t11(a INT,b INT,C INT,KEY 12333(a,b) )"]


[2020/09/11 14:07:26.993 +08:00] [ERROR] [misc.go:167] ["syntax error"] [error="line 1 column 44 near \"12333(a,b) )\" "]
[2020/09/11 14:07:26.993 +08:00] [ERROR] [conn.go:744] ["command dispatched failed"] [conn=3] [connInfo="id:3, addr:127.0.0.1:53444 status:10, collation:utf8_general_ci, user:root"] [command=Query] [status="inTxn:0, autocommit:1"] [sql="CREATE TABLE t11(a INT,b INT,C INT,KEY 12333(a,b) )"] [txn_mode=PESSIMISTIC] [err="[parser:1064]You have an error in your SQL syntax; check the manual that corresponds to your TiDB version for the right syntax to use line 1 column 44 near \"12333(a,b) )\" "]

~~~

- mysql> CREATE TABLE t1122222222222222222222222222222222222222222222222222222222222222222(a INT,b INT,C INT);
  ERROR 1059 (42000): Identifier name 't1122222222222222222222222222222222222222222222222222222222222222222' is too long



~~~mysql

[2020/09/11 14:19:41.010 +08:00] [INFO] [conn.go:869] [dispatch] [conn=3] [data:="CREATE TABLE t1122222222222222222222222222222222222222222222222222222222222222222(a INT,b INT,C INT)"]
[2020/09/11 14:19:41.011 +08:00] [INFO] [session.go:2257] ["CRUCIAL OPERATION"] [conn=3] [schemaVersion=214] [cur_db=test] [sql="CREATE TABLE t1122222222222222222222222222222222222222222222222222222222222222222(a INT,b INT,C INT)"] [user=root@127.0.0.1]
[2020/09/11 14:19:41.023 +08:00] [WARN] [2pc.go:1006] ["schemaLeaseChecker is not set for this transaction, schema check skipped"] [connID=0] [startTS=419379329365442563] [commitTS=419379329365442564]
[2020/09/11 14:19:41.030 +08:00] [INFO] [tidb.go:217] ["rollbackTxn for ddl/autocommit failed"]
[2020/09/11 14:19:41.030 +08:00] [WARN] [session.go:1165] ["run statement failed"] [conn=3] [schemaVersion=214] [error="[ddl:1059]Identifier name 't1122222222222222222222222222222222222222222222222222222222222222222' is too long"] [session="{\n  \"currDBName\": \"test\",\n  \"id\": 3,\n  \"status\": 2,\n  \"strictMode\": true,\n  \"user\": {\n    \"Username\": \"root\",\n    \"Hostname\": \"127.0.0.1\",\n    \"CurrentUser\": false,\n    \"AuthUsername\": \"root\",\n    \"AuthHostname\": \"%\"\n  }\n}"]
[2020/09/11 14:19:41.031 +08:00] [ERROR] [conn.go:744] ["command dispatched failed"] [conn=3] [connInfo="id:3, addr:127.0.0.1:53444 status:10, collation:utf8_general_ci, user:root"] [command=Query] [status="inTxn:0, autocommit:1"] [sql="CREATE TABLE t1122222222222222222222222222222222222222222222222222222222222222222(a INT,b INT,C INT)"] [txn_mode=PESSIMISTIC] [err="[ddl:1059]Identifier name 't1122222222222222222222222222222222222222222222222222222222222222222' is too long\ngithub.com/pingcap/errors.AddStack\n\t/root/code/pkg/mod/github.com/pingcap/errors@v0.11.5-0.20200729012136-4e113ddee29e/errors.go:174\ngithub.com/pingcap/parser/terror.(*Error).GenWithStackByArgs\n\t/root/code/pkg/mod/github.com/pingcap/parser@v0.0.0-20200810083003-f0edf4170630/terror/terror.go:255\ngithub.com/pingcap/tidb/ddl.checkTooLongTable\n\t/data/tidb/src/github.com/pingcap/tidb/ddl/ddl_api.go:224\ngithub.com/pingcap/tidb/ddl.checkTableInfoValidExtra\n\t/data/tidb/src/github.com/pingcap/tidb/ddl/ddl_api.go:1356\ngithub.com/pingcap/tidb/ddl.(*ddl).CreateTableWithInfo\n\t/data/tidb/src/github.com/pingcap/tidb/ddl/ddl_api.go:1644\ngithub.com/pingcap/tidb/ddl.(*ddl).CreateTable\n\t/data/tidb/src/github.com/pingcap/tidb/ddl/ddl_api.go:1597\ngithub.com/pingcap/tidb/executor.(*DDLExec).executeCreateTable\n\t/data/tidb/src/github.com/pingcap/tidb/executor/ddl.go:195\ngithub.com/pingcap/tidb/executor.(*DDLExec).Next\n\t/data/tidb/src/github.com/pingcap/tidb/executor/ddl.go:92\ngithub.com/pingcap/tidb/executor.Next\n\t/data/tidb/src/github.com/pingcap/tidb/executor/executor.go:269\ngithub.com/pingcap/tidb/executor.(*ExecStmt).handleNoDelayExecutor\n\t/data/tidb/src/github.com/pingcap/tidb/executor/adapter.go:502\ngithub.com/pingcap/tidb/executor.(*ExecStmt).handleNoDelay\n\t/data/tidb/src/github.com/pingcap/tidb/executor/adapter.go:384\ngithub.com/pingcap/tidb/executor.
~~~



- ALTER table t12 ADD key ``(a);

~~~

[2020/09/11 14:31:23.488 +08:00] [INFO] [conn.go:869] [dispatch] [conn=3] [data:="ALTER table t12 ADD key ''(a)"]
[2020/09/11 14:31:23.489 +08:00] [WARN] [session.go:1099] ["parse SQL failed"] [conn=3] [error="line 1 column 26 near \"''(a)\" "] [SQL="ALTER table t12 ADD key ''(a)"]
[2020/09/11 14:31:23.489 +08:00] [ERROR] [misc.go:167] ["syntax error"] [error="line 1 column 26 near \"''(a)\" "]
[2020/09/11 14:31:23.489 +08:00] [ERROR] [conn.go:744] ["command dispatched failed"] [conn=3] [connInfo="id:3, addr:127.0.0.1:53444 status:10, collation:utf8_general_ci, user:root"] [command=Query] [status="inTxn:0, autocommit:1"] [sql="ALTER table t12 ADD key ''(a)"] [txn_mode=PESSIMISTIC] [err="[parser:1064]You have an error in your SQL syntax; check the manual that corresponds to your TiDB version for the right syntax to use line 1 column 26 near \"''(a)\" "]

mysql> CREATE TABLE t10(x INT, KEY ``(x));
ERROR 1280 (42000): Incorrect index name 
ErrWrongNameForIndex
~~~



- ALTER table t12 ADD key ``(a);

mysql> ALTER table t12 ADD key ``(a);
Query OK, 0 rows affected (0.47 sec)

## 动手



~~~mysql
tail -f /data/tidb/tiup/tidb-deploy/tidb-4000/log/tidb.log
create table tt (a int, b int ,key(a));

drop table tt;

SHOW INDEX FROM tt;
alter table tt add index(a,b);
~~~



