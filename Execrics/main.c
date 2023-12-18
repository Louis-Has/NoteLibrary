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
   if (!p)
   {
      printf("Empty!");
   }
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

void TraverseListAll(pNode h)
{
   pNode p = h;
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

pNode CreateLinkList(int arr[])
{
   int size = 0;
   while (arr[size] != -1)
   {
      size++;
   }

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

// 数据结构
// 2.线性表
// 2.2.1 将两个递增的有序链表合并为 一个递增的有序链表。
// 要求结果链表仍使用原来两个链表的存储空间，不另外占用其他的存储空间。
// 表中不允许有重复的数据。
int arr11[] = {1, 2, 3, 4, 5, 7, 12, -1};
int arr12[] = {2, 4, 5, 6, 9, -1};

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
         tail = tail->next;
         pa = pa->next;
      }
      else if (pa->data > pb->data)
      {
         // 取较小者Lb中的元素，将pb链接在pc的后面，pb指针后移
         tail->next = pb;
         tail = tail->next;
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
   printf("MergeLinks result: ");
   TraverseList(pc);
   return;
}

// 2.2.2 将两个非递减的有序链表合并为 一个非递增的有序链表。
// 要求结果链表仍使用原来两个链表的存储空间，不另外占用其他的存储空间。
// 表中允许有重复的数据。
int arr21[] = {1, 2, 3, 3, 4, 5, 8, 9, 9, -1};
int arr22[] = {2, 5, 6, 6, 8, 10, 12, -1};

void MergeRevLinks(pNode la, pNode lb)
{
   pNode pa = la->next;
   pNode pb = lb->next;
   pNode pc = (pNode)malloc(sizeof(Node));
   pc->next = NULL;

   while (pa || pb)
   {
      pNode temp;

      if (!pb)
      {
         temp = pa;
         pa = pa->next;
      }
      else if (!pa)
      {
         temp = pb;
         pb = pb->next;
      }
      else if (pa->data <= pb->data)
      {
         temp = pa;
         pa = pa->next;
      }
      else
      {
         temp = pb;
         pb = pb->next;
      }

      temp->next = pc->next;
      pc->next = temp;
      // free(temp);
   }
   printf("MergeRevLinks result: ");
   TraverseList(pc);
   return;
}

// 2.2.3 已知两个链表A和B分别表示两个集合，其元素递增排列。
// 请设计算法求出A与B的交集，并存放于A链表中。
int arr31[] = {1, 3, 4, 5, 6, 7, 8, 9, -1};
int arr32[] = {2, 3, 6, 7, 9, 12, 14, -1};

void Mix(pNode la, pNode lb)
{
   pNode pa = la->next;
   pNode pb = lb->next;
   pNode pc = la;
   pNode tail = pc;

   while (pa && pb)
   {
      printf("pa:%d pb:%d \n", pa->data, pb->data);
      if (pa->data == pb->data)
      {
         tail->next = pa;
         tail = tail->next;
         pa = pa->next;
         pb = pb->next;
      }
      else if (pa->data > pb->data)
      {
         pb = pb->next;
      }
      else if (pa->data < pb->data)
      {
         pa = pa->next;
      }
   }

   printf("Mix result: ");
   TraverseList(pc);
   return;
}

int main()
{
   int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 8, -1};
   // CreateLinkList(arr);

   // MergeLinks(CreateLinkList(arr11), CreateLinkList(arr12));

   // MergeRevLinks(CreateLinkList(arr21), CreateLinkList(arr22));

   Mix(CreateLinkList(arr31), CreateLinkList(arr32));

   return 0;
}
