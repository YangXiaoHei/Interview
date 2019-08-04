#include "ds.h"

treenode *kth_node(treenode *root, int k)
{
    if (!root || k <= 0)
        return NULL;

    treenode *target = NULL;

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
        if (k-- == 1) 
            target = cur1;
        cur1 = cur1->right;
    }
    return target;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);
    int k = randWithRange(0, 15);
    printf("k = %d\n", k);
    treenode *kth = kth_node(root, k);
    if (kth)
        printf("node = %-3ld\n", kth->val);
    else
        printf("node not exist!\n");
}
