

### 准备数据
/data/tidb/tiup/tidb-deploy/tidb-4000/log

mysql -h 127.0.0.1 -P 4000 -u root  -p 

explain select * from teacher where age >=18


CREATE TABLE `teacher` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(32) NOT NULL,
  `age` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4;


CREATE TABLE `t` (
  `id` int(11) NOT NULL,
  `a` int(11) DEFAULT NULL,
  `b` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `idx_a` (`a`)
) ENGINE=InnoDB;

INSERT  INTO teacher(id,NAME,age) VALUES (1,'seven',18);
INSERT  INTO teacher(id,NAME,age) VALUES (2,'qingshan',20);



~~~
mysql -u root -p

create table t1(id int primary key, a int, b int, index(a));
create table t2 like t1;
drop procedure idata;
delimiter ;;
create procedure idata()
begin
  declare i int;
  set i=1;
  while(i<=1000)do
    insert into t1 values(i, 1001-i, i);
    set i=i+1;
  end while;
  
  set i=1;
  while(i<=1000000)do
    insert into t2 values(i, i, i);
    set i=i+1;
  end while;

end;;
delimiter ;
call idata()

~~~
-  34 | 到底可不可使用join？
~~~
CREATE TABLE `t2` (
  `id` int(11) NOT NULL,
  `a` int(11) DEFAULT NULL,
  `b` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `a` (`a`)
) ENGINE=InnoDB;

drop procedure idata;
delimiter ;;
create procedure idata()
begin
  declare i int;
  set i=1;
  while(i<=1000)do
    insert into t2 values(i, i, i);
    set i=i+1;
  end while;
end;;
delimiter ;
call idata();

create table t1 like t2;
insert into t1 (select * from t2 where id<=100)

Index Nested-Loop Join

explain select * from t1 straight_join t2 on (t1.a=t2.a);

Simple Nested-Loop Join
explain select * from t1 straight_join t2 on (t1.a=t2.b);
// Using where; Using join buffer (Block Nested Loop) 

https://www.shangmayuan.com/a/6018885a878e4348a9ecc27c.html

1 表 t1 的数据读入线程内存 join_buffer 中，因为咱们这个语句中写的是 select *，所以是把整个表 t1 放入了内存；
2 扫描表 t2，把表 t2 中的每一行取出来，跟 join_buffer 中的数据作对比，
  知足 join 条件的，做为结果集的一部分返回。
~~~

- mysql -h 127.0.0.1 -P 4000 -u root  -p123456 

~~~

mysql> explain select * from t1 straight_join t2 on (t1.a=t2.a);
+----------------------------------+---------+-----------+----------------------+-----------------------------------------------------------------------------+
| id                               | estRows | task      | access object        | operator info                                                               |
+----------------------------------+---------+-----------+----------------------+-----------------------------------------------------------------------------+
| IndexMergeJoin_32                | 1250.00 | root      |                      | inner join, inner:IndexLookUp_30, outer key:test.t2.a, inner key:test.t1.a  |
| ├─TableReader_49(Build)          | 1000.00 | root      |                      | data:Selection_48                                                           |
| │ └─Selection_48                 | 1000.00 | cop[tikv] |                      | not(isnull(test.t2.a))                                                      |
| │   └─TableFullScan_47           | 1000.00 | cop[tikv] | table:t2             | keep order:false                                                            |
| └─IndexLookUp_30(Probe)          | 1.25    | root      |                      |                                                                             |
|   ├─Selection_29(Build)          | 1.25    | cop[tikv] |                      | not(isnull(test.t1.a))                                                      |
|   │ └─IndexRangeScan_27          | 1.25    | cop[tikv] | table:t1, index:a(a) | range: decided by [eq(test.t1.a, test.t2.a)], keep order:true, stats:pseudo |
|   └─TableRowIDScan_28(Probe)     | 1.25    | cop[tikv] | table:t1             | keep order:false, stats:pseudo                                              |
+----------------------------------+---------+-----------+----------------------+-------------------------------------------------------------

mysql> explain select * from t1 straight_join t2 on (t1.a=t2.a);
+----+-------------+-------+------+---------------+------+---------+-----------+------+-------------+
| id | select_type | table | type | possible_keys | key  | key_len | ref       | rows | Extra       |
+----+-------------+-------+------+---------------+------+---------+-----------+------+-------------+
|  1 | SIMPLE      | t1    | ALL  | a             | NULL | NULL    | NULL      |  100 | Using where |
|  1 | SIMPLE      | t2    | ref  | a             | a    | 5       | test.t1.a |    1 | NULL        |
+----+-------------+-------+------+---------------+------+---------+-----------+------+-------------+
2 rows in set (0.00 sec)


mysql> explain select * from t1 straight_join t2 on (t1.a=t2.b);
+----+-------------+-------+------+---------------+------+---------+------+------+----------------------------------------------------+
| id | select_type | table | type | possible_keys | key  | key_len | ref  | rows | Extra                                              |
+----+-------------+-------+------+---------------+------+---------+------+------+----------------------------------------------------+
|  1 | SIMPLE      | t1    | ALL  | a             | NULL | NULL    | NULL |  100 | NULL                                               |
|  1 | SIMPLE      | t2    | ALL  | NULL          | NULL | NULL    | NULL | 1000 | Using where; Using join buffer (Block Nested Loop) |
+----+-------------+-------+------+---------------+------+---------+------+------+----------------------------------------------------+

explain select  sum(t1.a) from t1;

explain select * from t1,t2 where t1.a=t2.a;