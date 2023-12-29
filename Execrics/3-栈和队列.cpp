#include <iostream>
#include <cstring>
#include <optional>
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

// (6）假设以带头结点的循环链表表示队列，并且只设一个指针指向队尾元素站点(注意不设头指针) ，
// 试编写相应的置空队、判队空 、入队和出队等算法。

// 插入操作： 在循环链表中，如果没有头指针，插入节点可能需要特殊处理。通常，你需要找到链表中的最后一个节点，然后将其 next 指针指向新节点。
// 删除操作： 删除节点时，如果没有头指针，你可能需要遍历链表找到要删除的节点的前一个节点，并修改其 next 指针。如果队列很长，这可能会导致性能问题。
// 遍历操作： 遍历整个队列时，没有头指针可能使得代码更加复杂，因为你需要考虑循环的终止条件。
// 判空操作： 判断队列是否为空时，没有头指针可能需要特殊处理。你可能需要使用一个标记或其他方式来表示队列是否为空。

typedef int ElemType;

class Node // 构造Node节点
{
public:
    ElemType data;
    Node *next;

    Node(ElemType da = 0)
    {
        data = da;
        next = nullptr;
    }
};

using pNode = Node *;

class nodeQueue
{
private:
    Node *rear;

public:
    nodeQueue()
    {
        rear = new Node();
        rear->next = rear;
    }

    void ClearQueue()
    {
        rear->next = rear;
    }

    bool EmptyQueue()
    {
        return rear->next == rear;
    }

    void EnQueue(ElemType da)
    {
        Node *newNode = new Node(da);
        newNode->next = rear->next;
        rear->next = newNode;
        rear = rear->next;
    }

    ElemType DeQueue()
    {
        if (EmptyQueue())
        {
            cout << "empty!" << endl;
            return -1;
        }
        else
        {
            // rear->next 就是头结点
            // rear->next->next 就是队头元素节点
            Node *front = rear->next->next;
            ElemType res = front->data;
            if (front == rear) // 即队列只有一个元素
            {
                rear->next = rear;
            }
            else
            {
                rear->next->next = front->next;
            }
            delete front;
            return res;
        }
    }
};

// （7）假设以数组Q[m]存放循环队列中的元素, 同时设置一个标志tag，
// 以tag == 0和tag == 1来区别在队头指针(front)和队尾指针(rear)相等时，队列状态为“空”还是“满”。
// 试编写与此结构相应的插入(enqueue)和删除(dlqueue)算法。

const int m = 6;

class arrQueue
{
private:
    ElemType base[m];
    int front, rear, tag = 0;

public:
    arrQueue() {}
    bool isEmpty()
    {
        return (tag == 0 && front == rear);
    }

    bool isFull()
    {
        return (tag == 1 && front == rear);
    }

    void enQueue(int da)
    {
        if (isFull()) // full
        {
            cout << "arrQueue is fulled " << endl;
        }
        else
        {
            base[rear] = da;
            rear = (rear + 1) % m;
            cout << "en : " << base[rear - 1] << endl;

            if (tag == 0)
            {
                tag = 1;
            }
        }
    }

    ElemType dlQueue()
    {
        ElemType res;
        if (isEmpty())
        {
            cout << "arrQueue is empty" << endl;
        }
        else
        {
            // cout << "del : " << base[front] << endl;
            res = base[front];
            front++;

            if (front == rear)
            {
                tag = 0;
            }
        }

        return res;
    }

    void printQueue()
    {
        cout << "arrQueue content : ";
        while (!isEmpty())
        {
            cout << dlQueue() << " , ";
        }
    }
};

// (8）如果允许在循环队列的两端都可以进行插入和删除操作。要求：
// ① 写出循环队列的类型定义；
// ② 写出“从队尾删除”和“从队头插入”的算法。

class dbQueue
{
private:
    ElemType base[m];
    int front, rear = 0;

public:
    dbQueue() {}

    bool isEmpty()
    {
        return rear == front;
    }

    bool isFull()
    {
        return (rear + 1) % m == front;
    }

    void enRQueue(int da)
    {
        if (isFull())
        {
            cout << "rq is full !" << endl;
        }
        else
        {
            base[rear] = da;
            rear = (rear + 1) % m;
            cout << "enRQ : " << base[rear - 1] << endl;
        }
    }

    void enFQueue(int da)
    {
        if (isFull())
        {
            cout << "fq is full !" << endl;
        }
        else
        {
            base[--front] = da;
            cout << "enFQ : " << base[front] << endl;
        }
    }

    ElemType dlRQueue()
    {
        ElemType res;
        if (isEmpty())
        {
            cout << "dlRQ is Empty !" << endl;
        }
        else
        {
            res = base[--rear];
            // cout << "dlRQ : " << res << endl;
        }
        return res;
    }

    ElemType dlFQueue()
    {
        ElemType res;
        if (isEmpty())
        {
            cout << "dlFQ is Empty !" << endl;
        }
        else
        {
            res = base[front++];
            // cout << "dlFQ : " << res << endl;
        }
        return res;
    }
    void printQueue()
    {
        cout << "Queue content : ";
        while (!isEmpty())
        {
            cout << dlFQueue() << " , ";
        }
    }
};

// （9）已知Ackermann函数定义如下:

// ① 写出计算Ack(m,n)的递归算法，并根据此算法给出出Ack(2,1)的计算过程。
// ② 写出计算Ack(m,n)的非递归算法。

int Ack(int m, int n)
{
    if (m == 0)
        return (n + 1);
    else if (m != 0 && n == 0)
        return (Ack(m - 1, 1));
    else
        return (Ack(m - 1, Ack(m, n - 1)));
}

int Ackerman(int m, int n)
{
    int akm[m][n]; // 声明一个二维数组 akm 用于存储计算结果
    int i, j;      // 声明两个循环变量 i 和 j

    // 初始化第一行，即当 m=0 时的情况
    cout << "Ack i= 0 => ";
    for (j = 0; j < n; j++)
    {
        if (j)
        {
            cout << " - ";
        }
        akm[0][j] = j + 1;
        cout << akm[0][j];
    }
    cout << endl;

    // 通过两个嵌套的循环填充数组 akm
    for (i = 1; i < m; i++)
    {
        cout << "Ack i= " << i << " => ";
        // 处理每一行的第一个元素
        akm[i][0] = akm[i - 1][1];
        cout << akm[i][0];

        // 处理每一行的剩余元素
        for (j = 1; j < n; j++)
        {
            cout << " - ";
            akm[i][j] = akm[i - 1][akm[i][j - 1]];
            cout << akm[i][j];
        }
        cout << endl;
    }

    // 返回计算结果，即 A(m, n)
    return (akm[m][n]);
}

// （10）已知f为单链表的表头指针, 链表中存储的都是整型数据，试写出实现下列运算的递归算法：
// ① 求链表中的最大整数；
// ② 求链表的结点个数；
// ③ 求所有整数的平均值。
int findMax(pNode node)
{
    if (!node->next)
    {
        return node->data;
    }

    int max = findMax(node->next);
    return node->data > max ? node->data : max;
}

int findNodeNum(pNode node)
{
    if (!node->next)
    {
        return 1;
    }

    return findNodeNum(node->next) + 1;
}

float findNodeAva(pNode node, int len)
{
    if (!node->next)
    {
        cout << " this is final : " << node->data << endl;
        return node->data;
    }

    float res = (node->data + findNodeAva(node->next, len - 1) * (len - 1)) / len;
    cout << " now ready : " << node->data << " -> " << res << endl;
    return res;
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
    };

    []()
    {
        nodeQueue nq;
        cout << boolalpha << nq.EmptyQueue() << endl;

        nq.EnQueue(2);
        cout << boolalpha << nq.EmptyQueue() << endl;
        nq.EnQueue(3);
        nq.EnQueue(4);

        cout << "i want to " << nq.DeQueue() << endl;
        cout << "i want to " << nq.DeQueue() << endl;
        nq.EnQueue(5);
        nq.EnQueue(6);

        while (!nq.EmptyQueue())
        {
            ElemType dd = nq.DeQueue();
            cout << "NodeQueue conrtent : " << dd << endl;
        }
    };

    []()
    {
        arrQueue aq;
        aq.enQueue(2);
        aq.enQueue(3);
        aq.enQueue(4);

        int dd = aq.dlQueue();
        cout << "del : " << dd << endl;
        aq.enQueue(5);
        aq.enQueue(6);

        aq.printQueue();
    };

    []()
    {
        dbQueue dbq;
        dbq.enRQueue(1);
        dbq.enRQueue(2);
        dbq.enRQueue(3);
        cout << ">> dlFQ : " << dbq.dlFQueue() << endl;
        cout << ">> dlFQ : " << dbq.dlFQueue() << endl;
        dbq.enFQueue(5);
        dbq.enFQueue(4);
        dbq.enRQueue(7);
        dbq.enRQueue(6);
        dbq.enRQueue(8);
        cout << ">> dlRQ : " << dbq.dlRQueue() << endl;

        dbq.printQueue();
    };

    []()
    {
        // int m = 5;
        // int n = 15;

        // for (size_t i = 0; i < m; i++)
        // {
        //     cout << "Ack i=" << i << " : ";
        //     for (size_t j = 0; j < n; j++)
        //     {
        //         if (j)
        //         {
        //             cout << " - ";
        //         }
        //         cout << Ack(i, j);
        //     }
        //     cout << endl;
        // }
        // cout << Ackerman(4, 9);
    };

    []()
    {
        int arr[] = {1, 2, 13, 3, 12, 4, 9, 5, 15, 7};
        int len = sizeof(arr) / sizeof(arr[0]);

        pNode newNode = new Node(arr[0]);
        pNode tail = newNode;
        cout << "arr size : " << len << endl;

        for (size_t i = 1; i < len; i++)
        {
            tail->next = new Node(arr[i]);
            tail = tail->next;
        }
        // newNode = newNode->next;

        cout << "findMax : " << findMax(newNode) << endl;
        cout << "findNodeNum : " << findNodeNum(newNode) << endl;
        float ava = findNodeAva(newNode, len);
        cout << "findNodeAva : " << ava << endl;

        // printf all node
        cout << "newNode content : ";
        while (newNode)
        {
            cout << newNode->data;
            if (newNode->next)
            {
                cout << " -> ";
            }
            newNode = newNode->next;
        }
        cout << endl;
    }();
    return 0;
}
