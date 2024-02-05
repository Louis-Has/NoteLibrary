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

    if (pre && pre->data >= tr->data)
    {
        printf("check %d >= %d \n", pre->data, tr->data);
        flag = false;
        return;
    }

    pre = tr;

    checkBST(tr->right);
};

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
        BTree root = new Node{2, new Node{1, nullptr, nullptr}, new Node{3, nullptr, nullptr}};
        checkBST(root);

        printf("CheckBTree : %s \n", flag ? "true" : "false");
    }();

    return 0;
}
