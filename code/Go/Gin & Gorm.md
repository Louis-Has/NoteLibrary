1.  model tag gorm
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

2.  /user?uid=222&page=1
	1.  ctx.Query("uid")
	2.  ctx.DefaultQuery("page", 0)

3.  /user/:name
	1.  ctx.Param("name")

4.  post body
	1.  ctx.PostForm("user")
	2.  ctx.DefaultPostForm("user","ddd")
	3.  ctx.ShouldBind(&User)

5.  middleware
	1.  router.Use(middleware)
	2.  ctx.Next()
	3.  ctx.Abort()
	4.  ctx.Set("name","ddd")
	5.  ctx.Get("name")
	6.  goroutine
		1.  ctx.Copy()
		2.  [当请求频率间隔小于goroutine退出的时间，goroutine拿着上下文的地址去取上下文中的数据是不一致的](https://jinfeijie.cn/post-777)

6.  file,_ := ctx.FormFile("file")
	1.  ctx.SaveUploadedFile(file, dst)
	2.  extName := path.Ext(file.Filename)

7.  cookie
	1.  ctx.Cookie("key")
	2.  ctx.SetCookie("key","value",MaxAge,"/")

8.  errors.Is(err, gorm.ErrRecordNotFound)
9.  链式方法 避免污染
	1.  tx := db.Where("name = ?", "jinzhu").Session(&gorm.Session{})
	2.  tx := db.Where("name = ?", "jinzhu").WithContext(context.Background())
	3.  tx := db.Where("name = ?", "jinzhu").Debug()

10.  Hook
11.  事务
	1.  SkipDefaultTransaction

12.  AutoMigrate 迁移

### sqlx 和 gorm 比较

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