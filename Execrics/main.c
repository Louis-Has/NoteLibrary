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

// 2.2.4 已知两个链表A和B分别表示两个集合，其元素递增排列。
// 请设计算法求出两个集合A和B 的差集（即仅由在A中出现而不在B中出现的元素所构成的集合），
// 并以同样的形式存储，同时返回该集合的元素个数。
int arr41[] = {1, 2, 4, 6, 7, 10, 12, 14, 15, -1};
int arr42[] = {2, 3, 4, 7, 8, 9, 10, 11, -1};

void Difference(pNode la, pNode lb)
{
   pNode pa = la->next;
   pNode pb = lb->next;
   pNode pc = la;
   pNode tail = pc;

   while (pa && pb)
   {
      if (pa->data < pb->data)
      {
         tail->next = pa;
         tail = tail->next;
         pa = pa->next;
      }
      else if (pa->data > pb->data)
      {
         pb = pb->next;
      }
      else
      {
         pa = pa->next;
         pb = pb->next;
      }
      tail->next = NULL;
   }

   if (!pb)
   {
      tail->next = pa;
   }

   printf("Difference result: ");
   TraverseList(pc);
   return;
}

// 2.2.5 设计算法将一个带头结点的单链表A分解为两个具有相同结构的链表B、C，
// 其中B表的结点为A表中值小于零的结点，
// 而C表的结点为A表中值大于零的结点（链表A中的元素为非零整数，要求B、C表利用A表的结点）。
int arr51[] = {1, 2, -2, -5, 4, 3, -12, 13, 8, -1};

void Discompose(pNode la)
{
   pNode pa = la->next;
   pNode pb = (pNode)malloc(sizeof(Node));
   pNode tailb = pb;
   pNode pc = (pNode)malloc(sizeof(Node));
   pNode tailc = pc;

   while (pa)
   {
      if (pa->data > 0)
      {
         tailb->next = pa;
         tailb = tailb->next;
         pa = pa->next;
         tailb->next = NULL;
      }
      else
      {
         tailc->next = pa;
         tailc = tailc->next;
         pa = pa->next;
         tailc->next = NULL;
      }
   }

   printf("Discompose result: ");
   TraverseList(pb);
   TraverseList(pc);
   return;
}

// 2.2.6 设计一个算法，通过一趟遍历在单链表中确定值最大的结点。
int arr61[] = {2, 4, 12, 48, 2, 3, 8, 13, -1};

void FindMax(pNode la)
{
   pNode pa = la->next;
   if (!pa)
   {
      printf("result: 0");
   }
   int max = pa->data;
   while (pa)
   {
      max = pa->data > max ? pa->data : max;
      pa = pa->next;
   }

   printf("FindMax result: %d", max);
}

int main()
{
   int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 8, -1};
   // CreateLinkList(arr);

   // MergeLinks(CreateLinkList(arr11), CreateLinkList(arr12));

   // MergeRevLinks(CreateLinkList(arr21), CreateLinkList(arr22));

   // Mix(CreateLinkList(arr31), CreateLinkList(arr32));

   // Difference(CreateLinkList(arr41), CreateLinkList(arr42));

   // Discompose(CreateLinkList(arr51));

   FindMax(CreateLinkList(arr61));

   return 0;
}
