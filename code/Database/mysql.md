
6.  select * from tableA join tableB on a.name = b.name
7.  SELECT name, COUNT(\*) FROM employee_tbl GROUP BY name WITH ROLLUP;

1.  MySQL Innodb 事物 Transaction
	1.  begin;
	2.  commit;
	3.  rollback;

2.  MyISAM Innodb
	1.  事务 外键 哈希索引

3.  SQL优化
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



### SELECT语句 - 执行顺序

##### 1. FROM子句：首先，执行FROM子句，指定要查询的表（或表的组合）。



##### 2. WHERE子句：如果有WHERE子句，查询会根据WHERE条件对FROM子句中的表进行筛选，只选择满足条件的行。



##### 3. GROUP BY

如果有GROUP BY子句，查询会按照指定的列进行分组，将数据分成多个组。

```sql
SELECT cash,count(id) sum FROM author_mes GROUP BY cash  
```

###### ONLY_FULL_GROUP_BY

不赞成sql_mode去掉ONLY_FULL_GROUP_BY
1. MySQL5.7 官方的默认值
2. SQL SERVER、ORACLE、Postgres 规范是一致的，遵循sql-92标准。自带 ONLY_FULL_GROUP_BY 约束，认为违反这个规则的SQL都是不合法的。
3. 可能会有数据不一致的问题 important！

###### HAVING
HAVING 子句用于在 GROUP BY 子句之后对分组后的结果进行筛选。它允许使用聚合函数和条件来过滤分组后的数据。

```sql
SELECT cash,count(id) sum FROM author_mes GROUP BY cash  HAVING cash >100
```


##### 6. SELECT子句：在前面的步骤筛选和分组后，执行SELECT子句，选择要查询的列或表达式，并计算任何聚合函数。



##### 7. 子查询（Subquery）



##### 8. 联合查询（JOIN）
###### ON


##### 9. ORDER BY子句：如果有ORDER BY子句，查询会按照指定的列对结果进行排序。

使用 ORDER BY 子句可以对查询结果进行排序。ORDER BY 子句通常放在 SELECT 语句的末尾，用于按照指定的列进行升序（ASC）或降序（DESC）排序。
```sql
SELECT id,author,cash FROM author_mes ORDER BY cash ,id DESC
```

##### 10. LIMIT
LIMIT 子句用于限制查询结果返回的行数。它可以帮助你控制查询的结果集大小。

```sql
select _column,_column from _table [where Clause] [limit N][offset M]
```

##### 11. LIKE
LIKE 是一个用于模糊匹配的运算符，通常用于在字符串列中搜索符合特定模式的值。它可以与通配符一起使用，来进行模式匹配的操作。

1. `%`：表示零个或多个字符的任意序列。 例如，使用 `%` 通配符匹配以 "a" 开头的任意字符串：
    
```sql
SELECT *
FROM table_name
WHERE column_name LIKE 'a%';
```
    
2. `_`：表示一个单个字符。 例如，使用 `_` 通配符匹配以 "ab" 开头的两个字符的字符串：
    
```sql
SELECT *
FROM table_name
WHERE column_name LIKE 'ab_';
```
    
3. `[charlist]` 或 `[^charlist]`：表示一个字符集合或不在字符集合中的字符。 例如，使用 `[charlist]` 通配符匹配以 "a" 或 "b" 开头的字符串：
    
```sql
SELECT *
FROM table_name
WHERE column_name LIKE '[ab]%';
```
    
4. `ESCAPE`：用于指定转义字符，用于匹配特殊字符。 例如，使用 `ESCAPE` 关键字指定转义字符为 ""，来匹配以 "%" 字符开头的字符串：
    
```sql
SELECT *
FROM table_name
WHERE column_name LIKE '\% %' ESCAPE '\';
```
    

需要注意的是，LIKE 运算符是大小写敏感的，所以要注意在模式匹配时的大小写问题。


### MySQL 内置函数

1. 字符串函数：
    - **CONCAT**：用于将多个字符串连接在一起。
    - LENGTH：返回字符串的长度。
    - SUBSTRING：提取子字符串。
    - **UPPER** 和 **LOWER**：将字符串转换为大写或小写。

2. 数值函数：
    - **ABS**：返回一个数的绝对值。
    - **ROUND** 和 TRUNCATE：用于数值的四舍五入或截断。
    - **MIN** 和 **MAX**：返回一组数中的最小或最大值。
    - **AVG** 和 **SUM**：计算一组数的平均值和总和。

3. 日期和时间函数：
    - **NOW** 和 CURRENT_TIMESTAMP：返回当前日期和时间。
    - **DATE** 和 **TIME**：提取日期或时间部分。
    - DATE_FORMAT：格式化日期和时间。

4. 条件函数：
    - **IF** 和 CASE：用于条件判断和分支控制。
    - COALESCE：返回第一个非空表达式。

5. 聚合函数：
    - **COUNT**：计算满足条件的行数。
    - GROUP_CONCAT：将分组结果中的值连接为一个字符串。
    - SUM、AVG、MIN、MAX：用于对分组数据进行聚合计算。

6. 数据类型转换函数：
    - CAST 和 CONVERT：用于数据类型的转换。
    - STR_TO_DATE 和 DATE_FORMAT：用于日期和时间格式的转换。

### 索引

索引类型：

- 主键索引（**Primary Key Index**）：用于唯一标识表中的每一行，自动创建的索引。
- 唯一索引（**Unique Index**）：确保索引列的值是唯一的。
- 普通索引（**Non-Unique Index**）：用于加快查询速度，但允许索引列中的重复值。
- 全文索引（**Full-Text Index**）：用于全文搜索，适用于对文本内容进行搜索的场景。

索引的优化
	1.  场景 order by ，join on
	2.  unique ，index
	3.  not null
	4.  联合索引

