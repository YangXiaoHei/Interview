#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char buf[8192] = { 0 };
char *read_ptr = buf;
char *write_ptr = buf;

void xx_write(char c)
{
    assert(write_ptr - buf < sizeof(buf));
    if (c >= 0 && c <= 9)
        c += '0';
    *write_ptr++ = c; 
}

int xx_read(char *c)
{
    assert(read_ptr - buf < sizeof(buf));
    *c = *read_ptr++; 
    if (*c >= '0' && *c <= '9')
        *c -= '0';
    return *c >= 0 && *c <= 9;
}

void xx_print(void)
{
    char *p = buf;
    while (p != write_ptr)
        printf("%-2c", *p++);
    printf("\n");
}

typedef struct bstnode {
    int val;
    struct bstnode *left;
    struct bstnode *right;
} bstnode;

bstnode *bstnode_create(int val)
{
    bstnode *n = malloc(sizeof(bstnode));
    if (!n) exit(1);
    n->val = val;
    n->left = n->right = NULL;
    return n;
}

void bst_in_traverse(bstnode *root)
{
    if (!root)
        return;
    bst_in_traverse(root->left);
    printf("%-3d", root->val);
    bst_in_traverse(root->right);
}

void bst_print(bstnode *root)
{
    bst_in_traverse(root);
    printf("\n");
}

void bst_serialize(bstnode *root)
{
    if (!root) {
        xx_write('$');
        return;
    }
    xx_write(root->val);
    bst_serialize(root->left);
    bst_serialize(root->right);
}

void bst_deserialize(bstnode **root)
{
    char c;
    if (!xx_read(&c))
        return;

    *root = bstnode_create(c);
    bst_deserialize(&(*root)->left);
    bst_deserialize(&(*root)->right);
}

int main(int argc, char *argv[])
{
    bstnode *root = bstnode_create(1);
    root->left = bstnode_create(2);
    root->right = bstnode_create(3);
    root->left->left = bstnode_create(4);
    root->right->left = bstnode_create(5);
    root->right->right = bstnode_create(6);
    bst_print(root);
    bst_serialize(root);
    xx_print();

    bstnode *root2 = NULL;
    bst_deserialize(&root2);
    bst_print(root2);
}
