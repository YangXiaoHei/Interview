#include "ds.h"

void get_kth_node(treenode *root, treenode **target, int *k)
{
    if (!root)
        return;

    if (*target)
        return;

    get_kth_node(root->left, target, k);

    if ((*k)-- == 0)
        *target = root;

    get_kth_node(root->right, target, k);
}

void gen_two_treenode(treenode *root, int size, treenode **n1, treenode **n2)
{
    int k = randWithRange(0, size);
    int m = randWithRange(0, size);
    get_kth_node(root, n1, &k);
    get_kth_node(root, n2, &m);
}

treenode* lowest_common_parent_in_tree(treenode *root, treenode *n1, treenode *n2)
{
    if (!root || !n1 || !n2)
        return NULL;

   if (n2 == n1)
        return n1;

    int len1 = 0, len2 = 0;
    for (treenode *c = n1; c; c = c->parent)
        len1++;
    for (treenode *c = n2; c; c = c->parent)
        len2++;

    int diff = len1 - len2;
    diff = diff < 0 ? -diff : diff;
    treenode *longer = len1 > len2 ? n1 : n2;
    treenode *shorter = longer == n1 ? n2 : n1;
    while (diff-- > 0)
        longer = longer->parent;

    while (longer && shorter) {
        if (longer == shorter)
            break;
        longer = longer->parent;
        shorter = shorter->parent;
    }

    if (!longer || !shorter) {
        printf("what a fuck?!\n");
        return NULL;
    }

    return longer;
}

int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);
    treenode *root = bst_create(10);
    tree_draw(root);
    treenode *n1 = NULL, *n2 = NULL;
    gen_two_treenode(root, 10, &n1, &n2);
    printf("n1 = %ld n2 = %ld\n", n1->val, n2->val);
    treenode *comm = lowest_common_parent_in_tree(root, n1, n2);
    if (comm)
        printf("lowest common parent is %ld\n", comm->val);
}
