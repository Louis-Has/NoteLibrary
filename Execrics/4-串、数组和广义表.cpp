#include <iostream>
#include <cstring>
#include <optional>
#include <stack>

using namespace std;

// 定义栈中元素的类型
typedef int SElemType;

// （1）写一个算法统计在输入字符串中各个不同字符出现的频度并将结果存入文件
// （字符串中的合法字符为A-Z这26个字母和0-9这10个数字）。
void ASCCount(const char str[])
{
    while (*str != '\0')
    {
        cout << *str++ << endl;
    }
}

int main()
{
    const char str[][8] = {"sdrwr2", "342dfwf"};
    ASCCount(str[1]);
    return 0;
}
