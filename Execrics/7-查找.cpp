#include <iostream>

using namespace std;

typedef int SElemType;

typedef struct Node
{
    SElemType data;
    struct Node *left, *right;
} *BTree;

// （1）试写出折半查找的递归算法。

int BinSearch(int arr[], int val, int st, int en)
{
    if (st > en)
    {
        return -1;
    }

    int mid = (st + en) / 2;

    if (arr[mid] == val)
    {
        return mid;
    }

    if (val < arr[mid])
    {
        printf("find in %d - %d ,try : %d is  %d\n", st, en, mid, arr[mid]);

        return BinSearch(arr, val, 0, mid - 1);
    }

    if (val > arr[mid])
    {
        printf("find in %d - %d ,try : %d is  %d\n", st, en, mid, arr[mid]);

        return BinSearch(arr, val, mid + 1, en);
    }

    return -1;
};

// （2）试写一个判别给定二叉树是否为二叉排序树的算法。

// [题目分析] 根据二叉排序树中序遍历所得结点值为增序的性质，
// 在遍历中将当前遍历结点与其前驱结点值比较，即可得出结论，
// 为此设全局指针变量pre（初值为null）和全局变量flag，初值为true。
// 若非二叉排序树，则置flag为false。

Node *pre = nullptr;
bool flag = true;

void checkBST(BTree tr)
{
    if (!tr || !flag)
    {
        return;
    }

    checkBST(tr->left);

    printf("check point : %d ", tr->data); // print

    if (pre && pre->data >= tr->data)
    {
        printf("check %d >= %d \n", pre->data, tr->data);
        flag = false;

        printf(" failed\n");
        return;
    }

    printf(" over\n");

    pre = tr;

    checkBST(tr->right);
};


// （3）已知二叉排序树采用二叉链表存储结构，
// 根结点的指针为T，链结点的结构为（lchild,data,rchild），
// 其中lchild，rchild分别指向该结点左、右孩子的指针，data域存放结点的数据信息。
// 请写出递归算法，从小到大输出二叉排序树中所有数据值>=x的结点的数据。
// 要求先找到第一个满足条件的结点后，再依次输出其他满足条件的结点。

// [题目分析]本题算法之一是如上题一样，中序遍历二叉树，
// 在“访问根结点”处判断结点值是否≥x，如是则输出，并记住第一个≥x值结点的指针。
// 这里给出另一个算法，利用二叉排序树的性质，如果根结点的值>=x,则除左分枝中可能有<x的结点外都应输出。
// 所以从根结点开始查找，找到结点值<x的结点后，将其与双亲断开输出整棵二叉排序树。
// 如果根结点的值<x,则沿右子树查找第一个≥x的结点，找到后，与上面同样处理。


int main()
{
    []
    {
        int arr[] = {3, 4, 5, 7, 24, 30, 42, 54, 63, 72, 87, 95};
        int len = sizeof(arr) / sizeof(arr[0]);

        int val = 24;
        printf("BinSearch : find %d -> %d\n", val, BinSearch(arr, val, 0, len - 1));
    };

    []
    {
        BTree root = new Node{45,
                              new Node{12,
                                       new Node{3, nullptr, nullptr},
                                       new Node{37,
                                                new Node{24, nullptr, nullptr},
                                                nullptr}},
                              new Node{53,
                                       nullptr,
                                       new Node{100,
                                                new Node{61,
                                                         nullptr,
                                                         new Node{90,
                                                                  new Node{78, nullptr, nullptr},
                                                                  nullptr}},
                                                nullptr}}};

        checkBST(root);

        printf("CheckBTree : %s \n", flag ? "true" : "false");
    }();

    return 0;
}
