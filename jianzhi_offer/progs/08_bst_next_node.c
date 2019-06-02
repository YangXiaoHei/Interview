#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

typedef struct bstnode {
    int val;
    struct bstnode *parent;
    struct bstnode *left;
    struct bstnode *right;
} bstnode;

bstnode *bstnode_create(int val)
{
    bstnode *n = malloc(sizeof(bstnode));
    if (!n) return NULL;
    n->val = val;
    n->left = n->right = NULL;
    n->parent = NULL;
    return n;
}

int bst_next_node(bstnode *root, int pre)
{
   if (!root) return -1;

   bstnode *pren = root;
   while (pren) {
       if (pre == pren->val)
           break;
       if (pre < pren->val) pren = pren->left;
       else                 pren = pren->right;
   }

   if (!pren) return -1;

   if (!pren->right) {
       while (pren->parent && pren->parent->left != pren)
           pren = pren->parent;

       if (!pren->parent)
           return -1;
       return pren->parent->val;
   } 

   pren = pren->right;
   while (pren->left)
       pren = pren->left;

   return pren->val;
}

void bst_insert(bstnode **root, int val)
{
    if (!root) return;

    bstnode *parent = *root;
    bstnode *cur = parent;
    while (cur) {
        if (val == cur->val)
            return;

        parent = cur;
        if (val < cur->val) cur = cur->left;
        else                cur = cur->right;
    }

    bstnode *n = bstnode_create(val);
    if (!parent) {
        *root = n;
        return;
    }
        
    n->parent = parent;
    if (val < parent->val)
        parent->left = n;
    else
        parent->right = n; 
}

void bst_intraverse(bstnode *root)
{
    if (!root) return;
    bst_intraverse(root->left);
    printf("%-3d", root->val);
    bst_intraverse(root->right);
}

int main(int argc, char *argv[]) 
{
    int size = 20;
    int *array = arrayWithRange(size, 0, size);
    int r = randWithRange(0, size);
    printArray(array, size);

    bstnode *root = NULL;
    for (int i = 0; i < size; i++)
        bst_insert(&root, array[i]);

    printf("in traverse : ");
    bst_intraverse(root);
    printf("\n");

    printf("r = %d\n", r);
    int val = bst_next_node(root, r);
    printf("next_node : %d\n", val);
}
