
`GC`，全称 `Garbage Collection`，即垃圾回收，是一种自动内存管理的机制。


通常，垃圾回收器的执行过程被划分为两个半独立的组件：
-   赋值器（Mutator）：这一名称本质上是在指代用户态的代码。因为*对垃圾回收器而言，用户态的代码仅仅只是在修改对象之间的引用关系*，也就是在对象图（对象之间引用关系的一个有向图）上进行操作。
-   回收器（Collector）：负责执行垃圾回收的代码。




[GC](https://golang.design/go-questions/memgc/principal/)


[刘丹冰Aceld三色标记混合写屏障](https://www.yuque.com/aceld/golang/zhzanb)