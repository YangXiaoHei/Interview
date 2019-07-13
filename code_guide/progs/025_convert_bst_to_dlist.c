#include "ds.h"

void convert_core(treenode *root, treenode **head, treenode **last)
{
    if (!root)
        return;

    convert_core(root->left, head, last);

    if (!*last) {
        *last = root;
        *head = root;
    } else {
        (*last)->right = root;
        root->left = *last;
        *last = root;
    }

    convert_core(root->right, head, last);
}

void convert(treenode **root)
{
    if (!root || !*root)
        return;
    treenode *last = NULL;
    treenode *head = NULL;
    convert_core(*root, &head, &last);
    *root = head;
}

void bst_list_print(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }
    for (treenode *cur = root; cur; cur = cur->right)
        printf("%-3ld", cur->val);
    printf("\n");
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(10);
    pre_print(root);
    in_print(root);
    post_print(root);
    convert(&root);
    bst_list_print(root);    
}
