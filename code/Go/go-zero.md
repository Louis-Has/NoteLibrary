### ServiceContext & context

使用 `ServiceContext` 还是 `context.Context` 取决于你的具体需求和使用场景。

1. 使用 `ServiceContext` 的情况：
    
    - 当你使用 go-zero 框架进行服务开发时，可以使用 `ServiceContext` 来传递和共享与服务相关的上下文信息，如配置、请求上下文、元数据等。`ServiceContext` 提供了一些框架相关的功能和方法，方便你在服务中访问和操作这些信息。
    - 当你需要在服务中访问一些全局的服务配置或上下文信息时，可以将这些信息包装在 `ServiceContext` 中，以便在服务的不同方法或组件中使用。
2. 使用 `context.Context` 的情况：
    
    - 当你编写网络请求处理、并发任务、中间件等代码时，可以使用 `context.Context` 来传递请求相关的上下文信息，如请求的参数、请求的超时控制、请求的取消等。
    - 当你需要控制请求的生命周期，包括超时控制、取消操作等，可以使用 `context.Context` 提供的方法来管理请求的上下文。

需要注意的是，`ServiceContext` 是基于 `context.Context` 的扩展，你可以在需要的情况下将 `context.Context` 转换为 `ServiceContext` 或者从 `ServiceContext` 中获取原始的 `context.Context`，以便在服务的不同层次之间传递和共享上下文信息。

综上所述，如果你使用 go-zero 框架进行服务开发，建议使用 `ServiceContext` 来传递和共享与服务相关的上下文信息；而对于一般的请求处理和并发任务，可以使用标准库的 `context.Context` 来传递请求相关的上下文信息和管理请求的生命周期。


### 阿里云容器服务 go-zero

阿里云容器服务（Alibaba Cloud Container Service）和 Go-Zero 是两个不同的概念。

阿里云容器服务是阿里云提供的基于 Kubernetes 的云原生容器化应用管理服务，它允许用户在阿里云上轻松地创建、管理和运行容器化应用。您可以使用阿里云容器服务来构建和部署基于容器的应用，它提供了集群管理、自动扩缩容、应用部署、监控和日志等功能。

而 Go-Zero 是一种 Go 语言开发的微服务框架，它专注于解决微服务架构中的常见问题，如服务发现、负载均衡、接口调用、限流熔断、日志追踪等。Go-Zero 提供了一系列的工具和库，帮助开发人员更轻松地构建和管理微服务应用。

如果您想在阿里云容器服务上使用 Go-Zero，您可以将您的 Go-Zero 微服务应用容器化，并使用阿里云容器服务进行部署和管理。您可以使用 Docker 将 Go-Zero 应用打包为容器镜像，然后将镜像上传到阿里云容器镜像服务，并使用阿里云容器服务来创建和管理您的容器集群。

总结来说，阿里云容器服务是一种容器化应用管理服务，而 Go-Zero 是一种微服务框架，您可以在阿里云容器服务上部署和管理使用 Go-Zero 开发的微服务应用。

### 熔断怎么做的

### 服务降级怎么搞




1. [go-zero微服务实战系列（四、CRUD热热身）](https://www.cnblogs.com/kevinwan/p/16380728.html)
2. [goctl template 模板定制化](https://go-zero.dev/docs/tutorials/customization/template)