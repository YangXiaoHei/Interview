#include "ds.h"

#define HT_INSERT(h, k, v) ht_insert(h, (long)(k), (long)(v))
#define HT_CONTAIN(h, k) ht_contain(h, (long)(k))
#define HT_GET_H(h, k) ((ht *)ht_get(h, (long)(k)))
#define HT_GET_N(h, k) ((treenode *)ht_get(h, (long)(k)))

void init_map(treenode *root, ht *h)
{
    if (!root)
        return;

    HT_INSERT(h, root, ht_create());
    init_map(root->left, h);
    init_map(root->right, h);
}

void set_head_record(treenode *root, treenode *head, ht *h)
{
    if (!root)
        return;

    HT_INSERT(HT_GET_H(h, root), head, head);
    set_head_record(root->left, head, h);
    set_head_record(root->right, head, h);
}

void set_left(treenode *l, treenode *r, treenode *head, ht *h)
{
    if (!l)
        return;
    
    HT_INSERT(HT_GET_H(h, l), r, head);
    set_left(l->left, r, head, h);
    set_left(l->right, r, head, h);
}

void set_sub_record(treenode *l, treenode *r, treenode *head, ht *h)
{
    if (!r)
        return;

    set_left(l, r, head, h);
    set_sub_record(l, r->left, head, h);
    set_sub_record(l, r->right, head, h);
}

void init(treenode *root, ht *h)
{
    if (!root)
        return;

    set_head_record(root->left, root, h);
    set_head_record(root->right, root, h);

    set_sub_record(root->left, root->right, root, h);

    init(root->left, h);
    init(root->right, h);
}

treenode *query(treenode *root, treenode *n1, treenode *n2, ht *h)
{
    if (n1 == n2)
        return n1;
    
    if (HT_CONTAIN(HT_GET_H(h, n1), n2)) 
        return HT_GET_N(HT_GET_H(h, n1), n2);

    if (HT_CONTAIN(HT_GET_H(h, n2), n1))
        return HT_GET_N(HT_GET_H(h, n2), n1);

    return NULL;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(9);
    tree_draw(root);

    // 初始化记录项
    ht *h = ht_create();
    init_map(root, h);
    init(root, h);

    treenode *n1, *n2;
    tree_random_twonodes(root, &n1, &n2);
    printf("n1 = %ld n2 = %ld\n", n1->val, n2->val);
    treenode *com = query(root, n1, n2, h);
    if (com)
        printf("com = %ld\n", com->val);
    else
        printf("not exist!\n");
}
