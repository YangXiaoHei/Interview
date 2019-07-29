#include "ds.h"

treenode *lowest_common_parent(treenode *root, treenode *n1, treenode *n2)
{
    if (!root || !n1 || !n2)
        return NULL;

    int len1 = 0, len2 = 0;
    for (treenode *cur = n1; cur; cur = cur->parent)
        len1++;
    for (treenode *cur = n2; cur; cur = cur->parent)
        len2++;

    int diff = len1 - len2;
    diff = diff < 0 ? -diff : diff;

    treenode *longer = len1 > len2 ? n1 : n2;
    treenode *shorter = longer == n1 ? n2 : n1;

    while (diff--)
        longer = longer->parent;

    while (longer != shorter) {
        longer = longer->parent;
        shorter = shorter->parent;
    }
    return longer;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(10);
    tree_draw(root);
    treenode *n1, *n2;
    tree_random_twonodes(root, &n1, &n2);
    printf("n1 = %ld n2 = %ld\n", n1->val, n2->val);
    treenode *com = lowest_common_parent(root, n1, n2);
    printf("com = %ld\n", com->val);
}
