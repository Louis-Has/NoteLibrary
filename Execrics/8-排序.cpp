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
        // printf("now min is :%d \n", min->data);

        SElemType temp = head->data;
        head->data = min->data;
        min->data = temp;

        head = head->next;
    }
};

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
