#include "ds.h"

void longest_path_of_sum_in_tree_core(treenode *root, ht *h, int *len, int level, int sum, int k)
{
    if (!root)
        return;

    sum += root->val;
    if (!ht_contain(h, sum)) 
        ht_insert(h, sum, level);

    if (ht_contain(h, sum - k)) {
        int idx = ht_get(h, sum - k);
        if (level - idx > *len) 
            *len = level - idx;
    }

    longest_path_of_sum_in_tree_core(root->left, h, len, level + 1, sum, k);
    longest_path_of_sum_in_tree_core(root->right, h, len, level + 1, sum, k);

    if (ht_get(h, sum) == level) 
        ht_remove(h, sum);
}

long normal_hash(long key)
{
    return key;
}

int longest_path_of_sum_in_tree(treenode *root, int k)
{
    int len = 0;
    ht *h = ht_create(normal_hash);
    ht_insert(h, 0, -1);
    longest_path_of_sum_in_tree_core(root, h, &len, 0, 0, k);
    ht_release(&h);
    return len;
}

int main(int argc, char *argv[])
{
    int size = 10;
    int *arr = arrayNoDupWithRange(size, -5, 5);
    printArray(arr, size);

    treenode *root = bst_create_with_arr(arr, size);
    tree_draw(root);

    int k = randWithRange(0, 10);
    printf("k = %d, longest path = %d\n", k, longest_path_of_sum_in_tree(root, k));
}
