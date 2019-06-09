#include <stdio.h>
#include <stdlib.h>
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
    n->left = n->right = NULL;
    return n;
}

int is_bst_postorder_core(int *arr, int leftmost, int rightmost)
{
    if (leftmost >= rightmost)
       return 1; 

    int root = arr[rightmost];
    int rt;
    for (rt = leftmost; rt != rightmost; rt++)
        if (arr[rt] > root)
            break;

    for (int j = rt; j != rightmost; j++)
        if (arr[j] < root)
            return 0;

    return is_bst_postorder_core(arr, leftmost, rt - 1) && is_bst_postorder_core(arr, rt, rightmost - 1);
}

int is_bst_postorder(int *arr, int size)
{
    if (!arr || size <= 0) 
        return 0;
    return is_bst_postorder_core(arr, 0, size - 1);
}

int main(int argc, char *argv[])
{
    int arr[] = {5, 7, 6, 9, 11, 10, 8};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", is_bst_postorder(arr, size));

    swap(&arr[0], &arr[size - 1]);
    printf("%d\n", is_bst_postorder(arr, size));

    int b[] = {7, 4, 6, 5};
    size = sizeof(b) / sizeof(b[0]);
    printf("%d\n", is_bst_postorder(b, size));

    swap(&b[0], &b[size - 1]);
    printf("%d\n", is_bst_postorder(b, size));
}
