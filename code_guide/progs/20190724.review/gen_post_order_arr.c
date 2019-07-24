#include "ds.h"

long hash(long k) { return k; }

void gen_post_arr(long *pre, long *in, long *post, ht *h, int *post_idx, int ps, int pe, int is, int ie)
{
    if (ps > pe)
        return;
    
    post[(*post_idx)--] = pre[ps];
    int i = ht_get(h, pre[ps]);
    gen_post_arr(pre, in, post, h, post_idx, pe - ie + i + 1, pe, i + 1, ie);
    gen_post_arr(pre, in, post, h, post_idx, ps + 1, ps + i - is, is, i - 1);
}

void gen_arr(long *pre, long *in, long *post, int size)
{
    if (!pre || !in || !post || size <= 0)
        return;

    ht *h = ht_create(hash);
    for (int i = 0; i < size; i++)
        ht_insert(h, in[i], i);

    int post_idx = size - 1;
    gen_post_arr(pre, in, post, h, &post_idx, 0, size - 1, 0, size - 1);
    ht_release(&h);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(5);
    tree_draw(root);
    long *pre = to_pre_arr(root);
    long *in = to_in_arr(root);
    long *post = to_post_arr(root);
    printArrayL(post, 5);

    long post_gen[5] = { 0 };
    gen_arr(pre, in, post_gen, 5);
    printArrayL(post_gen, 5);
}
