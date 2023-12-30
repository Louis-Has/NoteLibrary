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
    int len = 26 + 10;
    int res[len] = {0};
    while (*str != '\0')
    {
        if ('0' <= *str && *str <= '9')
        {
            res[*str - '0']++;
        }
        else if ('A' <= *str && *str <= 'Z')
        {
            res[*str - 'A' + 10]++;
        }
        str++;
    }

    for (size_t i = 0; i < len; i++)
    {
        if (!res[i])
            continue;
        if (i < 10)
        {
            cout << "int " << i << " : " << res[i] << endl;
        }
        else
        {
            cout << "char " << static_cast<char>(i + 'A' - 10) << " : " << res[i] << endl;
        }
    }
}

int main()
{
    const char str[][24] = {"DJH&*@", "342DFWF5444RRE"};
    ASCCount(str[1]);
    return 0;
}
