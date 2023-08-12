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

### 经典排序

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