```bash
docker run -d --hostname my-rabbit --name rabbit -p 15672:15672 -p 5672:5672 rabbitmq
```

```bash
rabbitmq-plugins enable rabbitmq_management
```

[rabbitmq_management](http://localhost:15672)


### 参考文章：
1. [RabbitMQ(一) 入门与四种交换机类型](https://amos-x.com/index.php/amos/archives/rabbitmq_01/)
2. [RabbitMQ Tutorials](https://www.rabbitmq.com/getstarted.html)