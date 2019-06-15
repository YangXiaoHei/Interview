#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

typedef int val_type;

typedef struct avlnode {
   val_type val; 
   int height;
   int size;
   struct avlnode *left;
   struct avlnode *right;
} avlnode;

avlnode *avlnode_create(val_type val)
{
    avlnode *n = malloc(sizeof(avlnode));
    if (!n) exit(1);
    n->val = val;
    n->height = 0;
    n->size = 1;
    n->left = n->right = NULL;
    return n;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int size(avlnode *n)
{
    return n ? n->size : 0;
}

int height(avlnode *n)
{
    return n ? n->height : -1;
}

avlnode* rotate_left(avlnode *n)
{
    avlnode *up = n->right;
    
    n->right = up->left;
    up->left = n;

    up->size = n->size;
    n->size = 1 + size(n->left) + size(n->right);

    n->height = 1 + max(height(n->left), height(n->right));
    up->height = 1 + max(height(up->left), height(up->right));
    
    return up;
}

avlnode* rotate_right(avlnode *n)
{
    avlnode *up = n->left;

    n->left = up->right;
    up->right = n;
    
    up->size = n->size;
    n->size = 1 + size(n->left) + size(n->right);

    n->height = 1 + max(height(n->left), height(n->right));
    up->height = 1 + max(height(up->left), height(up->right));

    return up;
}

int balance_factor(avlnode *n)
{
    return height(n->left) - height(n->right);
}

avlnode * balance(avlnode *n)
{
    if (balance_factor(n) < -1) {
        if (balance_factor(n->right) > 0) 
            n->right = rotate_right(n->right);
        n = rotate_left(n);
    } else if (balance_factor(n) > 1) {
        if (balance_factor(n->left) < 0) 
           n->left = rotate_left(n->left);
        n = rotate_right(n);
    }
    return n;
}

avlnode* avl_insert_core(avlnode *root, val_type val)
{
    if (!root) 
        return avlnode_create(val);

    if (root->val == val)
        return root;

    if (val < root->val) 
        root->left = avl_insert_core(root->left, val);
    else
        root->right = avl_insert_core(root->right, val);

    root->height = 1 + max(height(root->left), height(root->right));
    root->size = 1 + size(root->left) + size(root->right);
    return balance(root);
}

void avl_insert(avlnode **root, val_type val)
{
    if (!root)
        return;
    *root = avl_insert_core(*root, val);
}

avlnode *avl_remove_min_not_free(avlnode *root)
{
    if (!root->left) 
        return root->right;

    root->left = avl_remove_min_not_free(root->left);
    root->height = 1 + max(height(root->left), height(root->right));
    root->size = 1 + size(root->left) + size(root->right);
    return balance(root);
}

avlnode *avl_min_node(avlnode *root)
{
    while (root->left)
        root = root->left;
    return root;
}

avlnode *avl_remove_core(avlnode *root, val_type val)
{
    if (!root)
        return NULL;

    if (root->val == val) {
        avlnode *todel = root;
        avlnode *up = NULL;
        if (!todel->left) {
            up = todel->right;
            free(todel);
            return up;
        }
        if (!todel->right) {
            up = todel->left;
            free(todel);
            return up;
        }
        up = avl_min_node(todel->right);
        up->right = avl_remove_min_not_free(todel->right);
        up->left = todel->left;
        free(todel);
        up->height = 1 + max(height(up->left), height(up->right));
        up->size = 1 + size(up->left) + size(up->right);
        return up;
    }

    if (val < root->val)
        root->left = avl_remove_core(root->left, val);
    else
        root->right = avl_remove_core(root->right, val);
    root->height = 1 + max(height(root->left) , height(root->right));
    root->size = 1 + size(root->left) + size(root->right);
    return root;
}

void avl_remove(avlnode **root, val_type val)
{
    if (!root) 
       return;
   *root = avl_remove_core(*root, val); 
}

void avl_in_traverse(avlnode *root)
{
    if (!root)
        return;

    avl_in_traverse(root->left);
    printf("%-3d", root->val);
    avl_in_traverse(root->right);
}

void avl_print(avlnode *root)
{
    avl_in_traverse(root);
    printf(" height=%-3d size=%-3d\n", height(root), size(root));
}

avlnode *avl_create(int sz)
{
    avlnode *root = NULL;
    int last_height = height(root);
    while (sz--) {
        int r = randWithRange(0, sz);
        avl_insert(&root, r);
        if (height(root) != last_height) {
            printf("height=%-3d size=%-3d\n", height(root), size(root));
            last_height = height(root);
        }
    }
    return root;
}

void avl_test(void)
{
    int sz = 10000;
    avlnode *root = avl_create(sz);
    int last_height = height(root);
    while (root) {
        int r = randWithRange(0, sz);
        avl_remove(&root, r);
        if (height(root) != last_height) {
            printf("height=%-3d size=%-3d\n", height(root), size(root));
            last_height = height(root);
        }
    }
}

void shuffle(int *arr, int size)
{
    for (int i = 0; i < size; i++) {
        int r = randWithRange(0, size - i) + i;
        swap(arr + r, arr + i);
    }
}

int main(int argc, char *argv[])
{
    avl_test();
}


