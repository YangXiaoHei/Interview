#include "ds.h"

int left_height(treenode *root, int level)
{
    while (root) {
        level++;
        root = root->left;
    }
    return level;
}

int count_cbt_node_core(treenode *root, int level, int height)
{
    if (level == height)
        return 1;

    if (left_height(root->right, level) == height)
        return (1 << (height - level)) + count_cbt_node_core(root->right, level + 1, height);
    else
        return (1 << (height - level - 1)) + count_cbt_node_core(root->left, level + 1, height);
}

int count_cbt_node(treenode *root)
{
    if (!root)
        return 0;
    int height = tree_height(root);
    return count_cbt_node_core(root, 1, height);
}

int main(int argc, char *argv[])
{
#define N(x) treenode_create(x)
    treenode *root = N(1);
    root->left = N(2);
    root->left->left = N(3);
    root->left->right = N(4);
    root->right = N(5);
    root->right->left = N(6);
    root->right->right = N(7);
    root->left->left->left = N(8);
    tree_draw(root);
    printf("%d\n", count_cbt_node(root));
}
