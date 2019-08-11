#include "ds.h"

int pre_seq[100], pre_size = 0;
int in_seq[100], in_size = 0;

void pre_trav(long v)
{
    pre_seq[pre_size++] = v;
}

void in_trav(long v)
{
    in_seq[in_size++] = v;
}

void gen_arr(int *pre, int *in, int *post, int *post_idx, int ps, int pe, int is, int ie, ht *h)
{
    if (ps > pe)
        return;

    post[(*post_idx)--] = pre[ps];
    int i = ht_get(h, pre[ps]);
    gen_arr(pre, in, post, post_idx, pe - ie + i + 1, pe, i + 1, ie, h);
    gen_arr(pre, in, post, post_idx, ps + 1, ps + i - is, is, i - 1, h);
}

void gen_post_arr(int *pre, int *in, int size, int *post)
{
    int post_idx = size - 1;
    ht *h = ht_create();
    for (int i = 0; i < size; i++)
        ht_insert(h, in[i], i);
    gen_arr(pre, in, post, &post_idx, 0, size - 1, 0, size - 1, h);
    ht_release(&h);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(7);
    tree_draw(root);    
    pre_traverse_funptr(root, pre_trav);
    in_traverse_funptr(root, in_trav);
    printArray(pre_seq, pre_size);
    printArray(in_seq, in_size);
    int post_seq[100];
    gen_post_arr(pre_seq, in_seq, pre_size, post_seq);
    printArray(post_seq, pre_size);
}
