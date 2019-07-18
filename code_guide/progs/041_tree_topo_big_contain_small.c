#include "ds.h"

int check(treenode *big, treenode *small)
{
    if (!small)
        return 1;

    if (!big || big->val != small->val)
        return 0;

    return check(big->left, small->left) && check(big->right, small->right);
}

int contain(treenode *big, treenode *small)
{
    if (!big)
        return 0;
    return check(big, small) || contain(big->left, small) || contain(big->right, small);
}

int main(int argc, char *argv[])
{
#define N(x) treenode_create(x)
    treenode *root = N(1);
    root->left = N(2);
    root->right = N(3);
    root->left->left = N(4);
    root->left->right = N(5);
    root->right->left = N(6);
    root->right->right= N(7);
    tree_draw(root);

    {
        treenode *small = N(1);
        tree_draw(small);
        printf("is contain : %d\n", contain(root, small));
    }

    {
        treenode *small = N(2);
        tree_draw(small);
        printf("is contain : %d\n", contain(root, small));
    }
    {
        treenode *small = N(3);
        tree_draw(small);
        printf("is contain : %d\n", contain(root, small));
    }
    {
        treenode *small = N(4);
        tree_draw(small);
        printf("is contain : %d\n", contain(root, small));
    }
    {
        treenode *small = N(5);
        tree_draw(small);
        printf("is contain : %d\n", contain(root, small));
    }
    {
        treenode *small = N(9);
        tree_draw(small);
        printf("is contain : %d\n", contain(root, small));
    }
    {
        treenode *small = N(0);
        tree_draw(small);
        printf("is contain : %d\n", contain(root, small));
    }

    {
        treenode *small = N(2);
        small->left = N(4);
        small->right = N(5);
        tree_draw(small);
        printf("is contain : %d\n", contain(root, small));
    }

    {
        treenode *small = N(1);
        small->left = N(3);
        small->right= N(2);
        tree_draw(small);
        printf("is contain : %d\n", contain(root, small));
    }

    {
        treenode *small = N(1);
        small->left = N(2);
        small->right= N(3);
        tree_draw(small);
        printf("is contain : %d\n", contain(root, small));
    }
    {
        treenode *small = N(5);
        small->left = N(4);
        small->right= N(2);
        tree_draw(small);
        printf("is contain : %d\n", contain(root, small));
    }
    {
        treenode *small = N(1);
        small->left = N(2);
        small->right = N(3);
        small->left->left = N(4);
        small->left->right = N(5);
        small->right->left = N(6);
        small->right->right= N(7);
        tree_draw(small);
        printf("is contain : %d\n", contain(root, small));
    }
}
