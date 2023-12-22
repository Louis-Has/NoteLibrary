#include <iostream>

using namespace std;

// 将编号为0和1的两个栈存放于一个数组空间V[m]中，栈底分别处于数组的两端。
// 当第0号栈的栈顶指针top[0]等于-1时该栈为空，当第1号栈的栈顶指针top[1]等于m时该栈为空。
// 两个栈均从两端向中间增长。试编写双栈初始化，判断栈空、栈满、进栈和出栈等算法的函数。

// 定义栈中元素的类型
typedef int SElemType;

// 定义双栈数据结构
class DblStack
{
private:
    int top[2], bot[2]; // 栈顶和栈底指针
    SElemType *V;       // 栈数组
    int m;              // 栈最大可容纳元素个数
public:
    // 初始化
    DblStack(int maxSize) : m(maxSize)
    {
        V = new SElemType[maxSize];

        top[0] = -1; // 第0号栈初始化为空
        bot[0] = 0;  // 第0号栈初始化栈底

        top[1] = maxSize;     // 第1号栈初始化为空
        bot[1] = maxSize - 1; // 第1号栈初始化栈底
    }
    // 栈空
    bool IsEmpty(int i) const
    {
        return i ? top[1] == m : top[0] == -1;
    }
    // 栈满
    bool IsFull(int i) const
    {
        return i ? top[1] == m / 2 : top[0] == m / 2 - 1;
    }

    void PrintAll()
    {
        cout << "V: ";
        for (int i = 0; i < m; i++)
        {
            if (i)
            {
                cout << " , ";
            }
            cout << V[i];
        }
        cout << endl;
    }
    // 进栈
    void Push(int i, SElemType data)
    {
        if (IsFull(i))
        {
            printf("Stack %d is full. Cannot push element %d.\n", i, data);
        }
        if (i)
        {
            V[--top[1]] = data;
        }
        else
        {
            V[++top[0]] = data;
        }
    }
    // 出栈
    SElemType Pop(int i)
    {
        if (IsEmpty(i))
        {
            printf("Stack %d is empty. Cannot pop.\n", i);
        }
        if (i)
        {
            return V[top[1]++];
        }
        else
        {
            return V[top[0]--];
        }
    }
};

int main()
{
    []()
    {
        DblStack DS(10);

        DS.Push(0, 5);
        DS.Push(0, 6);
        DS.Push(0, 7);
        DS.Push(1, 4);
        DS.Push(1, 222);
        cout << boolalpha << DS.IsEmpty(0) << endl;
        DS.PrintAll();
        cout << DS.Pop(0) << endl;
        DS.Push(0, 12);
        DS.PrintAll();
    }();

    return 0;
}
