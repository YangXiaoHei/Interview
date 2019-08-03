#include "ds.h"

void two_error_nodes(treenode *root, treenode **arr)
{
    treenode *cur1 = root, *cur2 = NULL;
    treenode *prev = NULL;

    arr[0] = arr[1] = NULL;

    while (cur1) {
        cur2 = cur1->left;
        if (cur2) {
            while (cur2->right && cur2->right != cur1)
                cur2 = cur2->right;

            if (!cur2->right) {
                cur2->right = cur1;
                cur1 = cur1->left;
                continue;
            }

            cur2->right = NULL;
        } 
        if (prev && prev->val > cur1->val) {
            arr[0] = arr[0] ? arr[0] : prev; 
            arr[1] = cur1;
        }
        prev = cur1;
        cur1 = cur1->right;
    }
}

int main(int argc, char *argv[])
{
#define N(x) treenode_create(x)
    treenode *arr[2] = { NULL };
    treenode *root = N(5);
    root->left = N(3);
    root->right = N(7);
    root->left->left = N(2);
    root->left->right = N(4);
    root->right->left = N(6);
    root->right->right = N(8);
    tree_draw(root);

    root->left->val = 4;
    root->left->right->val = 3;
    tree_draw(root);
    
    two_error_nodes(root, arr);
    printf("%-3ld %-3ld\n", arr[0]->val, arr[1]->val);
}
