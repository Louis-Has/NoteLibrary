```bash
docker run -d --hostname my-rabbit --name rabbit -p 15672:15672 -p 5672:5672 rabbitmq
```

```bash
rabbitmq-plugins enable rabbitmq_management
```

[rabbitmq_management](http://localhost:15672)

### 四种交换机类型

#### Direct exchange（直连交换机）
直连型交换机（direct exchange）是根据消息携带的路由键（routing key）将消息投递给对应队列的，步骤如下：

将一个队列绑定到某个交换机上，同时赋予该绑定一个路由键（routing key）
当一个携带着路由值为R的消息被发送给直连交换机时，交换机会把它路由给绑定值同样为R的队列。
#### Fanout exchange（扇型交换机）Work Queues
扇型交换机（funout exchange）将消息路由给绑定到它身上的所有队列。不同于直连交换机，路由键在此类型上不启任务作用。如果N个队列绑定到某个扇型交换机上，当有消息发送给此扇型交换机时，交换机会将消息的发送给这所有的N个队列

```go
        q, err := ch.QueueDeclare(
                "task_queue", // name
                true,         // durable
                false,        // delete when unused
                false,        // exclusive
                false,        // no-wait
                nil,          // arguments
        )
```
#### Topic exchange（主题交换机）Publish/Subscribe
主题交换机（topic exchanges）中，队列通过路由键绑定到交换机上，然后，交换机根据消息里的路由值，将消息路由给一个或多个绑定队列。

扇型交换机和主题交换机异同：

对于扇型交换机路由键是没有意义的，只要有消息，它都发送到它绑定的所有队列上
对于主题交换机，路由规则由路由键决定，只有满足路由键的规则，消息才可以路由到对应的队列上

```go
        err = ch.ExchangeDeclare(
                "logs",   // name
                "fanout", // type
                true,     // durable
                false,    // auto-deleted
                false,    // internal
                false,    // no-wait
                nil,      // arguments
        )
```
#### Headers exchange（头交换机）
类似主题交换机，但是头交换机使用多个消息属性来代替路由键建立路由规则。通过判断消息头的值能否与指定的绑定相匹配来确立路由规则。
此交换机有个重要参数：”x-match”

当”x-match”为“any”时，消息头的任意一个值被匹配就可以满足条件
当”x-match”设置为“all”的时候，就需要消息头的所有值都匹配成功

### Ack

### ddd
### 参考文章：
1. [RabbitMQ(一) 入门与四种交换机类型](https://amos-x.com/index.php/amos/archives/rabbitmq_01/)
2. [RabbitMQ Tutorials](https://www.rabbitmq.com/getstarted.html)