#include "ds.h"

int tree_is_equal(treenode *n1, treenode *n2)
{
    if (!n1 && !n2)
        return 1;

    if (!!n1 ^ !!n2)
        return 0;

    if (n1->val != n2->val)
        return 0;

    return tree_is_equal(n1->left, n2->left) && tree_is_equal(n1->right, n2->right);
}

int tree_big_contain_small(treenode *big, treenode *small)
{
    if (!big || !small)
        return 0;

    int equal = 0;
    if (big->val == small->val) 
        equal = tree_is_equal(big, small);

    if (equal)
        return 1;

   return tree_big_contain_small(big->left, small) || tree_big_contain_small(big->right, small);
}

int main(int argc, char *argv[])
{
#define N(x) treenode_create(x)
    treenode *big = N(1);
    big->left = N(2);
    big->left->left = N(4);
    big->left->left->right = N(8);
    big->left->right = N(5);
    big->left->right->left = N(9);
    big->right = N(3);
    big->right->left = N(6);
    big->right->right = N(7);
    tree_draw(big);

    {
        treenode *small = N(2);
        small->left = N(4);
        small->left->right = N(8);
        small->right = N(5);
        small->right->left = N(9);
        tree_draw(small);
        printf("contain : %d\n", tree_big_contain_small(big, small));
    }
    {
        treenode *small = N(2);
        small->left = N(4);
        small->left->right = N(8);
        small->right = N(5);
        tree_draw(small);
        printf("contain : %d\n", tree_big_contain_small(big, small));
    }
}
