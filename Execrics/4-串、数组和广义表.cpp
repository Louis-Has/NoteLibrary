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
    const int len = 26 + 10;
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

    int s_len = 0;
    while (s[s_len] != '\0')
    {
        ++s_len;
    }

    int t_len = 0;
    while (t[t_len] != '\0')
    {
        ++t_len;
    }

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

// （4）已知字符串S1中存放一段英文，
// 写出算法format(s1,s2,s3,n),将其按给定的长度n格式化成两端对齐的字符串S2, 其多余的字符送S3。

void Format(char *s1, char *s2, char *s3, int n)
{
    int len = strlen(s1);
    int j = 0;
    int h = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (s1[i] != ' ')
        {
            if (j < n)
            {
                s2[j++] = s1[i];
            }
            else
            {
                s3[h++] = s1[i];
            }
        }
    }
}

// （5）设二维数组a[1..m, 1..n] 含有m*n 个整数。
// ① 写一个算法判断a中所有元素是否互不相同?输出相关信息(yes/no)；
// ② 试分析算法的时间复杂度。

// (6)设任意n个整数存放于数组A(1:n)中，
// 试编写算法，将所有正数排在所有负数前面（要求算法复杂度为0(n)）。

void Arrange(int arr[], int len)
{
    int n = 0;
    int m = len - 1;

    while (n < m)
    {
        while (arr[n] > 0)
        {
            n++;
        }

        while (arr[m] < 0)
        {
            m--;
        }

        if (n < m)
        {
            int temp = arr[n];
            arr[n] = arr[m];
            arr[m] = temp;
        }
    }

    // print content
    cout << "Arange result : ";
    for (size_t i = 0; i < len; i++)
    {
        if (i)
            cout << " -> ";
        cout << arr[i];
    }
    cout << endl;
}

int main()
{
    // []()
    // {
    //     const char str[][24] = {"DJH&*@", "342DF WF54^%$44RR"};
    //     ASCCount(str[1]);
    // }();

    // []()
    // {
        // string str[] = {"asd456ghjk123"};
        // cout << "InvertStore : " << InvertStore(str[0]);
    // };

    // []()
    // {
    //     char st[24] = "abcdefgh";
    //     char tt[] = "QWERT";
    //     insert(st, tt, 2);
    // };

    // []()
    // {
    //     char s1[24] = "ab c2 d 23e f233 ";
    //     char s2[24] = "";
    //     char s3[24] = "";
    //     int nLen = 4;
    //     Format(s1, s2, s3, nLen);
    //     printf("Format result :\n s1 %s \n s2 %s \n s3 %s \n nLen %d \n", s1, s2, s3, nLen);
    // };

    // []()
    // {
        int arr[] = {-2, 3, 55, -12, 1, 23, -8, -6, 10};
        Arrange(arr, sizeof(arr) / sizeof(arr[0]));
    // };

    return 0;
}
