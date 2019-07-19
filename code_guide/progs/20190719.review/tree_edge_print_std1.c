#include "ds.h"

void collect_left_and_right(treenode *root, int level, int *arr)
{
    if (!root)
        return;

    if (arr[level * 2 + 0] == -1)
        arr[level * 2 + 0] = root->val;
    arr[level * 2 + 1] = root->val;

    collect_left_and_right(root->left, level + 1, arr);
    collect_left_and_right(root->right, level + 1, arr);
}

void print_middle_leaf(treenode *root, int level, int *arr)
{
    if (!root)
        return;

    print_middle_leaf(root->left, level + 1, arr);
    if (!root->left && !root->right && root->val != arr[level * 2 + 0] && root->val != arr[level * 2 + 1])
        printf("%-3ld", root->val);
    print_middle_leaf(root->right, level + 1, arr);
}

void print_tree_edge_std1(treenode *root)
{
    if (!root)
        return;

    int h = tree_height(root);
    int *arr = malloc(sizeof(int) * (h * 2));
    memset(arr, -1, sizeof(int) * (h * 2));
    collect_left_and_right(root, 0, arr);

    // 打印左边缘
    for (int l = 0; l < h; l++) 
        printf("%-3d", arr[l * 2 + 0]);

    // 打印中间叶节点
    print_middle_leaf(root, 0, arr);

    // 打印右边缘
    for (int l = h - 1; l >= 0; l--)
        if (arr[l * 2 + 0] != arr[l * 2 + 1])
            printf("%-3d", arr[l * 2 + 1]);
    free(arr);
    printf("\n");
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(7);
    tree_draw(root);
    print_tree_edge_std1(root);
}
