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

int is_contain(bstnode *root1, bstnode *root2)
{
    if (!root2) return 1;
    if (!root1) return 0;
    if (root1->val != root2->val)
        return 0;
    return is_contain(root1->left, root2->left) && is_contain(root1->right, root2->right);
}

int bigtree_contain_smalltree(bstnode *root1, bstnode *root2)
{
    if (!root1 || !root2)
        return 0;

    int result = 0;
    if (root1->val == root2->val) 
        result = is_contain(root1, root2);

    return result || bigtree_contain_smalltree(root1->left, root2)
                  || bigtree_contain_smalltree(root1->right, root2);
}

int main(int argc, char *argv[])
{
    bstnode *root1 = bstnode_create(8);
    root1->left = bstnode_create(8);
    root1->right = bstnode_create(7);
    root1->left->left = bstnode_create(9);
    root1->left->right = bstnode_create(2);
    root1->left->right->left = bstnode_create(4);
    root1->left->right->right = bstnode_create(7);
    bst_in_traverse(root1);
    printf("\n");

    bstnode *root2 = bstnode_create(8);
    root2->left = bstnode_create(9);
    root2->right = bstnode_create(2);
    root2->right->left = bstnode_create(4);
    root2->right->right = bstnode_create(7);
    bst_in_traverse(root2);
    printf("\n");

    printf("%d\n", bigtree_contain_smalltree(root1, root2));
}
