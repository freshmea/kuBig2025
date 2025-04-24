#include <iostream>
#include <memory>
#include <vector>
using namespace std;

struct TreeNode
{
    int value;
    vector<shared_ptr<TreeNode>> chilren;
    TreeNode(int val) : value(val) {}
};

void printTree(const shared_ptr<TreeNode> &node, int depth = 0)
{
    if (!node)
        return;
    cout << string(depth * 2, ' ') << node->value << endl;
    for (const auto &child : node->chilren)
    {
        printTree(child, depth + 1);
    }
}

int main()
{
    auto root = make_shared<TreeNode>(1);
    root->chilren.push_back(make_shared<TreeNode>(2));
    root->chilren.push_back(make_shared<TreeNode>(3));
    root->chilren.push_back(make_shared<TreeNode>(4));
    root->chilren[0]->chilren.push_back(make_shared<TreeNode>(5));
    printTree(root);
    return 0;
}