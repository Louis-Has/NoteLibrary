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
        if (*str >= '0' && *str <= '9')
        {
            res[*str - '0']++;
        }
        else if (*str >= 'A' && *str <= 'Z')
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

// （2）写一个递归算法来实现字符串逆序存储，要求不另设串存储空间。
string InvertStore(string str)
{
    if (str.empty())
        return "";

    return InvertStore(str.substr(1)) + str[0];
}

// （3）编写算法，实现下面函数的功能。
// 函数void insert(char*s,char*t,int pos)将字符串t插入到字符串s中，插入位置为pos。
// 假设分配给字符串s的空间足够让字符串t插入。（说明：不得使用任何库函数）

void insert(char *s, char *t, int pos)
{
    cout << "s : " << s << endl;
    cout << "t : " << t << endl;
    cout << "pos : " << pos << endl;

    int s_len = strlen(s);
    int t_len = strlen(t);

    if (pos < 0 || pos > s_len)
    {
        cout << "Invalid position." << endl;
        return;
    }

    for (size_t i = s_len - 1; i >= pos; i--)
    {
        s[i + t_len] = s[i];
    }

    for (size_t i = 0; i < t_len; i++)
    {
        s[i + pos] = t[i];
    }

    cout << "Result : " << s << endl;
}

int main()
{
    []()
    {
        const char str[][24] = {"DJH&*@", "342DF WF54^%$44RR"};
        ASCCount(str[1]);
    };

    []()
    {
        string str[] = {"asd456ghjk123"};
        cout << "InvertStore : " << InvertStore(str[0]);
    };

    []()
    {
        char st[24] = "abcdefgh";
        char tt[] = "QWERT";
        insert(st, tt, 2);
    }();

    return 0;
}
