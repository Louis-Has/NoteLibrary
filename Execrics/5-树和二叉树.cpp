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
    TreeNode *root;
    TreeNode *Insert(TreeNode *current, SElemType da);
    void InorderTraversal(TreeNode *current);

public:
    Tree() : root(nullptr)
    {
    }

    void insert(SElemType da)
    {
        root = Insert(root, da);
    }

    void printTree()
    {
        InorderTraversal(root);
        cout << endl;
    };
};

TreeNode *Tree::Insert(TreeNode *current, SElemType da)
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
}

void Tree::InorderTraversal(TreeNode *current)
{
    if (current != nullptr)
    {
        cout << current->data << " -> ";
        InorderTraversal(current->left);
        InorderTraversal(current->right);
    }
}
// （1）统计二叉树的叶结点个数。
// [题目分析]如果二叉树为空，
// 返回0，如果二叉树不为空且左右子树为空，返回1，
// 如果二叉树不为空，且左右子树不同时为空，返回左子树中叶子节点个数加上右子树中叶子节点个数。

// int LeafNodeCount(Tree T)
// {
// }

int main()
{
    // （1）统计二叉树的叶结点个数。
    Tree Tr;
    Tr.insert(0);
    Tr.insert(2);
    Tr.insert(5);
    Tr.insert(3);
    Tr.insert(1);
    Tr.printTree();

    return 0;
}
