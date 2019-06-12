#include <stdio.h>
#include <stdlib.h>

typedef struct bstnode {
    int val;
    struct bstnode *left;
    struct bstnode *right;
} bstnode;

bstnode *bstnode_create(int val)
{
    bstnode *n = malloc(sizeof(bstnode));
    if (!n) exit(1);
    n->left = n->right = NULL;
    n->val = val;
    return n;
}

void bst_in_traverse(bstnode *root)
{
    if (!root) return;

    bst_in_traverse(root->left);
    printf("%-3d", root->val);
    bst_in_traverse(root->right);
}

void bst_print(bstnode *root)
{
    bst_in_traverse(root);
    printf("\n");
}

int is_contain(bstnode *big, bstnode *small)
{
    if (!small) return 1;
    if (!big) return 0;
    if (big->val != small->val)
        return 0;
    return is_contain(big->left, small->left) && is_contain(big->right, small->right);
}

int bigtree_contain_smalltree(bstnode *big, bstnode *small)
{
    if (!big || !small)
        return 0;

    int result = 0;
    if (big->val == small->val) 
        result = is_contain(big, small);

    return result || bigtree_contain_smalltree(big->left, small)
                  || bigtree_contain_smalltree(big->right, small);
}

int main(int argc, char *argv[])
{
    bstnode *big = bstnode_create(8);
    big->left = bstnode_create(8);
    big->right = bstnode_create(7);
    big->left->left = bstnode_create(9);
    big->left->right = bstnode_create(2);
    big->left->right->left = bstnode_create(4);
    big->left->right->right = bstnode_create(7);
    bst_print(big);

    bstnode *small = bstnode_create(8);
    small->left = bstnode_create(9);
    small->right = bstnode_create(2);
    small->right->left = bstnode_create(4);
    small->right->right = bstnode_create(7);
    bst_print(small);

    printf("%d\n", bigtree_contain_smalltree(big, small));
}
