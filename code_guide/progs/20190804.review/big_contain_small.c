#include "ds.h"

int contain(treenode *big, treenode *small)
{
    if (!small)
        return 1;

    if (!big)
        return 0;

    if (big->val != small->val)
        return 0;

    return contain(big->left, small->left) && contain(big->right, small->right);
}

int big_contain_small(treenode* big, treenode *small)
{
    if (!big || !small)
        return 0;

    int result = 0; 
    if (big->val == small->val)
        result = contain(big, small);

    return result || big_contain_small(big->left, small) || big_contain_small(big->right, small);
}

int main(int argc, char *argv[])
{
#define N(x) treenode_create(x)
    treenode *big = N(1);
    big->left = N(2);
    big->right = N(3);
    big->left->left = N(4);
    big->left->right = N(5);
    big->right->left = N(6);
    big->right->right = N(7);
    tree_draw(big);

    {
        treenode *small = N(2);
        small->right = N(5);
        tree_draw(small);
        printf("is contain %d\n", big_contain_small(big, small));
    }
    {
        treenode *small = N(1);
        small->left = N(2);
        small->right = N(3);
        small->right->right = N(7);
        tree_draw(small);
        printf("is contain %d\n", big_contain_small(big, small));
    }
}
