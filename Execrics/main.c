#include <stdio.h>
#include <stdlib.h>

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

   printf("create linklist: ");
   TraverseList(newLinkList);

   return newLinkList;
}

void MergeLinks(pNode la, pNode lb)
{
   pNode pa = la->next;
   pNode pb = lb->next;
   pNode pc = la; // important
   pNode tail = pc;

   while (pa && pb)
   {
      if (pa->data < pb->data)
      {
         // 取较小者La中的元素，将pa链接在pc的后面，pa指针后移
         tail->next = pa;
         tail = pa;
         pa = pa->next;
      }
      else if (pa->data > pb->data)
      {
         // 取较小者Lb中的元素，将pb链接在pc的后面，pb指针后移
         tail->next = pb;
         tail = pb;
         pb = pb->next;
      }
      else
      {
         // 相等时取La中的元素，删除Lb中的元素
         tail->next = pa;
         tail = pa;
         pa = pa->next;

         pNode temp = pb->next;
         free(pb);
         pb = temp;
      }
   }
   tail->next = pa ? pa : pb;
   printf("result: ");
   TraverseList(pc);
}

int main()
{
   int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 8};
   // CreateLinkList(arr, sizeof(arr) / sizeof(arr[0]));

   // 数据结构
   // 2.线性表
   // 2.2.1 将两个递增的有序链表合并为 一个递增的有序链表。要求结果链表仍使用原来两个链表的存储空间，不另外占用其他的存储空间。表中不允许有重复的数据。
   int arr11[] = {1, 2, 3, 4, 5, 7, 12};
   int arr12[] = {2, 4, 5, 6, 9};
   MergeLinks(CreateLinkList(arr11, 7), CreateLinkList(arr12, 5));

   return 0;
}
