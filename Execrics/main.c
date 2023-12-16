#include <stdio.h>
#include <stdlib.h>
// 数据结构
// 线性表

// 将两个递增的有序链表合并为 一个递增的有序链表。要求结果链表仍使用原来两个链表的存储空间，不另外占用其他的存储空间。表中不允许有重复的数据。
typedef struct node
{
   int data;          // 存储整数数据的成员
   struct node *next; // 指向下一个节点的指针
} Node, *pNode;

void TraverseList(pNode h)
{
   pNode p = h->next;
   while (p != NULL)
   {
      printf("%d", p->data);
      if (p->next != NULL)
      {
         printf(" -> ");
      }
      p = p->next;
   }
   printf("\n");
   return;
}

pNode CreateLinkList(int arr[], int size)
{
   pNode newLinkList = (pNode)malloc(sizeof(Node));
   pNode tail = newLinkList;
   tail->next = NULL;

   for (int i = 0; i < size; i++)
   {
      pNode newNode = (pNode)malloc(sizeof(Node));
      newNode->data = arr[i];
      newNode->next = NULL;
      tail->next = newNode;
      tail = newNode;
   }

   TraverseList(newLinkList);

   return newLinkList;
}

int main()
{
   int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 8, 8};
   CreateLinkList(arr, sizeof(arr) / sizeof(arr[0]));

   return 0;
}
