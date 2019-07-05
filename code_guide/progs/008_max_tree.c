#include "ds.h"

long normal_hash(long key)
{
    return key;
}

void pop_and_set_map(stack *s, ht *h)
{
    int top = stack_pop(s);
    if (stack_empty(s))
        ht_insert(h, top, -1); 
    else 
        ht_insert(h, top, stack_peek(s));
}

void max_tree(int *arr, int size, treenode **root)
{
    ht *lmap = ht_create(normal_hash); 
    ht *rmap = ht_create(normal_hash); 
    stack *s = stack_create();

    for (int i = 0; i < size; i++) {
        int val = arr[i];
        while (!stack_empty(s) && stack_peek(s) < val) 
            pop_and_set_map(s, lmap);
        stack_push(s, val);
    }
    
    while (!stack_empty(s))
        pop_and_set_map(s, lmap);

    for (int i = size - 1; i >= 0; i--) {
        int val = arr[i];
        while (!stack_empty(s) && stack_peek(s) < val) 
            pop_and_set_map(s, rmap);
        stack_push(s, val);
    }
    while (!stack_empty(s))
        pop_and_set_map(s, rmap);

#define HT_INSERT(h, x, v) ht_insert(h, (long)x, (long)v)
#define HT_GET(h, x) ((treenode *)ht_get(h, (long)x))

    ht *node_map = ht_create(normal_hash);
    for (int i = 0; i < size; i++)
        HT_INSERT(node_map, arr[i], treenode_create(arr[i]));

    treenode *parent = NULL;
    for (int i = 0; i < size; i++) {
        int val = arr[i];
        int lg = ht_get(lmap, val);
        int rg = ht_get(rmap, val);
        treenode *n = HT_GET(node_map, val);
        if (lg < 0 && rg < 0) {
            *root = HT_GET(node_map, val);
            continue;
        } 

        if (lg < 0) 
            parent = HT_GET(node_map, rg);
        else if (rg < 0) 
            parent = HT_GET(node_map, lg);
        else {
            int min = lg < rg ? lg : rg;
            parent = HT_GET(node_map, min);
        }
        if (!parent->left)
            parent->left = n;
        else
            parent->right = n;
    }
}

int has_duplicate(int *arr, int size) 
{
    ht *h = ht_create(normal_hash);
    for (int i = 0; i < size; i++) {
        if (ht_get(h, arr[i]) > 0)
            return 1;
        ht_insert(h, arr[i], 1);
    }
    ht_release(&h);
    return 0;
}

int check_condition(treenode *root)
{
    if (!root)
        return 1;

    if (root->left && root->val < root->left->val)
        return 0;

    if (root->right && root->val < root->right->val)
        return 0;

    return check_condition(root->left) && check_condition(root->right);
}

int main(int argc, char *argv[])
{
    int size = 7;
    int *arr = NULL;
    int d = 0;
    do {
        arr = arrayWithRange(size, 1, 30);
        if ((d = has_duplicate(arr, size)))
            free(arr);
    } while (d);

    printArray(arr, size);
    treenode *root = NULL;
    max_tree(arr, size, &root);
    if (check_condition(root))
        printf("fit condition\n");
}
