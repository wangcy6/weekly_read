-- sysbench --mysql-socket=/data/mysql_3309/mysql.sock --test=tests/db/test.lua --mysql-user=root --num-threads=12 --report-interval=10 --rand-type=uniform --max-time=30 --max-requests=0 --percentile=99 --mysql-db=test run
-- sysbench --config-file=./sysbench-thread-1.cfg --test=./join_test_01.lua  run
-- Called by sysbench one time to initialize this script
function thread_init(thread_id)
   -- set_vars()
   --- 连接数据库
   db_connect()
end
-- Called by sysbench for each execution
function event(thread_id)
   local table_name
   local rs
  for i=1, 10000 do
      rs = db_query("select * from t1,t2 where t1.a=t2.a")
  end
end