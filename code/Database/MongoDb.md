1.  集合
	1.  db.createCollection(name, options)

2.  文档
	1.  db.collection.insert(document)
		1.  insertOne
		2.  insertMany

	2. db.collection.update(\<query>, \<update>) 更新文档
	3. db.collection.find(query, projection) 查询文档
		1.  $or
		2.  db.collection.find(query, {_id:0, title: 1, by: 1})
		3.  db.collection.find( { qty: { $gt: 50 ,$lt: 80}} )
			1.  $gt -------- greater than >
			2.  $gte --------- gt equal >=
			3.  $lt -------- less than <
			4.  $lte --------- lt equal <=
			5.  $ne ----------- not equal !=
			6.  $eq -------- equal =
	
	4.  db.collection.find({"title" : {$type : 'string'}})
	5.  db.collection.find().limit(NUMBER).skip(NUMBER)
	6.  db.collection.find().sort({KEY:1}) 排序
	7.  db.collection.createIndex(keys, options) 索引
	8.  db.collection.aggregate(AGGREGATE_OPERATION) 聚合
		1.  db.collection.aggregate([{$group : {_id : "$by_user", num_tutorial : {$sum : 1}}}])
		2.  $project：修改输入文档的结构。可以用来重命名、增加或删除域，也可以用于创建计算结果以及嵌套文档。
		3.  $match：用于过滤数据，只输出符合条件的文档。$match使用MongoDB的标准查询操作。
		4.  $limit：用来限制MongoDB聚合管道返回的文档数。
		5.  $skip：在聚合管道中跳过指定数量的文档，并返回余下的文档。
		6.  $unwind：将文档中的某一个数组类型字段拆分成多条，每条包含数组中的一个值。
		7.  $group：将集合中的文档分组，可用于统计结果。
		8.  $sort：将输入文档排序后输出。
		9.  $geoNear：输出接近某一地理位置的有序文档。