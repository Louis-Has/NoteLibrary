## Gin
### model tag gorm
	1.  column 指定 db 列名
	2.  type 列数据类型
	3.  size
	4.  primaryKey
	5.  unique
	6.  default
	7.  not null
	8.  autoIncrement
	9.  index
	10.  uniqueIndex
	11.  comment

### Restful 传递参数

1. 查询字符串（Query String）

```go
/user?uid=222&page=1

ctx.Query("uid")
ctx.DefaultQuery("page", 0)
```

2. 路径参数（Path Parameter）

```go
 /user/:name

ctx.Param("name")
```

3. 请求体（Post）

```go
 ctx.PostForm("user")
 ctx.DefaultPostForm("user","ddd")
```

### 表单验证 Bind

```go
 ctx.ShouldBind(&User)
```


### 中间件 middleware

使用
```go
router.Use(middleware)
```

ddd
```go
ctx.Next()
ctx.Abort()

ctx.Set("name","ddd")
ctx.Get("name")
```

6.  file,_ := ctx.FormFile("file")
	1.  ctx.SaveUploadedFile(file, dst)
	2.  extName := path.Ext(file.Filename)

8.  errors.Is(err, gorm.ErrRecordNotFound)

## Gorm

### 处理错误

```go
// 检查错误是否为 RecordNotFound
err := db.First(&user, 100).Error
errors.Is(err, gorm.ErrRecordNotFound)

```

### 链式方法

```go
// ## 新建会话方法

tx := db.Where("name = ?", "jinzhu").Session(&gorm.Session{})  
tx := db.Where("name = ?", "jinzhu").WithContext(context.Background())  
tx := db.Where("name = ?", "jinzhu").Debug()  
// `Session`, `WithContext`, `Debug` returns `*gorm.DB` marked as safe to reuse, newly initialized `*gorm.Statement` based on it keeps current conditions
```

### 迁移 AutoMigrate

```go
db.AutoMigrate(&User{})
```

## sqlx 和 gorm 比较

SQLx 和 GORM 都是 Go 语言中常用的数据库操作工具，它们有不同的设计理念和特点，下面是对它们进行比较的一些方面：


1. 设计理念：
    
    - SQLx：SQLx 是一个简单而轻量级的工具，旨在提供对数据库的基本操作支持，同时保持接口的简洁性和直观性。它提供了基本的 SQL 语句执行、查询参数绑定和结果映射等功能。
    - GORM：GORM 是一个功能丰富的 ORM（对象关系映射）库，它提供了更高级的数据库操作功能，包括模型定义、关联关系处理、预加载、事务管理、数据库迁移等。GORM 追求一种更面向对象的数据库访问方式，尽量隐藏底层 SQL 的细节，提供更高层次的抽象。
2. 查询语法：
    
    - SQLx：SQLx 提供了直接执行 SQL 语句的方法，可以通过参数绑定方式进行查询，并将查询结果映射到结构体中。
    - GORM：GORM 提供了更灵活的查询语法，支持链式调用的方式构建查询，可以进行条件筛选、排序、分页等操作，并且支持预加载关联数据。

3. 生态系统和扩展性：
    
    - SQLx：SQLx 是一个相对简洁的工具，没有过多的附加功能，但它可以与其他库和工具很好地集成，如 go-zero 框架的组件。
    - GORM：GORM 是一个功能丰富的 ORM 库，它提供了丰富的特性和插件机制，可以灵活地扩展和定制。同时，GORM 有一个活跃的社区，提供了许多扩展和插件供开发者使用。

综上所述，SQLx 更注重基本的数据库操作和性能，适合那些只需要基本 CRUD 操作的项目；而 GORM 则提供了更高级的 ORM 功能和更丰富的查询语法，适合复杂的业务场景和需要对象关系映射的项目。选择使用哪个工具，取决于您的具体需求和偏好。