str,_ := username.(string) 类型断言

# Function

### 实现set

- set := make(map[string]void)

### 设计一个阻塞队列

在Go语言中，可以使用内置的`channel`类型来设计一个阻塞队列。`channel`本身就具有阻塞和同步的特性，非常适合实现这样的队列。以下是一个简单的阻塞队列实现示例：

```go
package main

import "fmt"

type BlockingQueue struct {
    queue chan interface{}
}

func NewBlockingQueue(capacity int) *BlockingQueue {
    return &BlockingQueue{
        queue: make(chan interface{}, capacity),
    }
}

func (q *BlockingQueue) Enqueue(item interface{}) {
    q.queue <- item
}

func (q *BlockingQueue) Dequeue() interface{} {
    return <-q.queue
}

func main() {
    // 创建容量为3的阻塞队列
    queue := NewBlockingQueue(3)

    // 启动一个消费者协程
    go func() {
        for {
            item := queue.Dequeue()
            fmt.Println("消费:", item)
        }
    }()

    // 生产一些数据并入队
    for i := 1; i <= 5; i++ {
        fmt.Println("生产:", i)
        queue.Enqueue(i)
    }
}
```

在这个例子中，`BlockingQueue`结构体包含一个带有指定容量的`channel`。`Enqueue`方法将元素放入`channel`中，如果`channel`已满，将会阻塞直到有空间可用。`Dequeue`方法从`channel`中取出元素，如果`channel`为空，将会阻塞直到有新的元素可用。

在`main`函数中，我们创建了一个容量为3的阻塞队列，并启动一个消费者协程来消费队列中的元素。然后，我们通过调用`Enqueue`方法向队列中生产一些数据。由于队列的容量是3，其中2个元素会立即被消费，而后续的元素将会阻塞直到有空间可用。

请注意，这只是一个简单的阻塞队列实现示例，实际情况可能需要更多的方法和逻辑来满足具体需求。

### 实现使用字符串函数名，调用函数。

```go
type Animal struct{
    
}

func (a *Animal) Eat(){
    fmt.Println("Eat")
}

func main(){
    a := Animal{}
    reflect.ValueOf(&a).MethodByName("Eat").Call([]reflect.Value{})
    
}
```

### 有三个函数，分别打印"cat", "fish","dog"要求每一个函数都用一个goroutine，按照顺序打印100次。

此题目考察channel，用三个无缓冲channel，如果一个channel收到信号则通知下一个。

```go
var dog = make(chan struct{})
var cat = make(chan struct{})
var fish = make(chan struct{})

func Dog() {
	defer wg.Done()
	<-fish
	fmt.Println("dog")
	dog <- struct{}{}
}

func Cat() {
	defer wg.Done()
	<-dog
	fmt.Println("cat")
	cat <- struct{}{}
}

func Fish() {
	defer wg.Done()
	<-cat
	fmt.Println("fish")
	fish <- struct{}{}
}

var wg sync.WaitGroup

func TestGoroutine(t *testing.T) {

	for i := 0; i < 10; i++ {
		wg.Add(1)

		go Dog()
		go Cat()
		go Fish()
	}
	fish <- struct{}{}

	wg.Wait()
}
```


### 启动 2个groutine 2秒后取消， 第一个协程1秒执行完，第二个协程3秒执行完。

采用`ctx, _ := context.WithTimeout(context.Background(), time.Second*2)`实现2s取消。协程执行完后通过channel通知，是否超时。

```go
package main

import (
	"context"
	"fmt"
	"time"
)

func f1(in chan struct{}) {

	time.Sleep(1 * time.Second)
	in <- struct{}{}

}

func f2(in chan struct{}) {
	time.Sleep(3 * time.Second)
	in <- struct{}{}
}

func main() {
	ch1 := make(chan struct{})
	ch2 := make(chan struct{})
	ctx, _ := context.WithTimeout(context.Background(), 2*time.Second)

	go func() {
		go f1(ch1)
		select {
		case <-ctx.Done():
			fmt.Println("f1 timeout")
			break
		case <-ch1:
			fmt.Println("f1 done")
		}
	}()

	go func() {
		go f2(ch2)
		select {
		case <-ctx.Done():
			fmt.Println("f2 timeout")
			break
		case <-ch2:
			fmt.Println("f2 done")
		}
	}()
	time.Sleep(time.Second * 5)
}
```




# Goroutine 处理并发

### Go语言中处理并发的一些常见选择

1. Goroutine和通道（Goroutine and Channel）：
    - 使用`goroutine`可以轻松地创建并发任务，每个`goroutine`都是一个轻量级的执行单元，由Go运行时进行管理。
    - 使用`channel`可以在`goroutine`之间安全地传递数据，`channel`提供了同步和通信的机制。
    - 这是Go语言并发编程的核心特性，通过`goroutine`和`channel`可以实现高效、安全的并发程序。
2. `sync` 包中的同步原语：
    - Go语言的`sync`包提供了一系列的同步原语，如`WaitGroup`、`Mutex`、`RWMutex`、`Cond`等，用于实现不同类型的并发控制。
    - `WaitGroup`用于等待一组`goroutine`完成任务，`Mutex`和`RWMutex`用于对共享资源进行锁定和解锁，`Cond`用于条件变量的同步等。
3. `select` 语句：
    - `select`语句用于在多个通道上进行非阻塞的选择操作，一旦某个通道有数据可接收或发送，`select`就会执行对应的分支。
    - `select`语句可以用于实现并发选择和多路复用，处理多个通道的同时接收或发送操作。
4. `context` 包：
    - `context`包用于传递请求范围的上下文，可以用于控制和取消一组相关的`goroutine`。
    - 使用`context`可以实现对并发任务的超时控制、取消操作，以及传递请求范围的数据和参数。
5. `atomic` 包：
    - Go语言的`atomic`包提供了原子操作，用于处理共享资源的并发访问。
    - `atomic`包提供了一系列的原子操作函数，如`AddInt32`、`SwapPointer`、`LoadInt64`等，用于原子地读取和修改共享资源。
6. Channel 关闭和 `select` 超时：
    - 使用通道的关闭机制和`select`语句的超时功能，可以实现通知和超时控制。
    - 通过关闭通道或使用`select`的`time.After`，可以向`goroutine`发送信号或设置操作的超时时间。
7. WaitGroup 和 context 的组合使用：
    - 可以使用`WaitGroup`来等待一组`goroutine`的完成，而使用`context`来控制这些`goroutine`的取消和超时。

### Go什么时候发生阻塞

在 Go 中，阻塞通常发生在以下情况下：

1. 通道操作阻塞：当向一个已满的通道发送数据或从一个空的通道接收数据时，通道操作将会阻塞，直到有足够的空间发送或接收数据。
    
2. 互斥锁阻塞：当使用互斥锁进行临界区保护时，如果某个 goroutine 已经获取了锁并且没有释放，其他想要获取该锁的 goroutine 将会被阻塞，直到锁被释放。
    
3. 等待组阻塞：当使用 `sync.WaitGroup` 进行并发任务的等待时，如果还有未完成的任务，调用 `Wait` 方法会导致当前 goroutine 阻塞，直到所有任务完成。
    
4. 定时器阻塞：当使用定时器函数如 `time.Sleep` 或 `time.After` 等时，调用这些函数将会导致当前 goroutine 阻塞，直到定时器时间到达。
    
5. 文件读写阻塞：当进行文件读写操作时，如果文件没有准备好或无法进行读写，读取或写入操作将会阻塞，直到文件准备好或可读写。
    
6. 网络阻塞：在进行网络通信时，例如使用 `net.Dial` 进行连接、`net.Listen` 进行监听等，这些操作可能会因为网络连接的建立或等待请求的到来而阻塞。
    

需要注意的是，Go 的并发模型使用了 goroutine 和通道来实现轻量级的并发和通信，通常情况下并不会直接涉及到阻塞操作。大部分情况下，使用通道和选择语句等机制可以实现非阻塞的并发操作。但在特定的情况下，可能会发生阻塞，需要根据具体的代码和使用场景来分析和处理阻塞的情况。


### go竞态

在 Go 中，竞态（Race Condition）指的是多个 goroutine 并发访问共享资源时可能出现的不确定性行为。竞态条件的发生是由于多个 goroutine 同时读写共享资源，而没有进行正确的同步和互斥操作。

竞态条件可能导致程序出现非预期的结果，例如数据不一致、数据丢失、死锁等问题。在竞态条件下，程序的行为变得不可预测，因为每个 goroutine 的执行顺序和时间是不确定的。

为了避免竞态条件，可以采取以下措施：

1. 互斥锁：使用互斥锁（Mutex）或读写锁（RWMutex）来保护共享资源的读写操作。在访问共享资源之前，获取锁，在完成操作后释放锁，以确保同一时间只有一个 goroutine 访问共享资源。
    
2. 原子操作：使用原子操作来对共享资源进行读写，例如原子加减、原子交换等。原子操作能够确保多个 goroutine 对共享资源的操作是原子性的，避免了竞态条件的发生。
    
3. 通道通信：使用通道进行数据传递和同步，避免直接对共享资源进行读写操作。通过发送和接收操作来实现数据的同步和协调，保证每个操作的顺序和执行时机。
    
4. 等待组：使用等待组（WaitGroup）来协调多个 goroutine 的执行顺序和同步，确保某个操作在其他操作完成之后再执行。
    
5. 原子性检测工具：使用 Go 提供的原子性检测工具，例如 go run -race 命令或使用第三方竞态检测工具，来检测和分析潜在的竞态条件问题。
    

总之，避免竞态条件的关键是确保对共享资源的访问是同步和互斥的。通过合适的锁、原子操作、通道通信和同步机制，可以保证程序的正确性和可靠性，避免竞态条件带来的问题。


### channel 及实现原理

在Go语言中，通道（channel）是用于在多个goroutine之间传递数据的特殊数据结构。Go语言的通道实现是基于CSP（Communicating Sequential Processes）并发模型的一种实现。

通道实现原理主要涉及以下几个方面：

1. **数据结构：** 通道底层实现使用了一个称为 `hchan` 的数据结构来表示。它包含了通道的状态、缓冲区、发送和接收等操作的队列等信息。
    
2. **同步与调度：** 通道的操作会涉及到发送方和接收方的同步。当通道为空或满时，发送操作会阻塞，直到有接收操作使通道变得可用；接收操作也会阻塞，直到有发送操作提供数据。这种同步机制确保了 goroutine 的协调运行。
    
3. **内存分配：** 通道的元素存储在缓冲区中，而通道本身是一个引用类型。通道的创建会分配内存用于存储元素，但通道的复制只会复制引用，不会复制元素。
    
4. **锁与条件变量：** 通道的底层实现使用了互斥锁（Mutex）和条件变量（Cond）来实现并发控制。这些机制确保了对通道数据的安全访问。
    
5. **调度器：** Go 的运行时调度器会根据 goroutine 的状态、通道的可用性等因素来调度 goroutine 的运行。调度器确保了 goroutine 的公平调度，避免了饥饿和死锁。
    

需要注意的是，通道的底层实现在不同的 Go 版本中可能有所不同，而且可能会受到底层硬件架构的影响。通常来说，了解底层实现原理对于一般的 Go 程序员来说并不是必需的，因为标准库提供了高级的通道接口，可以方便地实现通信和同步。

##### channel 死锁的场景

在Go中，死锁通常发生在以下场景：

1. 单向通道的双向使用
2. 无缓冲通道的阻塞
3. 缓冲通道的填满与清空
4. 向已关闭的通道发送数据

这些场景中，如果发生了死锁，程序将被永久阻塞，无法继续执行。为了避免死锁，需要仔细设计和管理goroutine之间的通信和同步操作，确保发送和接收操作能够匹配，以及通道的缓冲区大小适当设置。同时，使用`select`语句可以避免阻塞和死锁情况的发生，通过在多个通道上进行非阻塞的发送和接收操作，选择可用的通道进行通信。

##### 接收通道（chan）的数据有几种办法

接收通道（chan）的数据有以下几种方法，它们在行为上有一些不同点：

1. 阻塞接收（Blocking Receive）：
    
    - 使用 `<-` 运算符从通道接收数据，如果通道中没有数据，该操作将会阻塞当前的goroutine，直到有数据可接收。
    - 该方法是最常见的接收通道数据的方式，用于需要等待通道有数据可用时进行接收。
    
    ```go
 ch := make(chan int) 
 data := <-ch // 阻塞接收通道数据
    ```
    
2. 非阻塞接收（Non-Blocking Receive）：
    
    - 使用 `select` 语句和 `default` 分支实现非阻塞接收，如果通道中没有数据，`default` 分支将会执行，不会阻塞当前的goroutine。
    - 这种方式用于避免在通道无数据时一直阻塞，允许进行其他操作或进行通道数据的轮询。
    
```go
ch := make(chan int)
select {
case data := <-ch: // 非阻塞接收通道数据
    fmt.Println("Received:", data)
default:
    fmt.Println("Channel is empty")
}
```
    
3. 带有 `ok` 参数的接收（Receive with ok idiom）：
    
    - 在接收数据的时候，可以使用带有 `ok` 参数的方式判断通道是否已关闭，从而避免在通道关闭后继续接收数据引发的panic。
    - `ok` 参数为一个布尔值，如果通道已关闭且没有数据可接收时，`ok` 将为 `false`。
    
```go
ch := make(chan int)
close(ch)

data, ok := <-ch // 使用ok参数接收通道数据，检查通道是否已关闭
if ok {
    fmt.Println("Received:", data)
} else {
    fmt.Println("Channel is closed")
}
```
    
4. `for range` 循环接收：
    
    - 可以使用 `for range` 循环来迭代接收通道中的数据，直到通道被关闭，此时循环会自动退出。
    - 这种方式适用于通道未关闭且你希望**持续接收通道数据**的场景。
    
```go
ch := make(chan int)

// 使用for range循环接收通道数据，直到通道被关闭
for data := range ch {
    fmt.Println("Received:", data)
}
```

总结：
- 阻塞接收用于等待通道有数据可接收时进行接收。
- 非阻塞接收通过 `select` 语句和 `default` 分支避免一直阻塞，允许进行其他操作或通道数据的轮询。
- 带有 `ok` 参数的接收方式可以判断通道是否已关闭，避免在通道关闭后继续接收数据导致panic。
- `for range` 循环接收用于持续接收通道数据，直到通道被关闭。

##### select可以用于什么

- -   `select` 主要用于**监听多个`channel`是否可以收发消息**，`select会尝试执行case语句`。当任何一个case满足条件则会执行，若没有可执行的case，就会执行**default分支**。如果default也不满足，程序会跳出select语句块。

### 控制并发数

#### Go中如何实现一个协程池

[超详细的讲解Go中如何实现一个协程池](https://toutiao.io/posts/e48co5x/preview)

#### 有缓冲的通道(chanel)

**使用通道：** 通过创建一个有缓冲的通道，你可以限制并发的协程数量。在通道满载时，后续协程会被阻塞，直到有空余位置。这种方法也称为“信号量”模式。


### go什么情况下内存会泄露

在Go语言中，内存泄漏是指程序在运行过程中不再使用的内存没有被垃圾回收器释放，导致内存持续增加，最终耗尽系统的可用内存。内存泄漏是开发过程中常见的错误之一，主要发生在以下情况下：

1. 循环引用：当两个或多个对象之间存在循环引用，并且这些对象都无法被访问到时，垃圾回收器无法正确识别它们，导致这些对象无法被回收。
    
2. 未关闭资源：在使用文件、网络连接、数据库连接等资源时，如果忘记及时关闭这些资源，它们会一直存在于内存中，导致内存泄漏。
    
3. 启动过多的goroutine：如果在程序中启动了大量的goroutine，但这些goroutine一直处于阻塞状态而无法终止，那么它们将占用系统的内存。
    
4. 大对象缓存：如果程序中使用了一个缓存结构来存储大对象，并且没有合理的策略去清理不再需要的对象，那么这些大对象将一直存在于内存中，导致内存泄漏。
    
5. 资源释放顺序错误：如果资源的释放顺序不正确，可能会导致资源无法被释放，从而造成内存泄漏。
    
6. 未使用的指针：如果创建了某些对象或数据结构的指针，但从未使用它们，这些指针指向的内存可能永远无法被回收。
    


# GMP 

1. **Goroutine（G）：** Goroutine 是 Go 语言中的轻量级线程，它们在程序中执行并发任务。Goroutine 由 Go 运行时（runtime）管理，可以通过 `go` 关键字创建。每个 Goroutine 都有一个唯一的标识符（GID）。
    
2. **操作系统线程（M）：** Go 运行时会创建一组操作系统线程，用于在实际的 CPU 核心上执行 Goroutine。每个操作系统线程都被称为 M（Machine），它负责调度和执行 Goroutine。
    
3. **处理器（P）：** 处理器（Processor）是 Go 运行时的调度单位，用于将 Goroutine 映射到操作系统线程上。处理器的数量可以通过 GOMAXPROCS 设置。

### GMP调度过程

1. 初始阶段，Go 运行时会根据 GOMAXPROCS 创建一定数量的处理器（P）。
2. 当一个新的 Goroutine 被创建时，它会被放入全局 Goroutine 队列（G），等待分配一个处理器（P）。
3. Go 运行时的调度器（Scheduler）会从全局 Goroutine 队列（G）中选择一个 Goroutine，将其分配给一个空闲的处理器（P）。
4. 处理器（P）负责将选中的 Goroutine 运行在一个操作系统线程（M）上执行。
5. 如果一个 Goroutine 在执行过程中发生阻塞（如等待 I/O），处理器会将其与操作系统线程分离，以便其他 Goroutine 继续执行。
6. 一段时间后，处理器会检查是否有其他 Goroutine 可以运行，如果没有，就会让出当前的操作系统线程，以便其他 Goroutine 有机会执行。
7. 如果一个 Goroutine 执行完毕或发生阻塞，相应的处理器会将其从操作系统线程中分离。
8. 在整个调度过程中，Goroutine 的状态会根据其运行状态进行切换，包括运行、阻塞、就绪等状态。

### GMP能不能去掉P层？会怎么样？

P 层的存在是为了**解决 M-N 模型中的线程切换和调度问题**。在 M-N 模型中，M 表示内核线程，N 表示 goroutine。**当一个内核线程中的 goroutine 阻塞时，会导致整个线程无法继续执行其他 goroutine，从而影响并发性能。** 通过引入 P 层，每个 M 可以绑定一个或多个 P，并且每个 P 可以执行多个 goroutine。P 层通过协作调度，使得当一个 goroutine 阻塞时，其他 goroutine 仍然可以继续执行，提高了并发性能和资源利用率。

因此，去掉 P 层会导致运行时系统失去了协作调度的能力，无法在阻塞时切换到其他可运行的 goroutine。这可能导致并发执行的能力下降，同时也会影响系统的资源利用率。因此，去掉 P 层可能会对程序的性能和可扩展性产生负面影响。

总的来说，P 层在 Go 的并发模型中起着重要的作用，去掉 P 层可能会导致运行时系统失去协作调度的能力，从而影响并发性能和资源利用率。因此，不建议去掉 P 层。

### 抢占式调度是如何抢占的，怎么调度 `goroutine`

GPM（Goroutine-Processor-Machine）是Go语言运行时系统中的调度器的核心组件。抢占式调度（Preemptive Scheduling）是指调度器可以主动中断当前正在执行的Goroutine并切换到其他可运行的Goroutine的调度方式。以下是GPM抢占式调度的工作原理：

1. G的创建和调度：在Go程序中，Goroutine是轻量级的执行单元。当创建一个Goroutine时，调度器会将其分配给可用的P（Processor）来执行。每个P都有一个G的运行队列（run queue）用于存储可运行的Goroutine。
    
2. P的管理：调度器会创建一组P，通常与CPU核心的数量相当。每个P都有自己的本地队列（local run queue）和全局队列（global run queue）。本地队列存储与该P绑定的Goroutine，全局队列存储所有未被分配到P的Goroutine。
    
3. 抢占时机：当一个Goroutine执行时间超过一定阈值（称为时间片）时，调度器会发出抢占信号，要求当前的Goroutine主动放弃执行权。这个阈值可以通过`GOMAXPROCS`和`GOMAXIMUMSCHEDULER`等环境变量进行配置。
    
4. 抢占过程：当抢占信号发生时，当前执行的Goroutine会被暂停，调度器会选择一个可运行的Goroutine来继续执行。选择的过程基于调度算法（例如多级反馈队列调度算法），它考虑到Goroutine的优先级、等待时间、资源需求等因素。
    
5. 上下文切换：当调度器选择了一个新的Goroutine来执行时，它会进行上下文切换，保存当前Goroutine的执行状态，并恢复选中Goroutine的执行状态。这个切换过程包括保存和恢复Goroutine的寄存器状态、堆栈指针等。
    
6. 队列管理：调度器会根据不同的策略和算法，动态地管理本地队列和全局队列中的Goroutine。它可以将Goroutine从一个P的本地队列转移到另一个P的本地队列，或者从全局队列移动到本地队列，以实现负载均衡和更好的调度效果。
    

通过抢占式调度，Go调度器能够在不同的Goroutine之间进行公平的资源分配，并防止某个Goroutine长时间占用CPU，从而提高整体的并发性能和响应能力。

# STW

### GC 中 stw 时机，各个阶段是如何解决的

在垃圾回收（Garbage Collection）的过程中，"STW"代表"Stop-The-World"，即停止应用程序的执行。在这期间，**所有的应用程序线程都被暂停，以便进行垃圾回收操作。** 以下是常见的垃圾回收阶段以及它们如何解决STW问题：

1. 标记阶段（Marking Phase）：在这个阶段，垃圾回收器标记出所有活动对象。为了解决STW问题，通常使用"并发标记"的技术，即**在应用程序运行的同时进行标记操作**。垃圾回收器会利用应用程序的空闲时间，**在后台线程进行标记操作**，以减少STW时间。
    
2. 清除阶段（Sweeping Phase）：在这个阶段，垃圾回收器**清除被标记为垃圾的对象**，并回收它们所占用的内存空间。这个阶段通常会涉及STW，因为需要确保所有垃圾对象都被正确地清除。一些垃圾回收器**采用增量清除或并发清除的方式来减少STW时间**，即在应用程序执行的同时进行清除操作。
    
3. 压缩阶段（Compacting Phase）：在这个阶段，垃圾回收器将存活的对象移动到一起，以减少内存碎片化，并提供更大的连续可用内存空间。**压缩阶段通常需要STW**，因为需要保证对象移动过程的一致性。类似于标记和清除阶段，一些垃圾回收器采用增量或并发压缩的方式来减少STW时间。
    

除了上述阶段外，还有其他一些垃圾回收相关的操作可能会导致STW，例如内存分配时的空间耗尽检查（Allocation Failure），或者在特定条件下触发的全局垃圾回收（Full GC）。为了减少STW的影响，一些垃圾回收器引入了各种技术和算法，如分代回收、并发回收、增量回收等，以在应用程序运行期间尽量减少STW时间，并平衡垃圾回收和应用程序的执行。

需要注意的是，不同的垃圾回收器和虚拟机实现可能有不同的策略和技术来解决STW问题。因此，具体的解决方法可能会因垃圾回收器和虚拟机的选择而有所差异。

# Language

### Go面向对象是如何实现

Go 语言虽然没有像其他一些面向对象编程语言那样提供传统的类和继承的概念，但它仍然支持面向对象的编程风格和特性。在 Go 中，面向对象是通过结构体（struct）和方法（method）来实现的。

以下是 Go 语言中实现面向对象的几个关键点：

1. 结构体（struct）：结构体是一种自定义的数据类型，可以用于封装一组相关的数据字段。**结构体可以包含字段和方法**，并可以定义行为和属性。
    
2. 方法（method）：方法是**与结构体关联的函数**，它可以访问结构体的字段和执行特定的操作。方法可以定义在结构体上，也可以定义在非结构体类型上。
    
3. 接口（interface）：接口是一组方法的集合，用于定义对象的行为。接口定义了对象应该具有的方法，并提供了一种约束，实现了接口的类型必须实现接口中定义的所有方法。
    
4. 封装（encapsulation）：封装是一种将数据和相关方法隐藏起来，只允许特定的操作方式来访问和修改数据的机制。在 Go 中，使用**大写字母开头的字段或方法**可以实现对外部的公开访问，小写字母开头的字段或方法则是私有的。
    
5. 继承（inheritance）：Go 语言没有显式的继承机制，但可以通过**嵌入结构体**来实现类似的效果。通过在一个结构体中嵌入另一个结构体，可以继承其字段和方法。
    
6. 多态（polymorphism）：Go 语言通过接口实现了多态的特性。多态允许不同类型的对象对相同的接口进行操作，提高了代码的灵活性和复用性。
    

总的来说，Go 语言的面向对象编程风格通过结构体、方法和接口等机制来实现。虽然与传统的面向对象编程语言有所不同，但它依然提供了一种灵活、简洁和高效的方式来组织和管理代码。

### GO Error

- [Golang 中的错误处理](https://pandaychen.github.io/2022/05/30/HOW-TO-DEAL-WITH-GOLANG-ERRORS/)
- [Golang error 的突围](https://www.cnblogs.com/qcrao-2018/p/11538387.html)

### Golang 闭包

1. [Golang 中关于闭包的坑](https://www.jianshu.com/p/fa21e6fada70)
2. [Golang 闭包与递归：介绍与应用场景](https://pandaychen.github.io/2023/03/25/A-GOLANG-CLOSURE-USAGE/)

- 是指内层函数引用了外层函数中的变量或称为引用了自由变量的函数，其返回值也是一个函数（方法）
- 特点
	- 闭包能够访问外层代码中的变量
	- `for range` 模式与 goroutine 同时执行
	- 所有的 goroutine 操作的变量都是直接操作外层代码的变量，而外层代码中的变量的值取决于循环执行的节点

#### 变量传递

`for range` 返回的 `val` 的值是引用的同一个内存地址的数据，所以匿名函数访问的函数体外部的 `val` 值是循环中最后输出的一个值

```go
  for _, item := range s {
                newitem := item
                go func() {
                        fmt.Println(newitem)
                        waitGroup.Done()
                }()
        }
```

### make  new 和 :=  使用区别

1. `make`：
	- `make` 是一个**用于创建切片、映射和通道的内置函数**。
	- 它分配并初始化了底层的数据结构，并**返回对应类型的引用（切片、映射或通道）**。
	- 使用 `make` 创建的变量是**对底层数据结构的引用**，而不是变量本身的值。

2. `new`：
	- `new` 是一个用于**在堆上分配内存并返回指向该内存的指针的内置函数**。
	- 它接收一个类型作为参数，并**返回该类型的零值**的指针。
	- 使用 `new` 创建的变量是指针类型，指向分配在堆上的内存空间。

3. `:=`（短变量声明）：
	- `:=` 操作符用于**在当前作用域内**声明和初始化变量。
	- 它根据右侧表达式的类型推断变量的类型，并进行赋值。
	- `:=` 创建的变量是**在栈上分配**的，并且**只在当前作用域内可见**。

##### 值类型和引用类型

首先我们得知道，Go分为数据类型分为值类型和引用类型，其中

- 值类型是 int、float、string、bool、struct和array，它们直接存储值，分配栈的内存空间，它们被函数调用完之后会释放
- 引用类型是 slice、map、chan和值类型对应的指针 它们存储是一个地址（或者理解为指针）,指针指向内存中真正存储数据的首地址，内存通常在堆分配，通过GC回收

1. new 的参数要求传入一个类型，而不是一个值，它会申请该类型的内存大小空间，并初始化为对应的零值，返回该指向类型空间的一个指针
2. make 也用于内存分配，但它只用于引用对象 slice、map、channel的内存创建，返回的类型是类型本身

### sync 同步原语

在 Go 语言中，`sync` 包提供了一些常用的同步原语，用于实现并发安全的操作。以下是几个常见的 `sync` 同步原语以及它们的作用：

1. **`sync.Mutex`：** 互斥锁是最基本的同步原语，用于保护共享资源的并发访问。使用互斥锁可以确保同时只有一个协程能够访问被保护的资源，避免竞争条件。
    
2. **`sync.RWMutex`：** 读写锁是在读多写少的场景中提供更高并发性的一种锁。多个协程可以同时获取读锁，但只有一个协程可以获取写锁。这允许多个协程同时读取数据，但写操作会独占锁。
    
3. **`sync.WaitGroup`：** `WaitGroup` 用于等待一组协程完成任务后再继续执行。你可以使用 `Add` 方法增加计数，使用 `Done` 方法减少计数，以及使用 `Wait` 方法阻塞主线程直到计数归零。

```go
requests := []*Request{...}
wg := &sync.WaitGroup{}
wg.Add(len(requests))

for _, request := range requests {
    go func(r *Request) {
        defer wg.Done()
        // res, err := service.call(r)
    }(request)
}
wg.Wait()
```
    
4. **`sync.Once`：** `Once` 用于保证某个操作只会执行一次。它在多个协程之间确保只有一个协程会执行指定的函数，通常用于初始化操作。
    
5. **`sync.Cond`：** 条件变量用于在协程之间同步和通信。通过 `Wait`、`Signal` 和 `Broadcast` 方法，你可以在特定条件下阻塞协程，唤醒单个协程或唤醒所有协程。
    
6. **`sync.Map`：**
    - `sync.Map` 是 Go 1.9 引入的一种并发安全的映射（map）类型，用于在多协程环境下进行读写操作而无需额外的锁。
    - `sync.Map` 可以安全地被多个协程并发地读写，而无需额外的锁定机制。
    - 它适用于一些读多写少的场景，可以提供较好的并发性能。
    
7. **`sync.Pool`：**
    - `sync.Pool` 用于对象的临时分配和复用。它可以用来存储临时的对象，以便在后续操作中重复使用，从而避免频繁的内存分配和垃圾回收。
    - `sync.Pool` 不保证存储的对象会一直存在，它可能在内存不足的情况下被释放。
    - `sync.Pool` 是基于协程的，每个协程都有一个独立的对象池，因此可以在协程之间实现资源的共享和复用。
    - `sync.Pool` 可以用于一些临时对象的高频使用场景，如临时缓冲区、连接池等。

```go
func main() {
	var pool = sync.Pool{
		New: func() interface{} {
			fmt.Println("Creating new object")
			return "new object"
		},
	}

	// 从池中获取对象
	obj := pool.Get().(string)
	fmt.Println("Got object from pool:", obj)

	// 将对象放回池中
	pool.Put(obj)

	// 再次从池中获取对象，此时不会创建新对象，而是从池中获取已有对象
	obj = pool.Get().(string)
	fmt.Println("Got object from pool:", obj)
}
```

### atomic 使用

[Go语言的原子操作atomic](https://www.programminghunter.com/article/37392193442/)

在Go语言中，`atomic`包提供了一组函数用于对基本类型进行原子操作。这些原子操作函数能够确保操作的原子性，避免竞态条件和数据不一致问题。以下是一些常用的`atomic`包函数及其用法：

1. `atomic.LoadInt32` 和 `atomic.LoadInt64`：用于原子地加载（读取）一个32位或64位整数值。

```go
value := atomic.LoadInt32(&num)
```

2. `atomic.StoreInt32` 和 `atomic.StoreInt64`：用于原子地存储（写入）一个32位或64位整数值。

```go
atomic.StoreInt32(&num, value)
```

3. `atomic.AddInt32` 和 `atomic.AddInt64`：用于原子地对一个32位或64位整数值进行加法操作。

```go
atomic.AddInt32(&num, 1)
```

4. `atomic.CompareAndSwapInt32` 和 `atomic.CompareAndSwapInt64`：用于原子地比较并交换一个32位或64位整数值。

```go
old := atomic.LoadInt32(&num)
new := 100
if atomic.CompareAndSwapInt32(&num, old, new) {
    // 操作成功
} else {
    // 操作失败
}
```

除了上述函数，`atomic`包还提供了其他原子操作函数，如递增和递减操作（`atomic.AddInt32`、`atomic.AddInt64`）、位操作（`atomic.LoadUint32`、`atomic.StoreUint32`）等。使用这些原子操作函数时，需要注意在多个goroutine之间正确同步和协调访问共享资源。

需要注意的是，`atomic`包只能用于基本类型的原子操作，对于复杂的数据结构，需要使用其他的同步机制，如互斥锁（`sync.Mutex`）或读写锁（`sync.RWMutex`）来保证线程安全性。



### panic（使用多值返回来返回错误
1. 函数立刻停止执行 (注意是函数本身，不是应用程序停止)
2. defer函数被执行
3. 返回给调用者(caller)
4. 调用者函数假装也收到了一个panic函数，从而  
	1. 立即停止执行当前函数  
	2. 它defer函数被执行  
	3. 返回给它的调用者(caller)
5. ...(递归重复上述步骤，直到最上层函数)  
    应用程序停止。
6. panic的行为

### log.Fatal
1. 打印输出内容
2. 退出应用程序
3. defer函数不会执行

### 数组（Array）和切片（Slice）

数组是**固定长度的、值类型**的数据结构。

切片是**动态长度的、引用类型**的数据结构。
	切片的底层实现是一个指向连续内存区域的指针，这个内存区域是数组。切片通过指针（Pointer）、长度（Length）和容量（Capacity）这三个字段来描述和操作底层数组。

- 当slice的`len==cap`后，再向slice中追加元素时，会发生扩容
- [你不知道的 Go 之 slice](https://darjun.github.io/2021/05/09/youdontknowgo/slice/)

### map

`map` 的数据结构是一个哈希表（Hash Table）

#### map如何顺序读取

1. map底层使用hash表实现,插入数据位置是随机的
2. 将 map 的 key 全部拿出来，放到一个数组中，
3. 然后对这个数组排序后对有序数组遍历，再间接取 map 里的值

**第三方库**
github.com/elliotchance/orderedmap

#### sync.Map

`sync.Map` 是 Go 语言标准库中的一个并发安全的映射数据结构。它是通过内置的 `sync` 包实现的，其内部实现比较复杂，基于分段锁（sharded lock）的方式来提高并发性能。下面是 `sync.Map` 的简要实现原理：

1. **分段锁**：`sync.Map` 内部维护了一个固定数量的小型映射（通常是 256 个），每个小型映射都有自己的互斥锁。这样，整个 `sync.Map` 中的数据被分为多个分段，每个分段独立于其他分段。这个分段锁的机制使得在读取或写入映射时只需锁住其中一个分段，而不需要锁住整个映射，从而提高了并发性能。
    
2. **哈希算法**：为了确定一个键值对应于哪个分段，`sync.Map` 使用哈希算法对键进行哈希运算，然后根据哈希值选择分段。这确保了不同键分布在不同的分段上，减少了锁竞争。
    
3. **原子操作**：`sync.Map` 使用原子操作来进行映射的读取、写入和删除操作，这样可以保证多个协程并发访问时不会发生数据竞争。
    
4. **无需手动加锁**：与传统的 `map` 不同，`sync.Map` 不需要手动加锁来保护并发访问。它的方法（如 `Load`、`Store`、`Delete`）会在内部进行加锁和解锁，使得操作变得更加方便。

1. **Load：**
    
    ```go
func (m *Map) Load(key interface{}) (value interface{}, ok bool)
    ```
    
    用于从 `sync.Map` 加载键对应的值，返回值和是否成功加载。
    
2. **Store：**
    
    ```go
func (m *Map) Store(key, value interface{})
    ```
    
    用于向 `sync.Map` 存储键值对，如果键已存在，则更新其对应的值。
    
3. **LoadOrStore：**
    
    ```go
func (m *Map) LoadOrStore(key, value interface{}) (actual interface{}, loaded bool)
    ```
    
    尝试从 `sync.Map` 加载指定键的值，如果键不存在，则存储提供的键值对。
    
4. **Delete：**
    
    ```go
func (m *Map) Delete(key interface{})
    ```
    
    从 `sync.Map` 删除指定键的键值对。
    
5. **LoadAndDelete：**
    
    ```go
func (m *Map) LoadAndDelete(key interface{}) (value interface{}, loaded bool)
    ```
    
    原子地加载并删除指定键的值。
    
6. **Range：**
    
    ```go
func (m *Map) Range(f func(key, value interface{}) bool)
	```
    
    遍历 `sync.Map` 中的键值对，通过传入的函数对每个键值对进行处理。

### map和切片的扩容规则

虽然`map`和切片都会触发扩容操作，但它们的扩容规则有一些不同之处：

**Map 扩容规则：**

1. 扩容触发：`map` 的扩容是在键值对数量达到**当前底层数组容量的负载因子**时触发的。负载因子是指当前键值对数量除以当前底层数组容量的比值。当负载因子超过一定的阈值时，会触发扩容。
2. 容量计算：扩容时会计算新的容量，并选择最接近当前容量的 2 的幂次作为新的容量。

**切片 扩容规则：**

1. 扩容触发：切片的扩容是在切片的长度（`len`）超过容量（`cap`）时触发的。当 `len` 超过了 `cap` 时，进行 `append` 操作将会导致扩容。
2. 增长策略：切片的扩容是通过创建一个新的更大的底层数组，并将原有数据复制到新数组中实现的。新数组的大小一般是原数组大小的 2 倍，但具体增长策略可能会因编译器和运行时的版本而有所不同。

**共同点：**

1. 数据复制：扩容时都会创建一个新的更大的底层数组，并将原有的数据复制到新数组中。这涉及到一次数据复制操作，因此扩容可能会产生一定的性能开销。
2. 动态调整：无论是`map`还是切片，扩容都是在运行时动态进行的，不需要程序员手动干预。

**区别：**

- `map` 扩容是根据负载因子来触发的，而切片扩容是根据当前切片长度和容量的比较进行判断的。
- `map` 的容量会动态增长到最接近当前容量的 2 的幂次，而切片的容量一般是原数组大小的 2 倍。因此，在`map`的扩容中，新容量可能更加灵活，而切片的扩容一般是按照倍增方式进行的。

需要特别注意的是，虽然`map`和切片的扩容是自动进行的，但在扩容时涉及到数据的重新哈希和底层数组的切换，因此扩容操作可能会产生一定的性能开销。在处理大量数据或对性能要求较高的场景中，应该合理评估扩容行为和性能影响，可以在创建`map`或切片时提前预估合适的容量，避免过多的扩容操作。

### fmt.Printf 的 格式化占位符

1. `%v`：通用的格式化占位符，根据值的类型选择合适的默认格式。
2. `%+v`：输出结构体各成员的**名称**和**值**；
3. `%#v`：输出结构体名称和结构体各成员的名称和值
4. `%s`：字符串。
5. `%t`：布尔值，打印 `true` 或 `false`。
6. `%T`：于打印值的类型信息

### go struct能不能比较

在 Go 语言中，结构体是可比较的，前提是结构体的字段都是可比较的类型。

可比较的类型包括基本类型（如整数、浮点数、布尔值等）、字符串、指针、数组、切片和结构体。如果**结构体的所有字段都是可比较的类型**，并且**字段的类型和顺序在两个结构体中完全相同**，并且**对应字段的值也相等**，那么这两个结构体就是**可比较且相等**的。

需要注意的是，如果**结构体中包含不可比较的类型，如切片、映射或函数等**，或者结构体中包含指针类型的字段，那么比较操作**将会引发编译错误**。如果需要深度比较结构体，可以使用其他库或自定义函数来实现。

综上所述，结构体是可比较的，但需要注意字段类型的可比较性和字段值的相等性。

- reflect.DeepEqual 函数用来判断两个值是否深度一致

### go defer（for defer）
- 被defer的函数执行顺序满足LIFO原则，后defer的先执行。
- 被`defer`的函数或者方法如果存在多级调用，只有最后一个函数或方法会被`defer`到函数return或者panic之前执行
- 被defer的**函数或方法的参数的值在执行到defer语句的时候就被确定**下来了。
- defer后面跟的必须是函数或者方法调用，defer后面的表达式不能加括号。
- 被defer的函数可以**对defer语句所在的函数的命名返回值做读取和修改操作**。

### context 的用途

- [上下文 Context](https://draveness.me/golang/docs/part3-runtime/ch06-concurrency/golang-context/)
- [Context](https://www.topgoer.cn/docs/golang/chapter11-10)

`context`（上下文）是Go语言中用于传递请求范围数据、控制请求的生命周期以及处理并发的重要机制。它主要用于**在多个Goroutine之间传递请求相关的数据和取消信号**。

#### `context` 使用场景

1. **并发操作的控制和取消：** 当你在一个应用程序中使用多个 goroutine 进行并发操作时，可以使用 `context` 来传递取消信号并优雅地停止 goroutine 的执行。如果某个操作或任务不再需要继续执行，你可以通过取消相关的 `context` 来通知相应的 goroutine 停止。
    
2. **处理请求和超时：** 在处理网络请求或其他 I/O 操作时，你可以使用 `context` 来设置截止时间，以确保请求在一定时间内完成。如果请求超过了指定的截止时间，相关的操作可以被取消，避免资源的浪费。
    
3. **传递请求范围的数据：** 在一个请求处理链中，你可以使用 `context` 来传递请求范围的数据，比如请求 ID、用户认证信息等。这可以避免在每个函数中显式地传递这些信息。
    
4. **数据库事务管理：** 当在数据库事务中进行多个操作时，你可以将事务相关的信息存储在 `context` 中，以便在不同的函数中进行访问和操作。
    
5. **处理多级调用栈：** 当在多级函数调用栈中需要传递信息时，可以使用 `context` 来传递数据，而不必一级一级地传递参数。
    
6. **测试和模拟：** 在测试代码中，你可以使用自定义的 `context` 来模拟不同的情境，以测试不同的路径和场景。

#### `context` 的衍生函数

1. **`context.WithCancel(parent Context) (ctx Context, cancel CancelFunc)`：** 这个函数用于从父上下文中衍生出一个新的上下文，并返回一个取消函数。当调用取消函数时，新的上下文及其所有的子上下文都会被取消。
    
2. **`context.WithTimeout(parent Context, timeout time.Duration) (Context, CancelFunc)`：** 这个函数用于从父上下文中衍生出一个新的上下文，它会在指定的时间后自动取消。一旦超过指定的时间，新的上下文及其所有的子上下文都会被取消。
    
3. **`context.WithDeadline(parent Context, deadline time.Time) (Context, CancelFunc)`：** 类似于 `WithTimeout`，这个函数用于从父上下文中衍生出一个新的上下文，不过它是在指定的截止时间之后自动取消。
    
4. **`context.WithValue(parent Context, key interface{}, val interface{}) Context`：** 这个函数用于从父上下文中衍生出一个新的上下文，并在其中添加一个键值对。这样可以在上下文中传递请求范围的值，如请求 ID、用户认证信息等。

### Time, Ticker
[golang 定時器(一) Time, Ticker 基本用法整理](https://davidleitw.github.io/posts/time01/)


### Go 语言 tag 的用处

在Go语言中，结构体字段的tag是用于为结构体字段附加元数据的一种机制。它以反引号包裹的字符串形式出现在结构体字段的声明后面，如`json:"name"`。

结构体字段的tag在编译期间可以被反射机制读取和解析，常用于以下场景：

1. 序列化和反序列化：常见的使用是在进行JSON、XML等格式的序列化和反序列化时，使用tag指定字段与序列化后的名称之间的映射关系。比如，可以使用`json:"name"`来指定某个字段在JSON中的名称。
    
2. 数据校验和验证：可以使用tag来指定字段的校验规则和约束条件。一些第三方库和框架可以根据tag定义的校验规则对结构体进行验证，比如检查字段的长度、数据类型等。
    
3. ORM映射：在使用ORM（对象关系映射）库时，可以使用tag来指定结构体字段与数据库表字段之间的映射关系，比如表名、列名、主键等。
    
4. API文档生成：一些API文档生成工具可以根据结构体字段的tag生成相应的API文档，包括字段的描述、类型、示例值等。
    

总之，结构体字段的tag为开发者提供了一种扩展和附加元数据的机制，可以在运行时通过反射读取和解析这些tag，用于实现各种功能和处理逻辑。

### 如何获取一个结构体的所有tag

```go
type User struct {
	ID   int    `json:"id"`
	Name string `json:"name"`
	Age  int    `json:"age"`
}

func main() {
	user := User{
		ID:   1,
		Name: "John Doe",
		Age:  30,
	}

	// 获取结构体类型
	userType := reflect.TypeOf(user)

	// 遍历结构体的字段
	for i := 0; i < userType.NumField(); i++ {
		field := userType.Field(i)

		// 获取字段的tag
		tag := field.Tag

		// 打印字段名和对应的tag值
		fmt.Printf("Field: %s, Tag: %s\n", field.Name, tag)
	}
}

```

### 函数返回局部变量的指针

	局部变量在函数返回后会被销毁，而返回指向已被销毁的局部变量的指针可能会导致访问无效的内存。

- 如果需要在函数之外使用局部变量的值，可以考虑使用返回值而不是指针。
	- Go会进行**逃逸分析**，如果发现局部变量的作用域超过该函数则会**把指针分配到堆区**，避免内存泄漏。
- 确实需要返回指向局部变量的指针，可以通过动态分配内存来避免访问无效的内存。例如，使用 `new` 或 `make` 函数创建堆上的变量，并返回指向该堆上变量的指针。


### uint 溢出问题怎么办

在 Go 语言中，`uint` 是无符号整数类型，它的取值范围是从 0 到 `math.MaxUint`。当进行计算或赋值操作时，如果超出了 `uint` 的取值范围，会发生溢出。

处理 `uint` 溢出的方法取决于具体的应用场景和需求。以下是一些处理 `uint` 溢出的常见方法：

1. 检查溢出：在进行计算之前，可以先检查操作数的范围，并确保不会导致溢出。例如，可以使用条件语句或比较操作符检查计算结果是否超过了 `math.MaxUint`。
    
2. 使用更大的整数类型：如果 `uint` 的范围不足以满足需求，可以考虑使用更大的整数类型，如 `uint64`。这样可以扩展取值范围，并避免溢出问题。注意，在使用更大的整数类型时，需要确保与其他相关代码的兼容性。
    
3. 使用溢出检测和处理函数：Go 语言标准库提供了一些处理溢出的函数，如 `math.SafeAdd`、`math.SafeSub`、`math.SafeMul` 等。这些函数可以进行溢出检测，并采取适当的措施来处理溢出情况。
    
4. 使用溢出安全的库：除了标准库提供的函数外，还有一些第三方库专门用于处理整数溢出问题。这些库提供了更丰富的功能和处理方式，可以根据具体需求选择合适的库来处理溢出问题。
    

需要注意的是，在处理溢出时，应根据具体的业务逻辑和需求来选择合适的处理方式。对于关键的计算和数据操作，建议进行严格的溢出检查和处理，以确保程序的正确性和安全性。


### go的调试/分析工具

Go语言提供了一些强大的调试和分析工具，可以帮助开发人员进行代码调试、性能优化和内存分析等任务。以下是一些常用的Go调试/分析工具：

1. go run、go build和go test：这些是Go的基本命令行工具，可用于构建、运行和测试Go程序。通过这些命令行工具，您可以快速验证程序的功能和正确性。
    
2. go fmt：这是Go的代码格式化工具，用于自动调整和统一代码的格式。使用go fmt命令可以确保代码在风格上保持一致，增强代码的可读性。
    
3. go vet：这是Go的静态分析工具，用于检查代码中的潜在错误和问题。go vet可以帮助您发现一些常见的错误，如未使用的变量、错误的函数调用和类型不匹配等。
    
4. go test -cover：这是Go的测试工具，通过加上-cover选项可以生成测试覆盖率报告。测试覆盖率报告显示了程序中哪些部分被测试覆盖到，帮助您确保测试覆盖全面。
    
5. go tool pprof：这是Go的性能分析工具，用于分析和优化程序的性能。通过使用pprof，您可以收集和分析程序的CPU使用情况、内存分配和堆栈跟踪等信息，以便找到性能瓶颈和优化机会。
    
6. go trace：这是Go的跟踪工具，用于生成程序执行的时间轴跟踪数据。通过使用go trace，您可以获得程序的详细执行信息，帮助您理解和调试程序的行为。
    

除了上述工具，还有许多第三方工具可用于Go的调试和分析，如Delve调试器、Goroutine分析工具、Heap分析工具等。这些工具提供了更多的功能和灵活性，可根据具体需求进行选择和使用。





### 参考文章：
1. [常见Go语言的面试题](https://zhuanlan.zhihu.com/p/360306642)
2. [Go设计模式常见面试题](https://zhuanlan.zhihu.com/p/542596378)