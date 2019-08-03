#include "ds.h"

void in(treenode *root)
{
    if (!root)
        return;

    treenode *cur1 = root, *cur2 = NULL;
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
        printf("%-3ld", cur1->val);
        cur1 = cur1->right;
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);
    in(root);
}
