#include <iostream>

using namespace std;

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
    DblStack(int maxSize) : m(maxSize)
    {
        V = new SElemType(maxSize);
        top[0] = top[1] = -1;
        bot[0] = bot[1] = 0;
    }

    bool IsEmpty(int i) const
    {
        return i ? top[1] == m : top[0] == -1;
    }
};

// 初始化
// 栈空
// 栈满
// 进栈
// 出栈

int main()
{
    DblStack DS(10);
    cout << boolalpha << DS.IsEmpty(1);
    return 0;
}
