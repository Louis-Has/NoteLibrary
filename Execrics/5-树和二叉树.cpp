#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

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

// （3）交换二叉树每个结点的左孩子和右孩子。
// [题目分析]如果某结点左右子树为空，返回，否则交换该结点左右孩子，然后递归交换左右子树。
void changeLR(TreeNode *root)
{
    if (root->left == nullptr && root->right == nullptr)
    {
        cout << "null" << endl;
        return;
    }

    TreeNode *temp;
    temp = root->right;
    root->right = root->left;
    root->left = temp;

    if (root->left != nullptr)
    {
        changeLR(root->left);
    }

    if (root->right != nullptr)
    {
        changeLR(root->right);
    }
}

// （4）设计二叉树的双序遍历算法
// （双序遍历是指对于二叉树的每一个结点来说，先访问这个结点，
// 再按双序遍历它的左子树，然后再一次访问这个结点，接下来按双序遍历它的右子树）。
// [题目分析]若树为空，返回；若某结点为叶子结点，则仅输出该结点；
// 否则先输出该结点，递归遍历其左子树，再输出该结点，递归遍历其右子树。

void doubleTraversal(TreeNode *root)
{
    if (root == nullptr)
    {
        cout << "point null !" << endl;
    }
    else if (root->left == nullptr && root->right == nullptr)
    {
        cout << root->data << endl;
    }
    else
    {
        cout << root->data << endl;
        doubleTraversal(root->left);
        cout << root->data << endl;
        doubleTraversal(root->right);
    }
}

// （5）计算二叉树最大的宽度（二叉树的最大宽度是指二叉树所有层中结点个数的最大值）。
// [题目分析] 求最大宽度可采用层次遍历的方法，记下各层结点数，每层遍历完毕，
// 若结点数大于原先最大宽度，则修改最大宽度。

int maxWidth(TreeNode *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    queue<TreeNode *> qu;
    qu.push(root);
    int maxWidth = 0;

    while (!qu.empty())
    {
        // int cindd;
        // cin >> cindd;

        int nodeSize = qu.size();
        maxWidth = max(maxWidth, nodeSize);

        cout << "nodeSize : " << nodeSize << endl;

        for (size_t i = 0; i < nodeSize; i++)
        {
            TreeNode *temp = qu.front();
            cout << "data : " << temp->data << endl;
            qu.pop();

            if (temp->left)
            {
                cout << "add left : " << temp->left->data << endl;
                qu.push(temp->left);
            }
            if (temp->right)
            {
                cout << "add right : " << temp->right->data << endl;
                qu.push(temp->right);
            }
        }
        cout << endl;
    }

    return maxWidth;
};

// （6）用按层次顺序遍历二叉树的方法，统计树中具有度为1的结点数目。
// [题目分析]
// 若某个结点左子树空右子树非空或者右子树空左子树非空，则该结点为度为1的结点
int countLevel1(TreeNode *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    queue<TreeNode *> qu;
    qu.push(root);
    int countNum = 0;

    while (!qu.empty())
    {
        // char cinchar;
        // cin >> cinchar;

        int nodeSize = qu.size();

        for (size_t i = 0; i < nodeSize; i++)
        {
            TreeNode *temp = qu.front();
            qu.pop();

            // cout << "nodeSize : " << nodeSize << "; date : " << temp->data << countNum << endl;

            if ((temp->left && !temp->right) || (!temp->left && temp->right))
            {
                // cout << " add 1 ~" << endl;
                countNum++;
            }

            if (temp->left)
            {
                qu.push(temp->left);
            }

            if (temp->right)
            {
                qu.push(temp->right);
            }
        }
    }

    return countNum;
};

int main()
{
    Tree Tr;
    // Tr.printTree();
    Tr.insert(8);
    Tr.insert(2);
    Tr.insert(5);
    Tr.insert(3);
    Tr.insert(1);
    Tr.insert(4);
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

    // // （3）交换二叉树每个结点的左孩子和右孩子。
    // changeLR(Tr.root);
    // Tr.printTree();

    // （4）设计二叉树的双序遍历算法
    // doubleTraversal(Tr.root);

    // （5）计算二叉树最大的宽度
    // cout << "maxWidth : " << maxWidth(Tr.root) << endl;

    // （6）用按层次顺序遍历二叉树的方法，统计树中具有度为1的结点数目。
    // cout << "countLevel1 : " << countLevel1(Tr.root) << endl;

    return 0;
}
