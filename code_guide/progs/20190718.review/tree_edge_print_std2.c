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
    
    print_right_edge(root->left, print && !root->left);
    print_right_edge(root->right, print);

    if (print || (!root->left && !root->right))
        printf("%-3ld", root->val);
}

void print_edge(treenode *root)
{
    if (!root)
        return;

    printf("%-3ld", root->val);
    if (root->left && root->right) {
        print_left_edge(root->left, 1);
        print_right_edge(root->right, 1);
    } else {
        print_edge(root->left ? root->left : root->right);
    }
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(10);
    tree_draw(root);
    print_edge(root);
    printf("\n");
}
