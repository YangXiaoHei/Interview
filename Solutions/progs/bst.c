#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tool.h"

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

void bst_insert(bstnode **rootp, int val)
{
    if (!rootp)
        return;

    bstnode *n = bstnode_create(val);
    if (!*rootp) {
      *rootp = n;  
      return;
    }

    bstnode **cur = rootp;
    while (*cur) {
        int cval = (*cur)->val;
        if (val == cval) {
            free(n);
            return;
        }

        if (val < cval) cur = &((*cur)->left);
        else            cur = &((*cur)->right);
    }
    *cur = n;
}

void bst_in_traverse(bstnode *root)
{
    if (!root) return;
    bst_in_traverse(root->left);
    printf("%-3d", root->val);
    bst_in_traverse(root->right);  
}

void bst_delete(bstnode **root, int val)
{
    if (!*root) return;
    bstnode *cur = *root;
    bstnode *parent = cur;
    bstnode *tmp = NULL;
    while (cur) {
        if (val == cur->val) {
            if (!cur->left) {
                if (parent == cur) {
                    tmp = *root;
                    *root = (*root)->right;
                    free(tmp);
                    break;
                } 

                if (parent->left == cur) 
                    parent->left = cur->right;
                else
                    parent->right = cur->right;
                free(cur);
            } else if (!cur->right) {
                if (parent == cur) {
                    tmp = *root;
                    *root = (*root)->left;
                    free(tmp);
                    break;
                }

                if (parent->left == cur) 
                    parent->left = cur->left;
                else  
                    parent->right = cur->left;
                free(cur);
            } else {
                bstnode *leftmax = cur->right;
                parent = leftmax;
                while (leftmax->left) {
                    parent = leftmax;
                    leftmax = leftmax->left; 
                }
                cur->val = leftmax->val;

                if (parent == leftmax) 
                    cur->right = leftmax->right;
                else 
                    parent->left = leftmax->right;
               
                free(leftmax);
            }
            break;
        }

        parent = cur;
        if (val < cur->val)
            cur = cur->left;
        else 
            cur = cur->right;
    }
}

bstnode *bst_create(int size)
{
    bstnode *root = NULL;
    while (size--) {
        int val = randWithRange(0, 10);
        printf("insert %-3d\n", val);
        bst_insert(&root, val);
    }
    return root;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    bstnode *bst = bst_create(10);
    bst_in_traverse(bst);    
    printf("\n");

    while (bst) {
        int del = randWithRange(0, 10);
        printf("delete %-3d\n", del);
        bst_delete(&bst, del);
        bst_in_traverse(bst);    
        printf("\n");
    }
}


