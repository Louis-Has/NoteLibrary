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
- main
	-  ch := make(chan int)
	- go producer("生产者1", ch)
	- go consumer("消费者1", ch)
##### -   大文件排序
- 拆分成小文件
- 逐个排序
- 考虑分治法，多线程加速
##### -   基本排序，哪些是稳定的
- 稳定：
	- 冒泡排序
	- 插入排序
	- 归并排序
- 不稳定
	- 选择排序
	- 希尔排序
	- 快速排序
	- 堆排序
##### -   http get跟head
- HEAD方法与 GET 方法类似，也是请求从服务器获取资源，服务器的处理机制也是一样的，但服务器不会返回请求的实体数据，只会传回响应头，也就是资源的“元信息”。
##### -   http 401,403
- 401 认证错误
- 403 没有被授权
##### -   http keep-alive
- 使客户端到服务器端的连接持续有效，建立长连接
##### -   http能不能一次连接多次请求，不等后端返回
- HTTP 1.1 版本使用长连接
- HTTP 2.0 版本，支持复用
##### -   tcp与udp区别，udp优点，适用场景[总结](https://www.developers.pub/article/1026813)
- tcp
	- 通过严格握手过程保证可靠
	- HTTP SSH FTP SMTP
- udp
	- 效率高，可以保证低延迟
	- 流媒体 实时游戏 物联网
##### -   time-wait的作用
- time-wait就是四次挥手后主动关闭方的状态
- net.ipv4.tcp_tw_recycle
- [为什么 TCP 协议有 TIME_WAIT 状态](https://draveness.me/whys-the-design-tcp-time-wait/)
##### -   数据库如何建索引
- CREATE [UNIQUE] INDEX [indexName] ON mytable;
##### -   孤儿进程，僵尸进程
- 孤儿：父进程退出，而子进程还在运行
- 僵尸：子进程退出，而父进程并没有调用wait或waitpid获取子进程的状态信息，那么子进程的进程描述符仍然保存在系统中。
##### -   死锁条件，如何避免
- **互斥条件**是指多个线程不能同时使用同一个资源。
- **持有并等待条件**是指，当线程 A 已经持有了资源 1，又想申请资源 2，而资源 2 已经被线程 C 持有了，所以线程 A 就会处于等待状态
- **不可剥夺条件**是指，当线程已经持有了资源 ，在自己使用完之前不能被其他线程获取
- **环路等待条件**指的是，在死锁发生的时候，两个线程获取资源的顺序构成了环形链。
- 避免
	- **使用资源有序分配法，来破环环路等待条件**
##### -   linux命令，查看端口占用，cpu负载，内存占用，如何发送信号给一个进程
- 查看端口占用 
	- lsof -i:80
	- netstat -tunlp | grep 端口号
- cpu负载
	- top
- 内存占用
	- vmstat -s
- 发送信号给一个进程
	- kill -15 pid
  

S
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

