#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tool.h"

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
    n->right = n->left = NULL;
    return n;
}

void bst_insert(bstnode **root, int val)
{
    if (!root) 
        return;

    bstnode *bn = bstnode_create(val);
    if (!*root) {
        *root = bn;
        return;
    }
    bstnode *parent = NULL, *cur = *root;
    while (cur) {
        if (cur->val == val) {
            free(bn);
            return;
        }
        parent = cur;
        if (val < cur->val)
            cur = cur->left;
        else
            cur = cur->right;
    }
    if (val < parent->val)
        parent->left = bn;
    else
        parent->right = bn;
}

void bst_remove(bstnode **root, int val)
{
    if (!root || !*root) 
        return;

    bstnode *parent = NULL;
    bstnode *cur = *root;
    while (cur) {
        if (cur->val == val)
            break;
        parent = cur;
        if (val < cur->val)
            cur = cur->left;
        else
            cur = cur->right;
    }
    if (!cur)
        return;

    if (!cur->left) {
        if (!parent) {
            bstnode *tmp = cur;
            cur = cur->right;
            free(tmp);
            *root = cur;
            return;
        }
        if (cur == parent->left)
            parent->left = cur->right;
        else
            parent->right = cur->right;
        free(cur);
    } else if (!cur->right) {
        if (!parent) {
            bstnode *tmp = cur;
            cur = cur->left;
            free(tmp);
            *root = cur;
            return;
        }
        if (cur == parent->left)
            parent->left = cur->left;
        else
            parent->right = cur->left;
        free(cur);
    } else {
        bstnode *replaced = cur;
        parent = cur;
        cur = cur->right;
        while (cur->left) {
            parent = cur;
            cur = cur->left;
        }
        /* at this moment cur not have a left child */
        replaced->val = cur->val;
        if (cur == parent->right)
            parent->right = cur->right;
        else
            parent->left = cur->right;
        free(cur);
    }
}

bstnode *bst_create(int size)
{
    bstnode *root = NULL;
    int n = size;
    while (size--) {
        int r = randWithRange(0, n);
        usleep(10);
        printf("insert %-3d\n", r);
        bst_insert(&root, r);
    }
    return root;
}

void bst_in_traverse(bstnode *root)
{
    if (!root) 
        return;

    bst_in_traverse(root->left);
    printf("%-3d", root->val);
    bst_in_traverse(root->right);
}

void bst_test(void)
{
    bstnode *root = bst_create(10);
    bst_in_traverse(root); 
    printf("\n");

    while (root) {
        int r = randWithRange(0, 10);
        printf("remove %-3d\n", r);
        bst_remove(&root, r);
        bst_in_traverse(root); 
        printf("\n");
    }
}

void convert_bst_to_list_core(bstnode *root, bstnode **last)
{
    if (!root)
        return;

    convert_bst_to_list_core(root->left, last);
    root->left = *last;
    if (*last)
        (*last)->right = root;
    *last = root;
    convert_bst_to_list_core(root->right, last);
}

bstnode *convert_bst_to_list(bstnode *root)
{
    bstnode *last = NULL;
    bstnode *head = NULL;
    convert_bst_to_list_core(root, &last);
    head = last;
    while (head && head->left)
        head = head->left;
    return head;
}

void bst_list_print(bstnode *head)
{
    printf("dual list convert by bst\n");
    while (head) {
        printf("%-3d", head->val);
        head = head->right;
    }
    printf("\n"); 
}

void bst_print(bstnode *root)
{
    bst_in_traverse(root); 
    printf("\n");
}

int main(int argc, char *argv[])
{
    bstnode *root = bst_create(10);
    bst_print(root);
    bstnode *list = convert_bst_to_list(root);
    bst_list_print(list);
}
