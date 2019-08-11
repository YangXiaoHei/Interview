#include "ds.h"

void sum_path_core(treenode *root, ht *h, int key, int sum, int level, int *find, int *pathlen)
{
    if (!root)
        return;

    if (*find)
        return;

    sum += root->val;
    if (!ht_contain(h, sum))
       ht_insert(h, sum, level); 

    if (ht_contain(h, sum - key) && !(key == 0 && ht_get(h, sum - key) == level)) {
        int l = ht_get(h, sum - key);
        *pathlen = level - l;
        *find = 1;
        return;
    }

    sum_path_core(root->left, h, key, sum, level + 1, find, pathlen);
    sum_path_core(root->right, h, key, sum, level + 1, find, pathlen);

    if (ht_get(h, sum) == level)
        ht_remove(h, sum);
}

int sum_path(treenode *root, int key)
{
    if (!root)
        return 0;

    ht *h = ht_create();
    ht_insert(h, 0, -1);
    int find = 0; 
    int pathlen = 0;
    sum_path_core(root, h, key, 0, 0, &find, &pathlen);
    ht_release(&h);
    return pathlen;
}

int main(int argc, char *argv[])
{
    int size = 6;
    int *arr = arrayWithRange(size, -10, 10);
    treenode *root = bst_create_with_arr(arr, size);
    tree_draw(root);
    int k = 0;
    printf("please input k ->");
    while (scanf("%d", &k) != EOF) {
        printf("%d\n", sum_path(root, k));
        printf("please input k ->");
    }
}
