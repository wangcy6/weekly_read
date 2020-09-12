#!/bin/bash
for (i=1; i<=1000; i++)
do
	 mysql -h 127.0.0.1 -P 4000 -u root  -p123456  -e " insert into test.t2 values($i, 1001-$i, $i);"
done