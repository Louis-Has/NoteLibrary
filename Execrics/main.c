#include <stdio.h>

void pr(unsigned int num)
{
   if (num > 9)
   {
      pr(num / 10);
   }
   printf("%d -> ", num % 10);
}

int main()
{
   unsigned int num = 1234005;
   printf("ready to start\n");

   pr(num);

   return 0;
}
