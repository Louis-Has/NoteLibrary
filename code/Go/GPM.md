### 协程来提高CPU利用率

线程(thread)
协程(co-routine)
	线程由CPU调度是抢占式的，*协程由用户态调度是协作式的*，一个协程让出CPU后，才执行下一个协程。

[GMP 模型，为什么要有 P？](https://mp.weixin.qq.com/s?__biz=MzUxMDI4MDc1NA==&mid=2247487503&idx=1&sn=bfc20f81a1c6059ca489733b31a2c63c&chksm=f9040552ce738c4496afffe69893ee6c4a8bfb7a50988f29e2e10b097dca24b9d63dd5177d9d&scene=178&cur_album_id=1751854579329056768#rd)
### Go语言的协程goroutine

**Go为了提供更容易使用的并发方法，使用了goroutine和channel**。goroutine来自协程的概念，让一组可复用的函数运行在一组线程之上，即使有协程阻塞，该线程的其他协程也可以被`runtime`调度，转移到其他可运行的线程上。最关键的是，程序员看不到这些底层的细节，这就降低了编程的难度，提供了更容易的并发。

在Go语言中，每一个goroutine是一个独立的执行单元，相较于每个OS线程固定分配2M内存的模式，**goroutine的栈采取了动态扩容方式， 初始时仅为2KB，随着任务执行按需增长**，最大可达1GB（64位机器最大是1G，32位机器最大是256M），且完全由golang自己的调度器 **Go Scheduler** 来调度。此外，GC还会周期性地将不再使用的内存回收，收缩栈空间。 因此，Go程序可以同时并发成千上万个goroutine是得益于它强劲的调度器和高效的内存模型。

任何用户线程最终肯定都是要交由OS线程来执行的，goroutine（称为G）也不例外，但是G并不直接绑定OS线程运行，而是由Goroutine Scheduler中的 P - Logical Processor （逻辑处理器）来作为两者的『中介』，P可以看作是**一个抽象的资源或者一个上下文**，一个P绑定一个OS线程，在golang的实现里把OS线程抽象成一个数据结构：**M，G实际上是由M通过P来进行调度运行的**，但是在G的层面来看，**P提供了G运行所需的一切资源和环境**，因此在G看来P就是运行它的 “CPU”，由 G、P、M 这三种由Go抽象出来的实现，最终形成了Go调度器的基本结构：

-   G: 表示Goroutine，每个Goroutine对应一个G结构体，**G存储Goroutine的运行堆栈、状态以及任务函数**，可重用。G并非执行体，每个G需要绑定到P才能被调度执行。
-   P: Processor，表示逻辑处理器， 对G来说，P相当于CPU核，**G只有绑定到P(在P的local runq中)才能被调度**。对M来说，P提供了相关的执行环境(Context)，如内存分配状态(mcache)，任务队列(G)等，**P的数量决定了系统内最大可并行的G的数量**（前提：物理CPU核数 >= P的数量），P的数量由用户设置的**GOMAXPROCS**决定，但是不论GOMAXPROCS设置为多大，P的数量最大为256。
-   M: Machine，OS线程抽象，代表着真正执行计算的资源，在绑定有效的P后，进入schedule循环；而schedule循环的机制大致是**从Global队列、P的Local队列以及wait队列中获取G**，**切换到G的执行栈上并执行G的函数**，**调用goexit做清理工作并回到M**，如此反复。M并不保留G状态，这是G可以跨M调度的基础，M的数量是不定的，由Go Runtime调整，为了防止创建过多OS线程导致系统调度不过来，目前默认最大限制为10000个。

 #### GMP模型

![[GMP.png]]


### 实现一个Goroutine Pool

启动服务之时先初始化一个 Goroutine Pool 池，这个Pool维护了一个类似栈的FILO队列 ，里面存放负责处理任务的Worker，然后在client端提交task到Pool中之后，在Pool内部，接收task之后的核心操作是：

1.  检查当前Worker队列中是否有空闲的Worker，如果有，取出执行当前的task；
    
2.  没有空闲Worker，判断当前在运行的Worker是否已超过该Pool的容量，是 — 阻塞等待直至有Worker被放回Pool；否 — 新开一个Worker（goroutine）处理；
    
3.  每个Worker执行完任务之后，放回Pool的队列中等待。

![[Goroutine Pool.png]]

实现了一个高性能的Goroutine Pool，较好地**解决了上述的大规模调度和资源占用的问题**，在执行速度和内存占用方面相较于原生goroutine并发占有明显的优势，尤其是内存占用，因为复用，所以规避了无脑启动大规模goroutine的弊端，可以**节省大量的内存**。

### 参考文章：
1. [GM到GMP，Golang经历了什么？](https://learnku.com/articles/57177)
2. [讲解Go中如何实现一个协程池](https://toutiao.io/posts/e48co5x/preview)
3. [Golang的协程调度器原理及GMP设计思想](https://www.yuque.com/aceld/golang/srxd6d)