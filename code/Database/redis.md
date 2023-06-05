1.  string
	1.  Set 
		1. 基本格式：\[业务名称]:\[数据名]:\[id]
		2. SetNX 不存在则设置 
			1. 用来分布式锁
			2. Del 释放锁
		3. Setex 设置过期时间 分布式锁常用
	3.  incr incrby decr decrby

3.  list列表类型
	1.  1,最新消息排行等功能(比如朋友圈的时间线) 2,消息队列

4.  hash哈希表类型
	1.  存储、读取、修改用户属性

5.  set集合类型
	1.  1、共同好友 2、利用唯一性,统计访问网站的所有独立ip 3、好友推荐时,根据tag求交集,大于某个阈值就可以推荐

6.  zset有序集合类型
	1.  1、排行榜 2、带权重的消息队列

7.  fluchdb 清空


### redis常用命令

### pipelines(管道)
- pipe := rdb.Pipeline()
- cmds, err := pipe.Exec(ctx)

### redis事务
- 不保证原子性
- 开启事务(multi) 命令入队 执行事务(exec)  取消事务：discard

### redis持久化
- rdb方式（redis database）
	- 先将数据读取到一个临时文件，持久化都结束了，再替换上个版本的持久化文件
	- 不进行i/o操作
	- 可能存在数据丢失
- aof方式(append only file)
	- 将所有命令都记录下来，恢复的时候再把所有命令都全部执行一遍。
	- 修复速度慢
		- aof 默认文件追加，文件会越来越大，如果文件太大，fork一个新的进程进行重写
- 持久化配置优化：
	1. 用来做缓存的Redis实例，尽量不要开启持久化功能
	2. 建议关闭RDB，只使用AOF持久化
	3. 利用脚本定期在Slave节点做RDB，实现数据备份
	4. 设置合理的`rewrite`阈值，避免频繁`bgrewrite`
	5. 配置`no-appendfsync-on-rewrite=yes`，禁止在`rewrite`期间做AOF，避免因AOF引起的阻塞


### 缓存穿透
1. 拦截非法参数
2. 将数据库不存在的数据也缓存下来：缺点是会有额外的内存消耗，而且可能造成短期的不一致
3. 使用布隆过滤器,保证一般访问体验

### 缓存雪崩
1. 给不同的key设置随机的TTL
2. 利用Redis集群的高可用性
3. 给缓存的业务添加降级限流策略
4. 给业务增加多级缓存

### 缓存击穿
1. 永不过期
2. 互斥锁：当发现缓存过期，需要从数据库获取数据时，先获取锁，获取锁之后才访问数据库；如果没有获取锁，则休眠一段时间再次重试在缓存中获取数据，没有的话，再次尝试获取锁；缺点是线程需要等待，性能会收到影响，而且可能有死锁的风险
2. 逻辑过期：将热key过期后的数据也缓存起来，作为老数据，当新数据失效时，返回老数据，通过子进程获取互斥锁，新数据放到缓存中，然后释放锁。其他的进程没有访问到老数据也没有获取到锁时，则直接返回老数据；解决了线程等待的问题，性能好，缺点是不保证一致性，有额外的内存，而且实现复杂

### 三种集群方案

- 主从复制模式
	- 一个是读写分离，分担 "master" 的读写压力
	- 一个是方便做容灾恢复
- Sentinel（哨兵）模式
	- 主从可以自动切换，系统更健壮，可用性更高
- Cluster 模式
	- 所有的 redis 节点彼此互联(PING-PONG机制)，内部使用二进制协议优化传输速度和带宽。
	- 节点的 fail 是通过集群中超过半数的节点检测失效时才生效。
	- 客户端与 Redis 节点直连，不需要中间代理层.客户端不需要连接集群所有节点，连接集群中任何一个可用节点即可。

### Redis分布式锁
1. 高并发下的超卖问题
2. [redsync/v4](https://github.com/go-redsync/redsync)
	1. 使用 SetNX(key string, value interface{}, expiration time.Duration) 实现分布式锁
	2. 加入 random(uuid) 保证 unlock 的是相应的锁。
	3. 开个后台线程，延长锁的时间。
	4. 使用 lua 脚本保证原子性 
	5. Redlock 算法
		1. tfinal = texpect − tdelta
		2. 从大多数 Redis 节点（即：超过 Quorum>=N2+1 台）成功获取到了锁
		3. 获取锁失败了应该立即向所有 Redis 节点发起释放锁的操作
	6. Zookeeper


1. [# 分布式锁：使用 Redis 实现](https://pandaychen.github.io/2020/06/01/REDIS-DISTRIBUTED-LOCK/)
2. [# Golang中的本地锁和分布式锁](https://www.xiaoyeshiyu.com/2022/lock/)
3. [# Redis学习笔记之实用篇](https://www.xiaoyeshiyu.com/2022/Redis-adv/)
4. [# Redis基本数据类型代码示例](https://www.cnblogs.com/jiujuan/p/17215125.html)