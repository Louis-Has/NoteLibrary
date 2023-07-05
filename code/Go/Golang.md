1.  struct 匿名字段 嵌入字段 重载字段 method重写
2.  如果不传Box的指针，那么SetColor接受的其实是Box的一个copy，也就是说method内对于颜色值的修改，其实只作用于Box的copy，而不是真正的Box。
3.  goroutine说到底其实就是协程，但是它比线程更小
4.  str,_ := username.(string) 类型断言

### GO Error
- [Golang 中的错误处理](https://pandaychen.github.io/2022/05/30/HOW-TO-DEAL-WITH-GOLANG-ERRORS/)
- [Golang error 的突围](https://www.cnblogs.com/qcrao-2018/p/11538387.html)

### [Golang 闭包](https://pandaychen.github.io/2023/03/25/A-GOLANG-CLOSURE-USAGE/)
- 是指内层函数引用了外层函数中的变量或称为引用了自由变量的函数，其返回值也是一个函数（方法）
- 特点
	- 闭包能够访问外层代码中的变量
	- `for range` 模式与 goroutine 同时执行
	- 所有的 goroutine 操作的变量都是直接操作外层代码的变量，而外层代码中的变量的值取决于循环执行的节点

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

### slice，len，cap，共享，扩容
- 当slice的`len==cap`后，再向slice中追加元素时，会发生扩容
- [你不知道的 Go 之 slice](https://darjun.github.io/2021/05/09/youdontknowgo/slice/)

### map如何顺序读取
- map底层使用hash表实现,插入数据位置是随机的
- 将 map 的 key 全部拿出来，放到一个数组中，
- 然后对这个数组排序后对有序数组遍历，再间接取 map 里的值

### 实现set
- set := make(map[string]void)

### go struct能不能比较
-  可比较：_Integer_，_Floating-point_，_String_，_Boolean_，_Complex(复数型)_，_Pointer_，_Channel_，_Interface_，_Array_
-  不可比较：_Slice_，_Map_，_Function_
- 所以 struct 当结构不包含不可直接比较成员变量时可直接比较，否则不可直接比较
- reflect.DeepEqual 函数用来判断两个值是否深度一致

### go defer（for defer）
- 被defer的函数执行顺序满足LIFO原则，后defer的先执行。
- 被`defer`的函数或者方法如果存在多级调用，只有最后一个函数或方法会被`defer`到函数return或者panic之前执行
- 被defer的函数或方法的参数的值在执行到defer语句的时候就被确定下来了。
- defer后面跟的必须是函数或者方法调用，defer后面的表达式不能加括号。
- 被defer的函数可以对defer语句所在的函数的命名返回值做读取和修改操作。

### 主协程如何等其余协程完再操作
- wg sync.WaitGroup
	- wg.Add(2)
	- wg.Done()
	- wg.Wait()

### select可以用于什么
- -   `select` 主要用于**监听多个`channel`是否可以收发消息**，`select会尝试执行case语句`。当任何一个case满足条件则会执行，若没有可执行的case，就会执行**default分支**。如果default也不满足，程序会跳出select语句块。

### context包的用途
- 主要用来在 goroutine 之间**传递上下文信息**，包括：请求特定数据、取消信号以及处理请求的截止日期。在多个 Goroutine 组成的树中同步取消信号以减少对资源的消耗和占用。
- 协程之间：需要共享一些全局变量、有共同的 deadline 等，而且可以同时被关闭。
- [Context](https://www.topgoer.cn/docs/golang/chapter11-10)

### Go 语言 tag 的用处

在Go语言中，结构体字段的tag是用于为结构体字段附加元数据的一种机制。它以反引号包裹的字符串形式出现在结构体字段的声明后面，如`json:"name"`。

结构体字段的tag在编译期间可以被反射机制读取和解析，常用于以下场景：

1. 序列化和反序列化：常见的使用是在进行JSON、XML等格式的序列化和反序列化时，使用tag指定字段与序列化后的名称之间的映射关系。比如，可以使用`json:"name"`来指定某个字段在JSON中的名称。
    
2. 数据校验和验证：可以使用tag来指定字段的校验规则和约束条件。一些第三方库和框架可以根据tag定义的校验规则对结构体进行验证，比如检查字段的长度、数据类型等。
    
3. ORM映射：在使用ORM（对象关系映射）库时，可以使用tag来指定结构体字段与数据库表字段之间的映射关系，比如表名、列名、主键等。
    
4. API文档生成：一些API文档生成工具可以根据结构体字段的tag生成相应的API文档，包括字段的描述、类型、示例值等。
    

总之，结构体字段的tag为开发者提供了一种扩展和附加元数据的机制，可以在运行时通过反射读取和解析这些tag，用于实现各种功能和处理逻辑。