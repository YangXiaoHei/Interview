#include "ds.h"

long hash(long k) { return k; }

int is_same_topo(treenode *n1, treenode *n2)
{
    if (!n1 && !n2)
        return 1;

    if (!n1 ^ !n2)
        return 0;

    if (n1->val != n2->val)
        return 0;

    return is_same_topo(n1->left, n2->left) && is_same_topo(n1->right, n2->right);
}

treenode *rebuild_by_pre_post(long *pre, long *post, int size, ht *h, int pi, int ps, int si, int ss)
{
    if (pi > ps)
        return NULL;
    treenode *n = treenode_create(post[ss--]);
    if (pi == ps)
        return n;

    int i = ht_get(h, pre[++pi]);
    n->left = rebuild_by_pre_post(pre, post, size, h, pi, pi + i - si, si, i);
    n->right = rebuild_by_pre_post(pre, post, size, h, pi + i - si + 1, ps, i + 1, ss);
    return n;
}

treenode *rebuild(long *pre, long *post, int size)
{
    if (!pre || !post || size <= 0)
        return NULL;

    ht *h = ht_create(hash);
    for (int i = 0; i < size; i++)
        ht_insert(h, post[i], i);
    treenode *root = rebuild_by_pre_post(pre, post, size, h, 0, size - 1, 0, size - 1);
    ht_release(&h);
    return root;
}

int main(int argc, char *argv[])
{
    int size = 7;
    treenode *root = bst_create(size);
    tree_draw(root);
    long *pre = to_pre_arr(root);
    long *post = to_post_arr(root);
    printArrayL(pre, size);
    printArrayL(post, size);
    treenode *copy = rebuild(pre, post, size);
    tree_draw(copy);
    if (!is_same_topo(root, copy)) {
        printf("后序遍历相同，但拓扑结构不一致\n");
    }
}
