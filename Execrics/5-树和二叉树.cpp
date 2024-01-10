#include <iostream>
#include <cstring>
#include <optional>
#include <stack>
#include <vector>

using namespace std;

// 定义栈中元素的类型
typedef int SElemType;

class TreeNode
{
public:
    SElemType data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(SElemType da) : data(da), left(nullptr), right(nullptr) {}
};

class Tree
{
private:
    TreeNode *Insert(TreeNode *current, SElemType da)
    {
        if (current == nullptr)
        {
            return new TreeNode(da);
        }

        if (da < current->data)
        {
            current->left = Insert(current->left, da);
        }
        else if (da > current->data)
        {
            current->right = Insert(current->right, da);
        }

        return current;
    };

    void InorderTraversal(TreeNode *current)
    {
        if (current != nullptr)
        {
            cout << current->data << " -> ";
            InorderTraversal(current->left);
            InorderTraversal(current->right);
        }
    };

public:
    TreeNode *root;
    Tree() : root(nullptr) {}

    void insert(SElemType da)
    {
        root = Insert(root, da);
    }

    void printTree()
    {
        if (root == nullptr)
        {
            cout << "tree is null" << endl;
        }
        else
        {
            InorderTraversal(root);
            cout << endl;
        }
    };

    //     void printTreeMap()
    //     {
    //         int rows = 3;
    //         int cols = 5;

    //         // new arrDate
    //         vector<vector<char>> arrDate(rows, vector<char>(cols, '_'));

    //         // show all date
    //         for (size_t i = 0; i < rows; i++)
    //         {
    //             for (size_t j = 0; j < cols; j++)
    //             {
    //                 cout << arrDate[i][j] << " - ";
    //             }
    //             cout << endl;
    //         }
    //     };
};

// （1）统计二叉树的叶结点个数。
// [题目分析]如果二叉树为空，
// 返回0，如果二叉树不为空且左右子树为空，返回1，
// 如果二叉树不为空，且左右子树不同时为空，返回左子树中叶子节点个数加上右子树中叶子节点个数。

int LeafNodeCount(TreeNode *T)
{
    if (T == nullptr)
    {
        return 0;
    }
    else if (T->left == nullptr && T->right == nullptr)
    {
        return 1;
    }

    int res = LeafNodeCount(T->left) + LeafNodeCount(T->right);
    return res;
}

// （2）判别两棵树是否相等。

bool compareTree(TreeNode *root1, TreeNode *root2)
{
    if (root1 == nullptr || root2 == nullptr)
    {
        if (root1 == nullptr && root2 == nullptr)
        {
            return true;
        }
        return false;
    }

    if (root1->data != root2->data)
    {
        return false;
    }
    else
    {
        return compareTree(root1->left, root2->left) && compareTree(root1->right, root2->right);
    }
}

int main()
{
    Tree Tr;
    // Tr.printTree();
    Tr.insert(8);
    Tr.insert(2);
    Tr.insert(5);
    Tr.insert(3);
    Tr.insert(1);
    Tr.printTree();

    // （1）统计二叉树的叶结点个数。
    // cout << LeafNodeCount(Tr.root) << endl;

    // Tree Ts;
    // Ts.insert(8);
    // Ts.insert(2);
    // Ts.insert(5);
    // Ts.insert(3);
    // Ts.insert(11);
    // Ts.printTree();
    // // （2）判别两棵树是否相等。
    // cout << boolalpha << compareTree(Tr.root, Ts.root) << endl;

    return 0;
}
