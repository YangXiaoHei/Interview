#include "ds.h"

#define HT_INSERT(h, k, v) ht_insert(h, (long)(k), (long)(v))
#define HT_CONTAIN(h, k) ht_contain(h, (long)(k))
#define HT_GET(h, k) ((treenode *)ht_get(h, (long)(k)))

void init_ptable(treenode *root, ht *h)
{
    if (!root)
        return;

    if (root->right)
        HT_INSERT(h, root->right, root);

    if (root->left)
        HT_INSERT(h, root->left, root);

    init_ptable(root->left, h);
    init_ptable(root->right, h);
}

treenode *lowest_common_parent(treenode *root, treenode *n1 ,treenode *n2)
{
    if (!root || !n1 || !n2)
        return NULL;

    if (n1 == n2)
        return n1;

    ht *h = ht_create();
    HT_INSERT(h, root, NULL);
    init_ptable(root, h);

    ht *path = ht_create();
    while (HT_CONTAIN(h, n1)) {
        HT_INSERT(path, n1, 0);
        n1 = HT_GET(h, n1);
    }

    while (!HT_CONTAIN(path, n2))
        n2 = HT_GET(h, n2);

    ht_release(&h);
    ht_release(&path);

    return n2;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);
    treenode *n1 = NULL, *n2 = NULL;
    tree_random_twonodes(root, &n1, &n2);
    printf("n1 = %ld n2 = %ld common parent = %ld\n", n1->val, n2->val, lowest_common_parent(root, n1, n2)->val);
}
