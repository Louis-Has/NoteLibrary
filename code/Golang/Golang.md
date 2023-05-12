1.  struct 匿名字段 嵌入字段 重载字段 method重写
2.  如果不传Box的指针，那么SetColor接受的其实是Box的一个copy，也就是说method内对于颜色值的修改，其实只作用于Box的copy，而不是真正的Box。
3.  goroutine说到底其实就是协程，但是它比线程更小
4.  str,_ := username.(string) 类型断言
5.  panic
	1.  使用多值返回来返回错误