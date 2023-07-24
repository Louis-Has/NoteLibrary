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

### 存储引擎

MyISAM 和 InnoDB 是 MySQL 中两种常用的存储引擎（Storage Engine），用于管理数据的存储和访问。它们有不同的特点和适用场景。

1. MyISAM： MyISAM 是 MySQL 的默认存储引擎（在 MySQL 5.5.5 版本之前）。它以较简单的方式存储数据，对于读操作具有较好的性能，适用于大量的读操作和少量的写操作的场景。
    
    主要特点：
    
    - 不支持事务：MyISAM 不支持事务，这意味着它不支持事务的原子性、一致性、隔离性和持久性（ACID 特性）。
    - **表级锁**：MyISAM 使用表级锁，这意味着在执行写操作时会锁定整个表，可能导致并发写操作的性能瓶颈。
    - **全文索引**：MyISAM 支持全文索引，适用于全文搜索的场景。
    
    由于 MyISAM 不支持事务和使用表级锁，不建议在高并发、写操作频繁的业务场景中使用 MyISAM 引擎。
    
2. InnoDB： InnoDB 是 MySQL 中另一种常用的存储引擎。它支持事务和行级锁，提供了更好的数据完整性和并发性，适用于高并发和频繁写入的业务场景。
    
    主要特点：
    
    - **支持事务**：InnoDB 支持事务，允许用户实现事务的原子性、一致性、隔离性和持久性（ACID 特性）。
    - **行级锁**：InnoDB 使用行级锁，可以在并发读写操作时避免表级锁带来的性能瓶颈，提高了并发性能。
    - 外键支持：InnoDB 支持外键约束，可以保证数据的完整性。
    
    InnoDB 是 MySQL 5.5.5 版本及以后的默认存储引擎。对于大多数应用来说，InnoDB 引擎通常是更好的选择，特别是对于需要支持事务和并发写入的应用场景。
    

在选择存储引擎时，应根据应用的需求和特点来选择合适的引擎。对于读多写少的简单查询场景，MyISAM 可能会有更好的性能。而对于需要事务支持和高并发写入的应用，InnoDB 是更稳定和可靠的选择。

### Transaction
1.  begin;
2.  commit;
3.  rollback;

当面试中涉及 MySQL 事务的问题时，通常会涵盖数据库事务的基本概念、事务的特性（ACID）、并发控制和隔离级别等方面。以下是一些可能出现在 MySQL 事务相关面试题中的问题：

1. 什么是数据库事务？ 回答：数据库事务是一组被视为单个逻辑单元的数据库操作，要么全部成功执行（提交），要么全部回滚（撤销），从而**确保数据的一致性和完整性**。
    
2. 事务的 ACID 特性是什么？ 回答：ACID 是事务的四个特性，分别是原子性（Atomicity）、一致性（Consistency）、隔离性（Isolation）和持久性（Durability）。原子性表示事务中的所有操作要么全部成功，要么全部失败回滚。一致性确保事务使数据库从一个一致性状态转换到另一个一致性状态。隔离性保证事务之间互不干扰，使并发执行的事务相互隔离。持久性确保一旦事务提交，其对数据库的修改将永久保存，即使系统崩溃也不会丢失。
    
3. MySQL 默认使用的事务隔离级别是什么？ 回答：MySQL 默认使用的事务隔离级别是 REPEATABLE READ。这是为了保证事务的可重复读性，即在同一个事务中多次读取同一数据，得到的结果都是一样的。
    
4. 什么是脏读（Dirty Read）、幻读（Phantom Read）和不可重复读（Non-repeatable Read）？ 回答：这些都是并发事务执行时可能出现的问题。
    
    - 脏读是指一个事务读取了另一个事务未提交的数据。
    - 幻读是指一个事务读取了另一个事务已提交的新增数据，导致之前的查询结果和之后的查询结果不一致。
	    - 使用 SERIALIZABLE 隔离级别：
			`SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;`
	    - 使用锁定读（FOR UPDATE）：
			`SELECT * FROM table_name WHERE column_name = 'value' FOR UPDATE;`
    - 不可重复读是指一个事务内两次读取同一数据，但两次读取的结果不一致，可能是因为另一个并发事务修改了数据。
5. 如何解决并发事务的问题？ 回答：可以通过设置不同的事务隔离级别来解决并发事务的问题。MySQL 支持四种事务隔离级别：READ UNCOMMITTED、READ COMMITTED、REPEATABLE READ 和 SERIALIZABLE。每个隔离级别都有不同的特点和用途，可以根据实际场景选择合适的隔离级别。
    

这些问题只是可能涉及 MySQL 事务的一部分，面试中可能会涵盖更多的细节和场景。在准备面试时，建议深入理解数据库事务的基本概念和 ACID 特性，以及各种隔离级别的特点和应用场景。

### 事务隔离级别

在 MySQL 中，可以通过设置合适的事务隔离级别来解决脏读问题。事务隔离级别包括 READ UNCOMMITTED、READ COMMITTED、REPEATABLE READ 和 SERIALIZABLE。设置事务隔离级别为 READ COMMITTED 或更高级别，可以避免脏读的问题。

- READ UNCOMMITTED
- READ COMMITTED：每个查询只能读取到已经提交的数据，**避免了脏读问题**。
- REPEATABLE READ：在**同一个事务内多次读取同一数据，得到的结果都是一样的**，避免了脏读和不可重复读问题。
- SERIALIZABLE：最高隔离级别，保证了事务的串行执行，**避免了脏读、不可重复读和幻读问题**。

设置事务隔离级别的方式为：
```sql
SET TRANSACTION ISOLATION LEVEL <isolation_level>;
```

### 锁机制

MySQL 的锁机制是用于实现并发控制的重要组成部分，确保在多个事务同时访问数据库时数据的一致性和完整性。MySQL 支持多种类型的锁，这些锁可以在事务执行过程中对数据进行加锁和解锁，以控制数据的访问权限。

主要的锁类型包括：

1. **共享锁（Shared Lock，也称为读锁）**：
    - 允许多个事务同时持有共享锁，并且可以共享同一份数据。
    - 共享锁用于防止其他事务对数据进行修改，但允许其他事务读取数据。
    - 适用于并发读取的场景。
2. **排他锁（Exclusive Lock，也称为写锁）**：
    - 一次只能有一个事务持有排他锁。
    - 排他锁用于防止其他事务对数据进行读取和修改，保证只有一个事务能够修改数据。
    - 适用于并发写入的场景。

MySQL 中的锁可以通过以下方式进行管理：

1. 表级锁（Table-level Lock）：
    - 表级锁是最粗粒度的锁，对整个表进行加锁。
    - 使用 LOCK TABLES 语句可以对表进行加锁，防止其他事务对整个表进行读写操作。
    - 一般情况下，表级锁的并发性较差，会导致性能瓶颈。
2. **行级锁（Row-level Lock）**：
    - 行级锁是最细粒度的锁，对数据库中的每一行数据进行加锁。
    - InnoDB 存储引擎支持行级锁，通过在事务中使用 SELECT ... FOR UPDATE 或 SELECT ... LOCK IN SHARE MODE 可以对查询的行进行加锁。
    - 行级锁的并发性较好，可以减少锁的竞争，提高数据库的并发性能。
3. 页级锁（Page-level Lock）：
    - 页级锁对数据库中的每一页数据进行加锁。
    - 在某些存储引擎中可能会使用页级锁作为粒度介于表级锁和行级锁之间的锁。

使用合适的锁机制可以确保并发事务之间的数据访问是正确、安全和有效的。在实际开发中，需要根据业务需求和数据库引擎的特性选择适合的锁策略，以保证数据库的性能和数据完整性。

#### 几种常用的锁机制及其使用方式：

1. 共享锁（Shared Lock）： 共享锁用于保证多个事务可以同时读取一份数据，但不允许并发事务修改数据。可以通过 **`LOCK IN SHARE MODE`** 语句在 SELECT 查询中使用共享锁：
    
    ```sql
SELECT * FROM table_name WHERE column_name = 'value' LOCK IN SHARE MODE;
    ```
    
    当事务持有共享锁时，其他事务也可以持有共享锁，但不能持有排他锁。
    
2. 排他锁（Exclusive Lock）： 排他锁用于保证只有一个事务可以修改数据，其他事务不能读取和修改数据。可以通过 **`FOR UPDATE`** 语句在 SELECT 查询中使用排他锁：
    
    ```sql
SELECT * FROM table_name WHERE column_name = 'value' FOR UPDATE;
    ```
    
    当事务持有排他锁时，其他事务不能持有共享锁或排他锁。
    
3. 行级锁（Row-level Lock）： 行级锁是最细粒度的锁，它对数据库中的每一行数据进行加锁。在 InnoDB 存储引擎中，默认就是使用行级锁。在事务中，可以通过 `SELECT ... FOR UPDATE` 或 `SELECT ... LOCK IN SHARE MODE` 语句对查询的行进行加锁。
    
4. 表级锁（Table-level Lock）： 表级锁是最粗粒度的锁，它对整个表进行加锁。可以通过 `LOCK TABLES` 和 `UNLOCK TABLES` 语句对表进行加锁和解锁。
    
```sql
LOCK TABLES table_name [AS alias] {READ | WRITE}; -- 执行操作... UNLOCK TABLES;
```
    
    表级锁的使用较少，一般情况下推荐使用行级锁。
    

需要注意的是，在使用锁机制时，要注意避免死锁（Deadlock）的情况。死锁是指两个或多个事务相互等待对方释放锁，导致无法继续执行的情况。为了避免死锁，需要合理地设计事务逻辑和锁的使用顺序。

#### 死锁（Deadlock）

死锁是在并发环境中发生的一种特殊情况，它指的是两个或多个事务相互持有对方所需要的资源，从而导致所有事务都无法继续执行，被永久地阻塞在等待对方释放资源的状态。简单来说，死锁是由于资源竞争导致的一种僵局，使得系统无法继续进行。

### SQL优化
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