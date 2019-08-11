#include "ds.h"

#define HT_INSERT(h, k, v) ht_insert(h, (long)(k), (long)(v))
#define HT_CONTAIN(h, k) ht_contain(h, (long)(k))
#define HT_GET(h, k) ((treenode *)ht_get(h, (long)(k)))

void init_map(treenode *root, ht *h)
{
    if (!root)
        return;

    if (root->left)
        HT_INSERT(h, root->left, root);

    if (root->right)
        HT_INSERT(h, root->right, root);

    init_map(root->left, h);
    init_map(root->right, h);
}

treenode *query(treenode *root, treenode *n1, treenode *n2, ht *h)
{
    if (!root || !n1 || !n2)
        return NULL;

    if (n1 == n2)
        return n1;

    ht *path = ht_create();
    HT_INSERT(h, root, NULL);
    while (HT_CONTAIN(h, n1)) {
        HT_INSERT(path, n1, 0);
        n1 = HT_GET(h, n1);
    }

    while (!HT_CONTAIN(path, n2))
        n2 = HT_GET(h, n2);

    ht_release(&path);
    return n2;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(9);
    tree_draw(root);

    // 初始化记录项
    ht *h = ht_create();
    init_map(root, h);

    treenode *n1, *n2;
    tree_random_twonodes(root, &n1, &n2);
    printf("n1 = %ld n2 = %ld\n", n1->val, n2->val);
    treenode *com = query(root, n1, n2, h);
    if (com)
        printf("com = %ld\n", com->val);
    else
        printf("not exist!\n");
}
