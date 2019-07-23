#include "ds.h"

int left_height(treenode *root, int level)
{
    while (root) {
        level++;
        root = root->left;
    }
    return level - 1;
}

int count_cbtnode_core(treenode *root, int level, int height)
{
    if (level == height)
        return 1;
    
    if (left_height(root->right, level + 1) == height)
       return (1 << (height - level)) + count_cbtnode_core(root->right, level + 1, height); 
    else
       return (1 << (height - level - 1)) + count_cbtnode_core(root->left, level + 1, height);
}

int count_cbtnode(treenode *root)
{
    int h = left_height(root, 1);
    return  count_cbtnode_core(root, 1, h); 
}

int main(int argc, char *argv[])
{
#define N(x) treenode_create(x)
    treenode *root = N(1);
    root->left = N(2);
    root->right = N(3);
    root->left->left = N(4);
    root->left->right = N(5);
    tree_draw(root);
    printf("cbtnode count %d\n", count_cbtnode(root));
}
