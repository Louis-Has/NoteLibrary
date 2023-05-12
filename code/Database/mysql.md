1.  sort
2.  limit
3.  like
4.  avg,count,max,min,sum
5.  索引
	1.  场景 order by ，join on
	2.  unique ，index
	3.  not null
	4.  联合索引

6.  select * from tableA join tableB on a.name = b.name
7.  SELECT name, COUNT(\*) FROM employee_tbl GROUP BY name WITH ROLLUP;
8.  MySQL Innodb 事物 Transaction
	1.  begin;
	2.  commit;
	3.  rollback;

9.  MyISAM Innodb
	1.  事务 外键 哈希索引

10.  SQL优化
	1.  slow_query_log
	2.  not null
	3.  show processlist
	4.  读写分离
	5.  in > between
	6.  in > exists
	7.  or > union 组合查询
	8.  where 1=1 > 去掉
	9.  where 联合索引 按顺序
	10.  避免隐式类型转换
	11.  join 小表在前
	12.  用表 的 别名
	13.  HAVING > where
	14.  where 从左到右的顺序
	15.  inset 多条合并插入
	16.  order by null
	17.  union > union all
	18.  delete > truncate