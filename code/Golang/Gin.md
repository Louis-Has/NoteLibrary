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