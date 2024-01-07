#include <iostream>
#include <cstring>
#include <optional>
#include <stack>

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

public:
    Tree() : root(nullptr) {}

    void insert(SElemType da)
    {
        root = Insert(root, da);
    }
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

// （1）统计二叉树的叶结点个数。
// [题目分析]如果二叉树为空，
// 返回0，如果二叉树不为空且左右子树为空，返回1，
// 如果二叉树不为空，且左右子树不同时为空，返回左子树中叶子节点个数加上右子树中叶子节点个数。

int LeafNodeCount(Tree T)
{
}

int main()
{
    // 1
    Tree Tr ;



    return 0;
}
