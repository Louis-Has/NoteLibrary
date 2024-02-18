#include <iostream>

using namespace std;
typedef int SElemType;

typedef struct node
{
    SElemType data;
    struct node *next;
} *List;

List CreateLinkList(SElemType arr[], int len)
{
    List head = nullptr;
    List tail = head;

    for (size_t i = 0; i < len; i++)
    {
        List temp = new node{arr[i]};

        if (head)
        {
            tail->next = temp;
            tail = temp;
        }
        else
        {
            head = temp;
            tail = head;
        }
    }

    return head;
};

void PrintList(List ls)
{
    if (!ls)
    {
        return;
    }
    cout << ls->data << " -> ";
    PrintList(ls->next);
};

void PrintAllList(List ls)
{
    PrintList(ls);
    cout << "null" << endl;
};

// （1）试以单链表为存储结构，实现简单选择排序算法。
void LinkSelectedSort(List ls)
{
    if (!ls || !ls->next)
    {
        return;
    }

    List head = ls;
    while (head)
    {
        List min = head, tail = head->next;

        while (tail)
        {
            if (tail->data < min->data)
            {
                min = tail;
            }
            tail = tail->next;
        }
        // printf("now min is : %d \n", min->data);

        SElemType temp = head->data;
        head->data = min->data;
        min->data = temp;

        head = head->next;
    }
};

// （2）有n个记录存储在带头结点的双向链表中，现用双向冒泡排序法对其按上升序进行排序，请写出这种排序的算法。
// （注：双向冒泡排序即相邻两趟排序向相反方向冒泡）。

// （3）设有顺序放置的n个桶，每个桶中装有一粒砾石，每粒砾石的颜色是红，白，蓝之一。
// 要求重新安排这些砾石，使得所有红色砾石在前，所有白色砾石居中，所有蓝色砾石居后，
// 重新安排时对每粒砾石的颜色只能看一次，并且只允许交换操作来调整砾石的位置。

// （4）编写算法，对n个关键字取整数值的记录序列进行整理，以使所有关键字为负值的记录排在关键字为非负值的记录之前，
// 要求：
// ① 采用顺序存储结构，至多使用一个记录的辅助存储空间；
// ② 算法的时间复杂度为O(n)。

// （5）借助于快速排序的算法思想，在一组无序的记录中查找给定关键字值等于key的记录。
// 设此组记录存放于数组r[l..n]中。若查找成功，则输出该记录在r数组中的位置及其值，否则显示“not find”信息。
// 请简要说明算法思想并编写算法。

// （6）有一种简单的排序算法，叫做计数排序。
// 这种排序算法对一个待排序的表进行排序，并将排序结果存放到另一个新的表中。
// 必须注意的是，表中所有待排序的关键字互不相同，计数排序算法针对表中的每个记录，扫描待排序的表一趟，统计表中有多少个记录的关键字比该记录的关键字小。
// 假设针对某一个记录，统计出的计数值为c，那么，这个记录在新的有序表中的合适的存放位置即为c。
//  ① 给出适用于计数排序的顺序表定义；
//  ② 编写实现计数排序的算法；
//  ③ 对于有n个记录的表，关键字比较次数是多少？
//  ④ 与简单选择排序相比较，这种方法是否更好？为什么？


int main()
{
    SElemType arr[] = {41, 12, 4, 17, 8, 3, 12};
    int len = sizeof(arr) / sizeof(arr[0]);

    List ls = CreateLinkList(arr, len);

    cout << "Create LinkList over : ";
    PrintAllList(ls);

    // （1）试以单链表为存储结构，实现简单选择排序算法。
    LinkSelectedSort(ls);
    cout << "SelectedSort :";
    PrintAllList(ls);

    return 0;
};
