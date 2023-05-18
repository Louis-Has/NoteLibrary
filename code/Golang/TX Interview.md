F
##### go的调度
 - 通过在 GM 中间加一层 P 实现在线程上的本地调度器
- [**M，G实际上是由M通过P来进行调度运行的**，但是在G的层面来看，**P提供了G运行所需的一切资源和环境**](obsidian://open?vault=NoteLibrary&file=code%2FGolang%2FGPM)
- M代表真正执行计算的资源，在绑定有效的P后，进入schedule循环；而schedule循环的机制大致是**从Global队列、P的Local队列以及wait队列中获取G**，**切换到G的执行栈上并执行G的函数**，**调用goexit做清理工作并回到M**，如此反复。
- 每一个goroutine是一个独立的执行单元，**goroutine的栈采取了动态扩容方式， 初始时仅为2KB，随着任务执行按需增长**，**G存储Goroutine的运行堆栈、状态以及任务函数**。
##### go struct能不能比较
-  可比较：_Integer_，_Floating-point_，_String_，_Boolean_，_Complex(复数型)_，_Pointer_，_Channel_，_Interface_，_Array_
-  不可比较：_Slice_，_Map_，_Function_
- 所以 struct 当结构不包含不可直接比较成员变量时可直接比较，否则不可直接比较
- reflect.DeepEqual 函数用来判断两个值是否深度一致
##### go defer（for defer）
- 被defer的函数执行顺序满足LIFO原则，后defer的先执行。
- 被`defer`的函数或者方法如果存在多级调用，只有最后一个函数或方法会被`defer`到函数return或者panic之前执行
- 被defer的函数或方法的参数的值在执行到defer语句的时候就被确定下来了。
- defer后面跟的必须是函数或者方法调用，defer后面的表达式不能加括号。
- 被defer的函数可以对defer语句所在的函数的命名返回值做读取和修改操作。
##### select可以用于什么
- -   `select` 主要用于**监听多个`channel`是否可以收发消息**，`select会尝试执行case语句`。当任何一个case满足条件则会执行，若没有可执行的case，就会执行**default分支**。如果default也不满足，程序会跳出select语句块。
##### context包的用途
- 主要用来在 goroutine 之间**传递上下文信息**，包括：请求特定数据、取消信号以及处理请求的截止日期。在多个 Goroutine 组成的树中同步取消信号以减少对资源的消耗和占用。
- 协程之间：需要共享一些全局变量、有共同的 deadline 等，而且可以同时被关闭。
- [Context](https://www.topgoer.cn/docs/golang/chapter11-10)
##### client如何实现长连接
-  TCP协议的`KeepAlive`机制
- 长：数据库的连接
- 短：web ajax 请求
##### -   主协程如何等其余协程完再操作
- wg sync.WaitGroup
	- wg.Add(2)
	- wg.Done()
	- wg.Wait()
##### -   slice，len，cap，共享，扩容
- 当slice的`len==cap`后，再向slice中追加元素时，会发生扩容
- [你不知道的 Go 之 slice](https://darjun.github.io/2021/05/09/youdontknowgo/slice/)
##### -   map如何顺序读取
- map底层使用hash表实现,插入数据位置是随机的
- 将 map 的 key 全部拿出来，放到一个数组中，
- 然后对这个数组排序后对有序数组遍历，再间接取 map 里的值
##### -   实现set
- set := make(map[string]void)
##### -   实现消息队列（多生产者，多消费者）
- 
##### -   大文件排序
##### -   基本排序，哪些是稳定的
##### -   http get跟head
##### -   http 401,403
##### -   http keep-alive
##### -   http能不能一次连接多次请求，不等后端返回
##### -   tcp与udp区别，udp优点，适用场景
##### -   time-wait的作用
##### -   数据库如何建索引
##### -   孤儿进程，僵尸进程
##### -   死锁条件，如何避免
##### -   linux命令，查看端口占用，cpu负载，内存占用，如何发送信号给一个进程
##### -   git文件版本，使用顺序，merge跟rebase

  

S
##### -   项目是实现爬虫的流程
##### -   爬虫如何做的鉴权吗
##### -   怎么实现的分布式爬虫
##### -   电商系统图片过多会造成带宽过高，如何解决
##### -   micro服务发现
##### -   mysql底层有哪几种实现方式
##### -   channel底层实现
##### -   java nio和go 区别
##### -   读写锁底层是怎么实现的
##### -   go-micro 微服务架构怎么实现水平部署的，代码怎么实现的
##### -   micro怎么用
##### -   怎么做服务员的
##### -   mysql索引为什么要用B+树？
##### -   mysql语句性能评测？
##### -   服务员发现有哪些机制
##### -   raft算法是那种一致性算法
##### -   raft有什么特点
##### -   当go服务部署到线上了，发现有内存泄露，该怎么处理
##### -   还有一些非常底层的问题

