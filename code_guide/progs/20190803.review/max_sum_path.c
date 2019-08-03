#include "ds.h"

int len = 0;

long hash(long key) { return key; }

void max_sum_path(treenode *root, ht *h, int key, int sum, int level)
{
    if (!root)
       return; 

    sum += root->val;
    if (!ht_contain(h, sum)) 
        ht_insert(h, sum, level);

    if (ht_contain(h, sum - key) && !(key == 0 && level == ht_get(h, sum - key))) {
        int l = ht_get(h, sum - key);
        if (level - l > len)
            len = level - l;
    }

    max_sum_path(root->left, h, key, sum, level + 1);
    max_sum_path(root->right, h, key, sum, level + 1);

    if (ht_get(h, sum) == level)
        ht_remove(h, sum);
}

int sum_path(treenode *root, int key)
{
    ht *h = ht_create(hash);
    ht_insert(h, 0, -1);
    max_sum_path(root, h, key, 0, 0);
    ht_release(&h);
    return len;
}

int main(int argc, char *argv[])
{
    int size = 8;
    int *arr = arrayWithRange(size, -10, 10);
    treenode *root = bst_create_with_arr(arr, size);
    tree_draw(root);
    int k = 0;
    printf("please input k -> ");
    while (scanf("%d", &k) != EOF) {
        printf("%d\n", sum_path(root, k));
        printf("please input k -> ");
    }
} 
