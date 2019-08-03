#include "ds.h"

void print_left_edge(treenode *root, int print)
{
    if (!root)
        return;

    if (print || (!root->left && !root->right))
        printf("%-3ld", root->val);

    print_left_edge(root->left, print);
    print_left_edge(root->right, print && !root->left);
}

void print_right_edge(treenode *root, int print)
{
    if (!root)
        return;

    print_right_edge(root->left, print && !root->right);
    print_right_edge(root->right, print);

    if (print || (!root->left && !root->right))
        printf("%-3ld", root->val);
}

void edge_print(treenode *root)
{
    if (!root)
        return;

    printf("%-3ld", root->val);
    if (root->left && root->right) {
        print_left_edge(root->left, 1);
        print_right_edge(root->right, 1);
    } else
        edge_print(root->left ? root->left : root->right);
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
}

