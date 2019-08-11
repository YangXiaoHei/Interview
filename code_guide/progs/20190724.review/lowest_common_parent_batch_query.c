#include "ds.h"

#define HT_INSERT(h, k, v) ht_insert(h, (long)(k), (long)(v))
#define HT_GET_HT(h, k) ((ht *)ht_get(h, (long)(k)))
#define HT_GET_N(h, k) ((treenode *)ht_get(h, (long)(k)))
#define HT_CONTAIN(h, k) ht_contain(h, (long)k)

void set_right(treenode *left, treenode *right, treenode *root, ht *h)
{
    if (!right)
        return;

    ht *subh = HT_GET_HT(h, left);
    HT_INSERT(subh, right, root);
    set_right(left, right->right, root, h);
    set_right(left, right->left, root, h);
}

void set_left(treenode *left, treenode *right, treenode *root, ht *h)
{
    if (!left)
       return;

    set_right(left, right, root, h);
    set_left(left->left, right, root, h);
    set_left(left->right, right, root, h); 
}

void set_subtree_record(treenode *root, ht *h)
{
    if (!root)
        return;

    set_left(root->left, root->right, root, h);
    set_subtree_record(root->left, h);
    set_subtree_record(root->right, h); 
}

void set_head_record(treenode *root, treenode *head, ht *h)
{
    if (!root)
        return;

    ht *subh = HT_GET_HT(h, root);
    HT_INSERT(subh, head, head);

    set_head_record(root->left, head, h);
    set_head_record(root->right, head, h);
}

void set_all_subcptable(treenode *root, ht *h)
{
    if (!root)
        return;

    set_head_record(root->left, root, h);
    set_head_record(root->right, root, h);
    set_subtree_record(root, h);

    set_all_subcptable(root->left, h);
    set_all_subcptable(root->right, h);
}

void init_all_subcptable(treenode *root, ht *h)
{
    if (!root)
        return;

    ht *subh = ht_create();
    HT_INSERT(h, root, subh);
    init_all_subcptable(root->left, h);
    init_all_subcptable(root->right, h);
}

void init_cptable(treenode *root, ht *h)
{
    init_all_subcptable(root, h); 
    set_all_subcptable(root, h);
}

treenode *query(ht *h, treenode *n1, treenode *n2)
{
    if (n1 == n2)
        return n1;

    if (HT_CONTAIN(h, n1) && HT_CONTAIN(HT_GET_HT(h, n1), n2))
        return HT_GET_N(HT_GET_HT(h, n1), n2);

    if (HT_CONTAIN(h, n2) && HT_CONTAIN(HT_GET_HT(h, n2), n1))
        return HT_GET_N(HT_GET_HT(h, n2), n1);

    return NULL;
}

int main(int argc, char *argv[])
{
    ht *h = ht_create();
    treenode *root = bst_create(8);
    tree_draw(root);
    treenode *n1 = NULL, *n2 = NULL;
    tree_random_twonodes(root, &n1, &n2);
    init_cptable(root, h);
    printf("n1 = %ld n2 = %ld common parent = %ld\n", n1->val, n2->val, query(h, n1, n2)->val);
}
