## Data structure

### HashMap

HashMap 是一种常见的数据结构，用于实现键值对映射关系的存储和检索。它通常用于存储具有唯一键的数据，这些键与对应的值关联在一起，以便快速查找和检索值。

以下是 HashMap 的基本解释：

- **键值对（Key-Value Pairs）**：HashMap 存储的数据是由键值对组成的。每个键都是唯一的，与一个特定的值相关联。这意味着你可以使用键来查找和访问相应的值。
    
- **哈希函数（Hash Function）**：HashMap 使用哈希函数将键映射到内部数组的特定索引位置。这个哈希函数计算出一个整数（哈希码），然后将它映射到数组的特定位置。
    
- **内部数组（Internal Array）**：HashMap 内部维护一个数组，该数组的大小通常会根据数据量动态调整。每个数组元素可以容纳一个键值对。
    
- **冲突处理（Collision Resolution）**：由于哈希函数可能将多个不同的键映射到相同的索引位置，因此可能会出现冲突。HashMap 使用不同的方法来解决这些冲突，最常见的方法是链式哈希（Chaining），即在同一个索引位置存储一个链表或其他数据结构来容纳多个键值对。
    
- **快速检索**：HashMap 具有快速的查找性能。通过哈希函数，它可以在平均情况下以常量时间复杂度 O(1) 找到给定键的值。但在最坏情况下，如果有很多哈希冲突，查找操作可能会变得较慢，最坏时间复杂度为 O(n)，其中 n 是键值对的数量。
    
- **动态大小调整**：HashMap 通常会在达到一定负载因子（load factor）时自动调整其内部数组的大小，以保持合理的性能。这意味着它可以适应不同数量的键值对而不需要手动管理数组大小。
    
- **无序性**：HashMap 内部元素的存储顺序通常是不确定的。如果需要按照特定顺序访问元素，可以使用其他数据结构，如 TreeMap。

## Algorithm

### 1亿条数据动态增长，取top10，怎么实现

对于动态增长的数据集，需要一种高效的算法来获取前N个最大值（Top N）。以下是一种基于最小堆（Min-Heap）的常见算法来解决这个问题：

1. 创建一个大小为N的最小堆，并将数据集的前N个元素插入堆中。
    
2. 对于剩余的数据元素，依次进行以下操作：
    
    - 如果当前元素比最小堆的根节点大，则将根节点替换为当前元素，并对最小堆进行调整，以保持堆的特性。
    - 如果当前元素比最小堆的根节点小或相等，则忽略该元素。
3. 当所有的数据元素都被处理后，最小堆中的元素即为前N个最大值。
    

这种方法的时间复杂度为O(NlogN)，其中N是前N个最大值的数量。通过维护最小堆，我们可以在动态增长的数据集中保持较小的内存占用，并及时获取最新的Top N结果。

请注意，具体实现可能因编程语言和数据结构库的不同而有所差异。在实际应用中，还可以结合其他优化技术，如并行计算、分布式计算或增量计算，以提高性能和效率。


### 深度优先搜索（DFS）和广度优先搜索（BFS）

深度优先搜索（DFS）和广度优先搜索（BFS）都是图或树等数据结构中用于遍历和搜索的算法，但它们的搜索方式和应用场景略有不同。

深度优先搜索（DFS）：

- 深度优先搜索是一种通过递归或使用栈的方式来遍历或搜索数据结构的算法。
- 在深度优先搜索中，从一个节点开始，不断探索当前节点的子节点，直到到达最深层的节点，然后再返回继续探索其他分支。
- DFS 常常用于解决能否到达某个目标状态，或者找到一条路径的问题。在某些情况下，DFS 可能会陷入无限循环，需要额外的控制来避免。

广度优先搜索（BFS）：

- 广度优先搜索是一种通过使用队列的方式来遍历或搜索数据结构的算法。
- 在广度优先搜索中，从一个节点开始，首先探索当前节点的所有邻居节点，然后逐层向外扩展，先探索距离起始节点更近的节点，再探索更远的节点。
- BFS 常常用于寻找最短路径、最短步数等问题，也可以用于遍历图或树的所有节点。

总结：

- DFS 通过递归或栈，深入地探索一个分支，再返回并探索其他分支，适合解决能否到达目标状态或找到一条路径的问题。
- BFS 通过队列，先广度地探索距离起始节点更近的节点，逐层扩展，适合解决寻找最短路径或最短步数等问题。

在具体应用中，选择使用深度优先搜索还是广度优先搜索取决于问题的性质以及数据结构的特点。

### 动态规划

动态规划（Dynamic Programming，简称 DP）是一种常见的算法思想，用于解决一类具有重叠子问题和最优子结构性质的问题。**它通过将问题分解成子问题，并保存子问题的解，以避免重复计算，从而有效地降低问题的复杂度。**

动态规划的核心思想是将原问题分解成若干个子问题，然后按照一定的顺序求解子问题，最终得到原问题的解。在这个过程中，动态规划会通过记录已解决的子问题的结果，避免重复计算，从而提高算法的效率。

动态规划通常适用于以下类型的问题：

1. 重叠子问题：问题的求解过程中涉及到重复计算同一子问题。
2. 最优子结构：问题的最优解可以通过子问题的最优解来构造。

动态规划通常有两种解决方法：自顶向下（Top-Down）和自底向上（Bottom-Up）。

- 自顶向下：从原问题开始，递归地分解成子问题，通过递归调用解决子问题，并保存子问题的解。这种方法通常使用递归或记忆化搜索。
- 自底向上：**从子问题开始，逐步递推求解原问题，将子问题的解保存起来，避免重复计算。** 这种方法通常使用迭代方式，通过循环来求解。

总之，动态规划是一种高效的算法思想，适用于解决各种复杂的优化问题，例如最短路径、最大子序列和、背包问题等。理解动态规划的关键是找到问题的重叠子问题和最优子结构，然后设计出合适的状态转移方程和存储方式，以实现高效求解。

### 经典排序 Sort

#### 基本排序，哪些是稳定的
- 稳定：
	- 冒泡排序
	- 插入排序
	- 归并排序
- 不稳定
	- 选择排序
	- 希尔排序
	- 快速排序
	- 堆排序


#### 选择排序

```go
// SelectionSort 选择排序 (selection sort) O(n^2) O(1) 不稳定
func SelectionSort(arr []int) []int {

	for i := 0; i < len(arr); i++ {
		min := i

		for j := i + 1; j < len(arr); j++ {
			if arr[j] < arr[min] {
				min = j
			}
		}
		arr[i], arr[min] = arr[min], arr[i]
	}

	return arr
}
```

#### 冒泡排序

```go
// BubbleSort 冒泡排序 (bubble sort) O(n^2)->O(n) O(1) 稳定
func BubbleSort(arr []int) []int {
	swapped := true

	for swapped {
		swapped = false
		for i := 0; i < len(arr)-1; i++ {
			if arr[i+1] < arr[i] {
				arr[i+1], arr[i] = arr[i], arr[i+1]
				swapped = true
			}
		}
	}

	return arr
}
```

#### 插入排序

```go
// InsertionSort 插入排序 (insertion sort) O(n^2)->O(n) O(1) 稳定
func InsertionSort(arr []int) []int {
	for i := 1; i < len(arr); i++ {
		tmpArr := arr[i]
		j := i
		for ; j > 0 && arr[j-1] >= tmpArr; j-- {
			arr[j] = arr[j-1]
		}
		arr[j] = tmpArr
	}
	return arr
}
```

#### 希尔排序

```go
// ShellSort 希尔排序 (shell sort) O(n^2)->O(n) O(1) 不稳定
func ShellSort(arr []int) []int {
	for d := int(len(arr) / 2); d > 0; d /= 2 {
		for i := d; i < len(arr); i++ {
			for j := i; j >= d && arr[j-d] > arr[j]; j -= d {
				arr[j], arr[j-d] = arr[j-d], arr[j]
			}
		}
	}
	return arr
}
```

#### 归并排序

```go
// 归并排序 (merge sort) O(logN) O(N) 稳定
func merge(a []int, b []int) []int {

	var r = make([]int, len(a)+len(b))
	var i = 0
	var j = 0

	for i < len(a) && j < len(b) {

		if a[i] <= b[j] {
			r[i+j] = a[i]
			i++
		} else {
			r[i+j] = b[j]
			j++
		}

	}

	for i < len(a) {
		r[i+j] = a[i]
		i++
	}
	for j < len(b) {
		r[i+j] = b[j]
		j++
	}

	return r

}

// Mergesort 合并两个数组 O(N/logN)
func Mergesort(items []int) []int {

	if len(items) < 2 {
		return items

	}

	var middle = len(items) / 2
	var a = Mergesort(items[:middle])
	var b = Mergesort(items[middle:])
	return merge(a, b)

}
```

#### 三向切分快速排序

```go
// QuickSort 三向切分快速排序 (quick sort) O(logN)->O(N^2) O(log2N) 不稳定
func QuickSort(arr []int) []int {

	if len(arr) <= 1 {
		return arr
	}

	pivot := arr[rand.Intn(len(arr))]

	lowPart := make([]int, 0, len(arr))
	highPart := make([]int, 0, len(arr))
	middlePart := make([]int, 0, len(arr))

	for _, item := range arr {
		switch {
		case item < pivot:
			lowPart = append(lowPart, item)
		case item == pivot:
			middlePart = append(middlePart, item)
		case item > pivot:
			highPart = append(highPart, item)
		}
	}

	lowPart = QuickSort(lowPart)
	highPart = QuickSort(highPart)

	lowPart = append(lowPart, middlePart...)
	lowPart = append(lowPart, highPart...)

	return lowPart
}
```

#### 堆排序

```go
// 堆排序 (heap sort)
type maxHeap struct {
	slice    []int
	heapSize int
}

func buildMaxHeap(slice []int) maxHeap {
	h := maxHeap{slice: slice, heapSize: len(slice)}
	for i := len(slice) / 2; i >= 0; i-- {
		h.MaxHeapify(i)
	}
	return h
}

func (h maxHeap) MaxHeapify(i int) {
	l, r := 2*i+1, 2*i+2
	max := i
	size := h.size()

	if l < size && h.slice[l] > h.slice[max] {
		max = l
	}
	if r < size && h.slice[r] > h.slice[max] {
		max = r
	}
	if max != i {
		h.slice[i], h.slice[max] = h.slice[max], h.slice[i]
		h.MaxHeapify(max) // important
	}
}

func (h maxHeap) size() int { return h.heapSize }

// HeapSort O(logN) O(1) 不稳定
func HeapSort(slice []int) []int {
	h := buildMaxHeap(slice)
	for i := len(h.slice) - 1; i >= 1; i-- {
		h.slice[0], h.slice[i] = h.slice[i], h.slice[0]
		h.heapSize--
		h.MaxHeapify(0)
	}
	return h.slice
}
```

#### 计数排序

```go
// 计数排序（Counting Sort） O(n) O(n)// 输入的数据必须是有确定范围的整数  
```

#### 桶排序

```go
// 桶排序（Bucket Sort）O(n) O(n)  
```

#### 基数排序

```go
// 基数排序（Radix Sort）O(n) O(n)
```



## Design patterns

##### **单例模式（Singleton Pattern）**：

1. **目的**：确保一个类只有一个实例，并提供全局访问点以便于访问该实例。
    
2. **使用场景**：当一个类需要在整个应用程序中只有一个实例时，可以使用单例模式。例如，数据库连接池、日志记录器、线程池等。
    
3. **实现方式**：通常通过类的静态成员或全局变量来保存唯一的实例，并提供一个静态方法来获取该实例。确保构造函数是私有的，以防止外部代码创建多个实例。
    

##### **工厂模式（Factory Pattern）**：

1. **目的**：工厂模式用于创建对象，但将对象的创建过程与客户端代码分离，以便于解耦。它提供了一种创建对象的抽象接口，客户端通过该接口请求对象而不需要了解对象的具体类。
    
2. **使用场景**：当需要创建一组相关或相似的对象，但不希望客户端直接实例化这些对象时，可以使用工厂模式。例如，图形库可以有一个抽象工厂，用于创建不同类型的图形对象。
    
3. **实现方式**：工厂模式通常包括一个抽象工厂接口和多个具体工厂类，每个具体工厂类负责创建一组相关对象。客户端代码通过调用工厂方法来创建对象，而不需要知道对象的具体类型。
    

**区别**：

1. **目的不同**：单例模式的目的是确保一个类只有一个实例，工厂模式的目的是将对象的创建和使用分离。
    
2. **用途不同**：单例模式通常用于管理全局唯一的资源，而工厂模式用于创建一组相关对象。
    
3. **实现方式不同**：单例模式使用静态成员或全局变量保存唯一实例，工厂模式通过工厂接口和具体工厂类来创建对象。
    
4. **关注点不同**：单例模式关注于对象的唯一性，工厂模式关注于对象的创建和抽象。