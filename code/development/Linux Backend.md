[# Java中如何使用DAO？和service，ORM，repository，MVC的model是啥关系？](https://www.zhihu.com/question/589707954/answer/2937836966)

[# Mysql 项目应用笔记（一）](https://pandaychen.github.io/2022/02/01/A-MYSQL-USAGE-REVIEW/)

### 常用的Linux命令：

1. 文件和目录操作：
    - `ls`: 列出目录内容
    - `cd`: 切换目录
    - `pwd`: 显示当前工作目录
    - `mkdir`: 创建目录
    - `rm`: 删除文件或目录
    - `cp`: 复制文件或目录
    - `mv`: 移动文件或目录
    - `touch`: 创建空文件或更新文件时间戳
2. 文件查看和编辑：
    - `cat`: 查看文件内容
    - `more`: 分页查看文件内容
    - `less`: 分页查看文件内容，支持向前翻页
    - `head`: 显示文件开头几行
    - `tail`: 显示文件结尾几行
    - `nano`: 使用Nano编辑器编辑文件
    - `vim`/`vi`: 使用Vim编辑器编辑文件
3. 系统信息：
    - `uname`: 显示系统信息
    - `df`: 显示磁盘空间使用情况
    - `free`: 显示内存使用情况
    - `top`: 实时显示系统资源使用情况
    - `ps`: 显示当前进程信息
    - `htop`: 类似于top，但提供更多交互选项
4. 用户和权限管理：
    - `whoami`: 显示当前用户名
    - `who`: 显示当前登录用户
    - `useradd`: 添加新用户
    - `userdel`: 删除用户
    - `passwd`: 修改用户密码
    - `chown`: 更改文件或目录的所有者
    - `chmod`: 更改文件或目录的权限
5. 网络相关：
    - `ping`: 测试与主机的连通性
    - `ifconfig`/`ip`: 显示网络接口信息
    - `netstat`: 显示网络连接状态
    - `ssh`: 安全登录到远程主机
    - `scp`: 在本地主机和远程主机之间复制文件
6. 包管理（适用于基于Debian的发行版，如Ubuntu）：
    - `apt`: 包管理工具，用于安装、更新和删除软件包
    - `apt-get`: 旧版本的包管理工具
    - `dpkg`: 低级包管理工具，用于处理.deb包
7. 压缩和解压缩：
    - `tar`: 创建和提取tar归档文件
    - `gzip`/`gunzip`: 压缩和解压缩gzip文件
    - `zip`/`unzip`: 压缩和解压缩zip文件

### Linux 管道操作

在Linux中，管道（Pipeline）是一种强大的功能，它允许将一个命令的输出直接作为另一个命令的输入。通过管道，可以将多个命令连接在一起，形成一个命令序列，从而实现更复杂的操作。管道操作使用垂直线符号（|）表示。

[Linux管道命令（pipe）](https://www.jianshu.com/p/9c0c2b57cb73)

### 浏览器输入地址，中间发生的过程

1. **域名解析（DNS解析）**：浏览器首先将输入的网址发送给本地的DNS解析器（可能是你的路由器或互联网服务提供商的DNS服务器）。DNS解析器会查找域名解析表，如果没有缓存的解析结果，则向根域名服务器发送请求。
    
2. 递归查询：根域名服务器收到DNS解析器的请求后，会返回顶级域名服务器的地址（如.com、.net等）。DNS解析器再向顶级域名服务器发送请求。
    
3. 迭代查询：顶级域名服务器会返回管理该域名的权威域名服务器的地址。DNS解析器继续向权威域名服务器发送请求。
    
4. 解析结果返回：权威域名服务器接收到DNS解析器的请求后，会**返回该域名对应的IP地址**。DNS解析器将这个IP地址缓存起来，并将解析结果返回给浏览器。
    
5. 建立连接：浏览器拿到解析结果后，会**使用HTTP协议与Web服务器建立连接**。浏览器发送一个HTTP请求，包含请求的方式（GET、POST等）、请求的资源路径、请求头等信息。
    
6. 服务器响应：Web服务器接收到浏览器发送的HTTP请求后，会解析请求并找到对应的资源。服务器将资源内容封装成HTTP响应，包括状态码、响应头和响应体等信息。
    
7. 数据传输：一旦服务器发送HTTP响应，浏览器就开始接收响应的数据。这个过程中，数据会通过网络传输到达浏览器端。
    
8. **渲染页面**：浏览器接收到响应数据后，开始解析HTML、CSS和JavaScript等资源，构建页面的DOM树。然后，浏览器根据DOM树来渲染页面，展示给用户。
    

这些步骤通常是在几毫秒到几秒之间完成的，具体的时间取决于网络连接的速度和服务器的响应时间。一旦页面加载完成，你就可以在浏览器上看到相应的网页内容。

### TCP协议中的TIME_WAIT状态

TCP协议中的TIME_WAIT状态是指**在TCP连接关闭后，等待一段时间以确保所有网络上的数据包都被接收和处理完毕的状态**。在这个状态下，TCP连接的一端（通常是客户端）会保持一段时间的等待，不接受新的连接请求。

TIME_WAIT状态的存在是为了解决网络中出现的延迟和重复数据包的问题。当TCP连接关闭时，可能还有一些延迟的数据包在网络中传输，这些数据包可能会在连接关闭后到达，而接收方可能会误将这些数据包当作新的连接请求。为了避免这种混淆，发送方在关闭连接后会保持在TIME_WAIT状态一段时间，以确保这些延迟数据包能够被正确地丢弃。

在TIME_WAIT状态下，TCP连接的一端会保持连接信息（包括源IP地址、目标IP地址、源端口号、目标端口号等）的记录。这样可以避免与之前的连接产生冲突，确保网络通信的可靠性。

TIME_WAIT状态的持续时间通常是根据TCP协议的实现来确定的，一般为2倍的MSL（Maximum Segment Lifetime）值。MSL是指网络上数据包的最长生存时间，一般为2分钟左右。因此，一个TCP连接的TIME_WAIT状态持续时间通常为4分钟左右。

在某些情况下，TIME_WAIT状态可能会导致一些问题，如端口耗尽等。为了解决这些问题，可以通过修改操作系统的参数，如减小TIME_WAIT状态的持续时间或启用TCP连接复用等方法来优化网络性能。

### 维服务

微服务是一种软件架构风格，将一个大型应用程序拆分为一组小型、独立的服务，每个服务都可以独立开发、部署和扩展。每个服务都具有自己的代码库、数据库和业务逻辑，并通过轻量级的通信机制进行相互通信，通常使用 RESTful API、消息队列或 RPC（Remote Procedure Call）进行交互。

微服务架构的核心理念是将应用程序拆分为一组高内聚、低耦合的服务单元，每个服务单元可以独立开发、测试、部署和扩展。每个服务都专注于解决特定的业务需求，通过定义明确的接口进行通信，从而实现松耦合和高度可维护性。

微服务架构的优势包括：

1. **独立开发和部署**：由于每个微服务都是独立的，可以使用不同的编程语言、技术栈和开发团队进行开发，从而提高开发效率和灵活性。同时，每个微服务可以独立部署，使得部署过程更加灵活和可控。
    
2. 弹性和可扩展性：由于每个微服务都是独立的，可以根据需求独立进行扩展，从而实现更好的弹性和可扩展性。例如，可以**对负载较高的微服务进行水平扩展**，而不会影响其他微服务的性能。
    
3. 松耦合和可维护性：微服务架构通过明确的接口和通信机制实现微服务之间的解耦，使得每个微服务都可以独立进行修改、维护和测试，从而提高系统的可维护性和可演化性。
    
4. 可替代性和技术多样性：由于每个微服务都是独立的，可以根据需求和技术发展选择不同的技术栈和工具来实现每个微服务，从而实现技术的灵活性和可替代性。
    

然而，微服务架构也带来了一些挑战，包括分布式系统的复杂性、服务间通信的开销、服务拆分和服务发现等问题。因此，在设计和实施微服务架构时需要权衡各种因素，并选择适合特定需求和组织的解决方案。

总之，微服务架构通过将大型应用拆分为小型、可独立部署的服务单元，提供了灵活、可扩展和可维护的解决方案，适用于构建复杂和高可用的分布式系统。

分布式是指将一个系统或应用拆分成多个部分并分布在不同的计算机或服务器上运行，这些部分通过网络进行通信和协作，共同完成系统的功能。在分布式系统中，各个部分被称为节点，节点之间通过消息传递或远程调用来进行通信和数据交换。


### 分布式

分布式系统具有以下特点：

1. 高可用性：由于系统的各个组件分布在多个节点上，当某个节点出现故障或不可用时，系统可以通过其他节点来继续提供服务，从而实现高可用性。
    
2. 可扩展性：分布式系统可以通过增加更多的节点来扩展其处理能力和容量，从而满足不断增长的用户需求。
    
3. 容错性：分布式系统通常采用冗余设计，即在不同的节点上存储和处理相同的数据和任务，以防止单点故障或数据丢失。
    
4. 弹性和灵活性：由于系统的各个组件可以独立部署和运行，可以方便地进行组件的添加、删除或替换，从而实现系统的弹性和灵活性。
    

分布式系统面临一些挑战，例如网络通信延迟、节点间的一致性和同步、数据分片和复制、故障处理和恢复等问题。为了解决这些问题，分布式系统通常采用一些技术和算法，如分布式数据存储、一致性协议、故障检测与容错机制等。

分布式系统广泛应用于各个领域，包括互联网服务、大规模数据处理、云计算、物联网、区块链等。通过将系统的工作负载分布在多个节点上，分布式系统可以提供更高的性能、可靠性和可伸缩性，同时也带来了更高的复杂性和管理难度。因此，在设计和实施分布式系统时需要仔细考虑各种因素，并选择适合特定需求和场景的架构和技术。


### 中间键

中间件的概念起源于软件工程领域，特别是Web开发中。它是一种在处理请求和响应之间进行处理的软件组件或模块，用于增强系统的功能、可扩展性和可维护性。

中间件的出现是为了解决系统开发中的一些共性问题，例如：

1. 代码复用：通过中间件，可以将一些通用的逻辑或功能封装起来，供多个请求或模块复用，减少了代码的冗余和重复编写。
    
2. 横切关注点（Cross-cutting Concerns）的处理：横切关注点指的是系统中与核心业务逻辑无关但又具有共性的功能，例如日志记录、权限验证、错误处理等。中间件可以在请求和响应的处理过程中插入这些横切关注点的逻辑，提高了代码的可维护性和可扩展性。
    
3. 请求和响应的处理流程控制：中间件可以在请求到达和响应返回的过程中，对请求和响应进行处理和转换。这样可以对请求进行预处理、过滤或转换，同时对响应进行加工或修改，实现更灵活的请求响应处理流程控制。
    

在Web开发中，中间件常常被用于处理HTTP请求和响应。例如，在一个Web框架中，可以定义多个中间件来实现日志记录、路由解析、身份验证、缓存等功能。每个中间件按照定义的顺序对请求进行处理，然后将请求传递给下一个中间件，最终生成响应并返回给客户端。

总而言之，中间件是一种通用的软件组件或模块，用于处理请求和响应之间的逻辑和功能。它提供了一种可插拔、可扩展的方式来增强系统的功能和可维护性，同时也提供了更灵活的请求响应处理流程控制机制。


### client如何实现长连接
-  TCP协议的`KeepAlive`机制
- 长：数据库的连接
- 短：web ajax 请求


### put 幂等

在 HTTP 协议中，PUT 方法被定义为幂等的，这意味着多次执行相同的 PUT 请求会得到相同的结果，不会对服务器产生副作用。

PUT 方法的幂等性是通过以下两个方面来实现的：

1. 目标资源的唯一性：PUT 请求通常会指定一个目标资源的 URL，通过该 URL 定位到要更新的资源。在多次执行相同的 PUT 请求时，请求的 URL 是不变的，因此会针对同一个资源进行更新操作。
    
2. 请求的副作用：PUT 请求只会对目标资源进行更新操作，而不会引起其他副作用。这意味着多次执行相同的 PUT 请求不会改变服务器的状态，也不会对其他资源产生影响。
    

为了确保 PUT 请求的幂等性，开发者需要遵循以下几点：

1. 请求的内容和目标资源的状态应该一致：即每次执行相同的 PUT 请求时，请求中的数据应该与目标资源的状态一致。如果目标资源的状态已经满足请求中的数据，再次执行 PUT 请求也应该保持不变。
    
2. 请求的幂等性应该在服务端实现：开发者应该在服务端的请求处理逻辑中保证 PUT 请求的幂等性，例如在数据库更新操作中使用唯一的标识符来保证每个请求只执行一次更新操作。
    

总结：PUT 请求的幂等性是通过请求的目标资源唯一性和请求的副作用来实现的。开发者需要保证请求的内容和目标资源的状态一致，并在服务端实现幂等性来确保多次执行相同的 PUT 请求得到相同的结果。


### SQLx 和 GORM 比较

SQLx 和 GORM 都是 Go 语言中常用的数据库操作工具，它们有不同的设计理念和特点，下面是对它们进行比较的一些方面：

1. 设计理念：
    
    - SQLx：SQLx 是一个简单而轻量级的工具，旨在提供对数据库的基本操作支持，同时保持接口的简洁性和直观性。它提供了基本的 SQL 语句执行、查询参数绑定和结果映射等功能。
    - GORM：GORM 是一个功能丰富的 ORM（对象关系映射）库，它提供了更高级的数据库操作功能，包括模型定义、关联关系处理、预加载、事务管理、数据库迁移等。GORM 追求一种更面向对象的数据库访问方式，尽量隐藏底层 SQL 的细节，提供更高层次的抽象。
2. 查询语法：
    
    - SQLx：SQLx 提供了直接执行 SQL 语句的方法，可以通过参数绑定方式进行查询，并将查询结果映射到结构体中。
    - GORM：GORM 提供了更灵活的查询语法，支持链式调用的方式构建查询，可以进行条件筛选、排序、分页等操作，并且支持预加载关联数据。
3. 数据库支持：
    
    - SQLx：SQLx 支持多种数据库，包括 MySQL、PostgreSQL、SQLite 等，可以通过不同的数据库驱动进行连接。
    - GORM：GORM 也支持多种数据库，包括 MySQL、PostgreSQL、SQLite、SQL Server 等，并且提供了针对不同数据库的特定功能支持。
4. 生态系统和扩展性：
    
    - SQLx：SQLx 是一个相对简洁的工具，没有过多的附加功能，但它可以与其他库和工具很好地集成，如 go-zero 框架的组件。
    - GORM：GORM 是一个功能丰富的 ORM 库，它提供了丰富的特性和插件机制，可以灵活地扩展和定制。同时，GORM 有一个活跃的社区，提供了许多扩展和插件供开发者使用。

综上所述，SQLx 更注重基本的数据库操作和性能，适合那些只需要基本 CRUD 操作的项目；而 GORM 则提供了更高级的 ORM 功能和更丰富的查询语法，适合复杂的业务场景和需要对象关系映射的项目。选择使用哪个工具，取决于您的具体需求和偏好。


### 依赖注入

依赖注入（Dependency Injection，简称DI）是一种软件设计模式，用于管理组件之间的依赖关系。它的核心思想是通过外部将依赖关系传递给组件，而不是组件自己创建或查找依赖关系。

在传统的软件设计中，组件通常会直接创建或查找它们所依赖的其他组件。这样的做法会导致组件与其依赖紧密耦合，难以重用和测试。而使用依赖注入，可以将依赖关系的创建和管理交给外部的容器或框架，从而解耦组件之间的关系，提高代码的可测试性和可维护性。

依赖注入的主要概念如下：

1. 依赖关系（Dependency）：组件 A 依赖于组件 B，意味着组件 A 需要使用组件 B 提供的功能或数据。
    
2. 依赖注入容器（Dependency Injection Container）：是一个管理和创建依赖关系的容器，负责创建组件实例并将依赖关系注入到组件中。
    
3. 依赖注入方式（Dependency Injection Method）：有三种常见的依赖注入方式：
    
    - 构造函数注入（Constructor Injection）：通过构造函数将依赖关系传递给组件。
    - 属性注入（Property Injection）：通过公开的属性或字段将依赖关系注入到组件。
    - 方法注入（Method Injection）：通过调用特定的方法将依赖关系传递给组件。

依赖注入的主要优势包括：

- 解耦性：依赖注入降低了组件之间的耦合度，使得组件更加独立和可复用。
- 可测试性：通过将依赖关系注入到组件中，可以方便地替换和模拟依赖对象，从而简化单元测试的编写。
- 可扩展性：通过依赖注入容器管理依赖关系，可以轻松添加、替换或删除组件，而无需修改组件本身的代码。

总而言之，依赖注入是一种通过外部传递依赖关系的方法，用于解耦组件之间的依赖关系，并提高代码的可测试性和可维护性。它可以通过依赖注入容器来管理依赖关系的创建和传递，从而实现更灵活和可扩展的软件设计。


### 为什么后端总是要 copy 一遍

在后端开发中，经常会涉及到从一个对象复制数据到另一个对象的操作。这种操作通常被称为"拷贝"或"复制"，它的目的是将一个对象的数据赋值给另一个对象，以便在后续的处理中使用。

有几个原因解释了为什么在后端开发中需要进行拷贝操作：

1. 数据隔离：拷贝操作可以创建一个新的对象，使得原始对象和拷贝对象之间相互独立，互不影响。这在并发或并行处理中特别重要，以避免不同线程之间的数据竞争和冲突。
    
2. 安全性：通过拷贝操作，可以防止不小心修改原始对象的数据。如果直接引用原始对象，可能会导致意外修改或破坏原始数据，而通过拷贝操作，可以在拷贝对象上进行修改，而不会影响到原始对象。
    
3. 数据转换：拷贝操作可以用于数据类型的转换，将一个类型的对象转换为另一个类型的对象。这在数据层面的转换和适配中非常常见，例如将**数据库查询结果**映射到领域对象或将**领域对象**转换为传输对象。
    

虽然在一些情况下可以直接引用原始对象，但通过拷贝操作可以提供更好的封装性、可维护性和安全性。它可以确保对象的独立性，并提供一种清晰的方式来处理和修改数据。因此，拷贝操作在后端开发中是一种常见的操作手段。


### get query 和path 区别

在 HTTP 请求中，有不同的方式来传递参数，其中两种常用的方式是通过查询字符串（Query String）和路径参数（Path Parameter）。

1. 查询字符串（Query String）：
    
    - 使用 `?` 字符将 URL 的路径和查询字符串分隔开。
    - 查询字符串以 `key=value` 的形式出现，多个参数之间使用 `&` 符号分隔。
    - 例如：`http://example.com/path?key1=value1&key2=value2`
    - 在 Go 中，可以使用 `r.URL.Query()` 方法获取查询字符串参数的键值对。
2. 路径参数（Path Parameter）：
    
    - 路径参数是将参数直接嵌入 URL 的路径中，通常用于表示资源的标识或唯一值。
    - 路径参数使用占位符的形式，通常由大括号 `{}` 括起来。
    - 例如：`http://example.com/path/{param}`
    - 在 Go 的路由中，可以使用路由库（如 Gorilla Mux）定义带有路径参数的路由，并通过参数提取器获取路径参数的值。

区别：

- 查询字符串（Query String）适合传递可选参数、筛选条件或较长的参数列表。它们可以以键值对的形式进行编码，并在 URL 中明确表示参数的名称和值。
- 路径参数（Path Parameter）适合表示唯一标识或资源的属性。路径参数直接嵌入到 URL 路径中，使 URL 更具描述性和可读性。

根据具体的应用场景和需求，可以选择使用查询字符串或路径参数来传递参数。一般而言，如果参数是必需的、对资源进行唯一标识或需要进行精确匹配，路径参数更适合；如果参数是可选的、用于过滤或传递较长的参数列表，查询字符串更适合。



### grpc为啥好，基本原理是什么，和http比呢

gRPC 是一种高性能、跨语言的远程过程调用（RPC）框架，具有以下几个优点：

1. 高性能：gRPC 使用基于 Protocol Buffers 的二进制协议，以及基于 HTTP/2 的多路复用和流控制机制，实现了高效的数据传输和低延迟的通信。这使得 gRPC 在网络传输效率和性能方面具有优势。
    
2. 跨语言支持：gRPC 支持多种编程语言，包括 Go、Java、Python、C++ 等，使得不同语言的应用程序可以轻松地进行跨语言的通信。这种跨语言的特性使得 gRPC 在分布式系统中的多语言环境下具有良好的互操作性。
    
3. 强大的消息编码和类型定义：gRPC 使用 Protocol Buffers（简称 Protobuf）作为消息的编码和类型定义工具。Protobuf 提供了简洁的消息结构、高效的编码格式和灵活的扩展性，使得数据在传输过程中更紧凑、更可靠，并且易于定义和维护。
    
4. 自动代码生成：gRPC 提供了丰富的代码生成工具，能够根据定义的服务和消息结构自动生成客户端和服务器端的代码。这样可以大大简化开发工作，减少手写代码的错误和工作量。
    

相比之下，HTTP 是一种常用的应用层协议，用于在客户端和服务器之间进行通信。与 gRPC 相比，HTTP 具有以下一些特点：

1. 文本协议：HTTP 使用文本格式（如 JSON、XML）来表示数据，相对于二进制格式，文本格式在传输效率和数据大小方面会有一些额外的开销。
    
2. 单向请求-响应模式：HTTP 的通信模式是一次请求对应一次响应，即客户端发起请求，服务器返回响应。而 gRPC 支持双向流式通信，允许客户端和服务器同时进行数据的发送和接收。
    
3. RESTful 风格：HTTP 常用于构建 RESTful 风格的服务，通过 URL 和 HTTP 方法（GET、POST、PUT、DELETE 等）来表示不同的资源和操作。而 gRPC 是基于 RPC 的，更注重定义和调用服务方法。
    

总体而言，gRPC 和 HTTP 在应用场景和特性上有一些区别。gRPC 更适合构建高性能、跨语言的服务，特别适用于微服务架构和大规模分布式系统。而 HTTP 更广泛应用于 Web 开发和传统的客户端-服务器通信，适用于各种类型的应用。选择 gRPC 还是 HTTP 取决于具体的需求和应用场景。