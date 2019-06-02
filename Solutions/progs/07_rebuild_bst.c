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
    if (!n) return NULL;
    n->left = n->right = NULL;
    n->val = val;
    return n;
}

bstnode *_bst_rebuild(int *pre, int ps, int pe, int *in, int is, int ie)
{
    printf("ps=%d pe=%d is=%d ie=%d\n", ps, pe, is, ie);
    if (ps > pe) {
        printf("return\n");
        return NULL;
    }

    int root_idx = is;
    int root_val = pre[ps];
    while (root_idx <= ie  && in[root_idx] != root_val)
        root_idx++;

    if (root_idx > ie) {
        printf("invalid input\n");
        exit(1);
    }

    bstnode *n = bstnode_create(root_val);

    n->left = _bst_rebuild(pre, ps + 1, ps + root_idx - is, in, is, root_idx - 1);
    n->right = _bst_rebuild(pre, ps + root_idx - is + 1, pe, in, root_idx + 1, ie);

    return n;
}

bstnode *bst_rebuild(int *pre, int *in, int len)
{
    if (!pre || !in || len <= 0)
        return NULL;
    return _bst_rebuild(pre, 0, len - 1, in, 0, len - 1);
}

void bst_intraverse(bstnode *root)
{
    if (!root) return;
    bst_intraverse(root->left);
    printf("%-3d", root->val);
    bst_intraverse(root->right);
}

void bst_pretraverse(bstnode *root)
{
    if (!root) return;
    printf("%-3d", root->val);
    bst_pretraverse(root->left);
    bst_pretraverse(root->right);
}

int main(int argc, char *argv[])
{
    int pre[] = {1, 2, 4, 7, 3, 5, 6, 8};    
    int in[] = {4, 7, 2, 1, 5, 3, 8, 6};
    bstnode *root = bst_rebuild(pre, in, 8);

    /*
     * 1  4  7  2  5  3  8  6
     * 4  7  2  1  5  3  8  6
     */
    bst_pretraverse(root);
    printf("\n");
    bst_intraverse(root);
    printf("\n");
}
