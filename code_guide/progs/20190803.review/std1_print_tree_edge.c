#include "ds.h"

void collect_lrmost(treenode *root, treenode **arr, int level)
{
    if (!root)
        return;

    if (!arr[level * 2 + 0])
        arr[level * 2 + 0] = root;
    arr[level * 2 + 1] = root;

    collect_lrmost(root->left, arr, level + 1);
    collect_lrmost(root->right, arr, level + 1);
}

void print_leaf(treenode *root, treenode **arr, int level)
{
    if (!root)
        return;

    print_leaf(root->left, arr, level + 1);
    if (!root->left && !root->right) {
        if (arr[level * 2 + 0] != root && arr[level * 2 + 1] != root)
          printf("%-3ld", root->val);  
    }
    print_leaf(root->right, arr, level + 1);
}

void edge_print(treenode *root)
{
    int height = tree_height(root);
    treenode **arr = malloc(sizeof(treenode *) * 2 * height);
    for (int i = 0; i < 2 * height; i++)
        arr[i] = NULL;

    collect_lrmost(root, arr, 0);

    for (int i = 0; i < height; i++) {
        if (arr[i * 2 + 0]) 
            printf("%-3ld", arr[i * 2 + 0]->val);
    }

    print_leaf(root, arr, 0);

    for (int i = height - 1; i >= 0; i--) {
        if (arr[i * 2 + 1] && arr[i * 2 + 1] != arr[i * 2 + 0])
            printf("%-3ld", arr[i * 2 + 1]->val);
    }
    printf("\n");
    free(arr);
}

int main(int argc, char *argv[])
{
     #define N(x) treenode_create(x)

    treenode *root = N(1);
    root->left = N(2);
    root->left->right = N(4);
    root->left->right->left = N(7);
    root->left->right->right = N(8);
    root->left->right->right->right = N(11);
    root->left->right->right->right->left = N(13);
    root->left->right->right->right->right = N(14);
    root->right = N(3);
    root->right->left = N(5);
    root->right->right = N(6);
    root->right->left->left = N(9);
    root->right->left->right = N(10);
    root->right->left->left->left = N(12);
    root->right->left->left->left->left = N(15);
    root->right->left->left->left->right = N(16);
    tree_draw(root);
    edge_print(root);
    printf("\n");
    tree_draw(root);
    edge_print(root);
}
