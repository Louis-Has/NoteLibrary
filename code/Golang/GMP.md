### 协程来提高CPU利用率

线程(thread)
协程(co-routine)
	线程由CPU调度是抢占式的，*协程由用户态调度是协作式的*，一个协程让出CPU后，才执行下一个协程。

### Go语言的协程goroutine

**Go为了提供更容易使用的并发方法，使用了goroutine和channel**。goroutine来自协程的概念，让一组可复用的函数运行在一组线程之上，即使有协程阻塞，该线程的其他协程也可以被`runtime`调度，转移到其他可运行的线程上。最关键的是，程序员看不到这些底层的细节，这就降低了编程的难度，提供了更容易的并发。

Go中，协程被称为goroutine，它非常轻量，一个goroutine只占几KB，并且这几KB就足够goroutine运行完，这就能在有限的内存空间内支持大量goroutine，支持了更多的并发。虽然一个goroutine的栈只占几KB，但实际是可伸缩的，如果需要更多内容，`runtime`会自动为goroutine分配。

### Goroutine调度器的GMP模型的设计思想

在新调度器中，除了**M线程(thread)** 和 **G协程(goroutine)**，又引进了**P处理器(Processor)**。

1. P的数量：
	-   由启动时环境变量`$GOMAXPROCS`或者是由`runtime`的方法`GOMAXPROCS()`决定。这意味着在程序执行的任意时刻都只有`$GOMAXPROCS`个goroutine在同时运行。
2. M的数量:
	-  go语言本身的限制：go程序启动时，会设置M的最大数量，默认10000.但是内核很难支持这么多的线程数，所以这个限制可以忽略。
	-  runtime/debug中的SetMaxThreads函数，设置M的最大数量
	-  一个M阻塞了，会创建新的M。


