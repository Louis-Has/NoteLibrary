#include <iostream>
#include <cstring>
#include <stack>

using namespace std;

// （1）将编号为0和1的两个栈存放于一个数组空间V[m]中，栈底分别处于数组的两端。
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

// （2）回文是指正读反读均相同的字符序列，
// 如“abba”和“abdba”均是回文，但“good”不是回文。
// 试写一个算法判定给定的字符向量是否为回文。(提示：将一半字符入栈)

bool isPalindrome(const char *str)
{
    stack<char> charStack;
    int len = strlen(str);
    cout << str << " length: " << len << " , isPalindrome: ";

    for (size_t i = 0; i < len / 2; i++)
    {
        charStack.push(str[i]);
    }

    int start = (len % 2 == 0) ? (len / 2) : (len / 2 + 1);

    for (size_t i = start; i < len; i++)
    {
        if (charStack.top() != str[i])
        {
            return false;
        }
        charStack.pop();
    }
    return true;
}

// （3）设从键盘输入一整数的序列：a1, a2, a3，…，an，
//  试编写算法实现：用栈结构存储输入的整数，当ai≠-1时，将ai进栈；
//  当ai=-1时，输出栈顶整数并出栈。
//  算法应对异常情况（入栈满等）给出相应的信息。

#define maxsize 栈空间容量

void Inouts()
{
    int m = 4;
    int stack[m];
    int top = 0;
    int n = m * 2;

    for (size_t i = 0; i < n; i++)
    {
        int da;
        cin >> da;

        if (cin.fail())
        {
            // 输入不是整数，处理异常情况
            cerr << "Invalid input. Please enter integers only.\n";
            break;
        }

        //  handle the input data
        if (da == -1)
        {
            if (top == 0)
            {
                cout << "Stack is Empty!" << endl;
            }
            else
            {
                top--;
                cout << "Stack pop: " << stack[top] << endl;
            }
        }
        else
        {
            if (top == m)
            {
                cout << "Stack is Full!" << endl;
            }
            else
            {
                stack[top++] = da;
                cout << "Stack push: " << stack[top - 1] << endl;
            }
        }
    }

    cout << "Now Stack contents: ";
    while (top != 0)
    {
        cout << stack[--top] << "->";
    }
    cout << endl;
}

// （4）从键盘上输入一个后缀表达式，试编写算法计算表达式的值。
// 规定：逆波兰表达式的长度不超过一行，以$符作为输入结束，
// 操作数之间用空格分隔,操作符只可能有+、-、*、/四种运算。
// 例如：234 34+2*$。

void expr()
{
    stack<int> OPTR;
    string da;
    // cin >> da;
    getline(cin, da);
    int sum = 0;

    cout << "string : " << da << endl;

    for (size_t i = 0; i < da.length(); i++)
    {
        cout << da[i] << " ";
        if (isdigit(da[i]))
        {
            sum = sum * 10 + (da[i] - '0');
            cout << "sum is : " << sum << endl;
        }
        else if (da[i] == '$')
        {
            cout << "break!" << endl;
            break;
        }
        else
        {
            OPTR.push(sum);
            sum = 0;
            if (da[i] == ' ') // 空格之间是数字间隔
            {
                cout << "space!";
            }
            else if (da[i] == '*')
            {
                int temp = OPTR.top();
                OPTR.pop();
                int temp2 = OPTR.top();
                OPTR.pop();
                OPTR.push(temp2 / temp);
                cout << "mul : " << OPTR.top();
            }
            else if (da[i] == '/')
            {
                int temp = OPTR.top();
                OPTR.pop();
                int temp2 = OPTR.top();
                OPTR.pop();
                OPTR.push(temp2 / temp);
                cout << "div : " << OPTR.top();
            }
            else if (da[i] == '+')
            {
                int temp = OPTR.top();
                OPTR.pop();
                int temp2 = OPTR.top();
                OPTR.pop();
                OPTR.push(temp2 / temp);
                cout << "add : " << OPTR.top();
            }
            else if (da[i] == '-')
            {
                int temp = OPTR.top();
                OPTR.pop();
                int temp2 = OPTR.top();
                OPTR.pop();
                OPTR.push(temp2 / temp);
                cout << "sub : " << OPTR.top();
            }

            cout << endl;
        }
    }

    cout << "result : " << OPTR.top() << endl;
}

// （5）假设以I和O分别表示入栈和出栈操作。
// 栈的初态和终态均为空，入栈和出栈的操作序列可表示为仅由I和O组成的序列，
// 称可以操作的序列为合法序列，否则称为非法序列。
// ①下面所示的序列中哪些是合法的？
//    A. IOIIOIOO     B. IOOIOIIO      C. IIIOIOIO     D. IIIOOIOO
// ②通过对①的分析，写出一个算法，判定所给的操作序列是否合法。
// 若合法，返回true，否则返回false（假定被判定的操作序列已存入一维数组中）。

// ①A和D是合法序列，B和C 是非法序列。

bool judge(string st)
{
    cout << st << endl;

    stack<int> sta;

    for (size_t i = 0; i < st.length(); i++)
    {
        if (st[i] == 'I')
        {
            cout << "ready to push" << endl;
            sta.push(1);
        }
        else if (st[i] == 'O')
        {
            cout << "ready to pop" << endl;
            if (sta.empty())
            {
                cout << "stack is empty!" << endl;
                return false;
            }
            else
            {
                sta.pop();
            }
        }
    }

    // 检查 stack 是否清空
    if (!sta.empty())
    {
        cout << "stack not yet empty!" << endl;
        return false;
    }
    else
    {

        // finally
        return true;
    }
}

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
    };

    []()
    {
        cout << boolalpha << isPalindrome("abcdcba") << endl;
        cout << boolalpha << isPalindrome("abcdba") << endl;
        cout << boolalpha << isPalindrome("abcddcba") << endl;
    };

    // Inouts();

    // expr();

    []()
    {
        string dd[] = {"IOIIOIOO", "IOOIOIIO", "IIIOIOIO", "IIIOOIOO"};
        bool res = judge(dd[3]);
        cout << boolalpha << "Judge result: " << res;
    }();

    return 0;
}
