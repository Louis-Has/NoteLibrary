## System

### errors

### viper

```bash
go get github.com/spf13/viper
```

- viper.ReadInConfig()
- viper.Unmarshal(&config)
	- viper.Get("app_name")

[Go 每日一库之 viper](https://darjun.github.io/2020/01/18/godailylib/viper/)

### zap 高性能日志库

```bash
go get -u go.uber.org/zap
go get github.com/lestrrat-go/file-rotatelogs
go get gopkg.in/natefinch/lumberjack.v2
```

优势 
- 使用非常简单。我们可以设置任何`io.Writer`作为日志记录输出并向其发送要写入的日志。
劣势
- 仅限基本的日志级别
    - 只有一个`Print`选项。不支持`INFO`/`DEBUG`等多个级别。
- 对于错误日志，它有`Fatal`和`Panic`
    - Fatal日志通过调用`os.Exit(1)`来结束程序
    - Panic日志在写入日志消息之后抛出一个panic
    - 但是它缺少一个ERROR日志级别，这个级别可以在不抛出panic或退出程序的情况下记录错误
- 缺乏日志格式化的能力——例如记录调用者的函数名和行号，格式化日期和时间格式。等等。
- 不提供日志切割的能力。

 zap.Option
- zap.AddCaller() 输出文件名和行号
- zap.AddCallerSkip(skip int) 输出的文件名和行号是调用封装函数的位置
- zap.AddStackTrace(lvl zapcore.LevelEnabler) 输出此次调用的堆栈

 file-rotatelogs
- 按日期切割

 Lumberjack
- 按文件大小切割

1. [golang高性能日志库zap的使用](https://jian1098.github.io/2020/12/16/42.golang%E9%AB%98%E6%80%A7%E8%83%BD%E6%97%A5%E5%BF%97%E5%BA%93zap%E7%9A%84%E4%BD%BF%E7%94%A8/)
2. [在Go语言项目中使用Zap日志库](https://www.liwenzhou.com/posts/Go/zap/#autoid-1-2-1)

### time/rate
[Golang 标准库限流器 time/rate 实现剖析](https://www.cyhone.com/articles/analisys-of-golang-rate/)
### ants 高性能且低损耗的 goroutine 池


## Time
### Cron 定时任务管理库

```go
 c := cron.New()
 
 c.AddFunc("@every 1s", func() {
    fmt.Println("tick every 1 second")
  })

 c.AddFunc("30 3-6,20-23 * * *", func() {
    fmt.Println("On the half hour of 3-6am, 8-11pm")
  })
```

`cron`库支持用 **5** 个空格分隔的域来表示时间。这 5 个域含义依次为：

- `Minutes`：分钟，取值范围`[0-59]`，支持特殊字符`* / , -`；
- `Hours`：小时，取值范围`[0-23]`，支持特殊字符`* / , -`；
- `Day of month`：每月的第几天，取值范围`[1-31]`，支持特殊字符`* / , - ?`；
- `Month`：月，取值范围`[1-12]`或者使用月份名字缩写`[JAN-DEC]`，支持特殊字符`* / , -`；
- `Day of week`：周历，取值范围`[0-6]`或名字缩写`[JUN-SAT]`，支持特殊字符`* / , - ?`。

### jobrunner 基于 cron 的定时任务管理库。
### carbon 日期时间的创建和运算
### copier 处理相同或不同结构体/map 之间的赋值。 


## Data
### cast  小巧、实用的类型转换库
### validator 使用最为广泛的数据校验库。

### casbin 灵活、强大的权限管理库，支持多种语言。


## Database

### redsync




