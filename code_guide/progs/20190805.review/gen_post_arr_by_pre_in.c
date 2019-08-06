#include "ds.h"

long hash(long key) { return key; }

void gen_post_arr(int *pre, int *in, int *post, int *post_idx, ht *h, int pi, int ps, int ii, int is)
{
    if (pi > ps)
        return;
    
    post[(*post_idx)--] = pre[pi];
    int i = ht_get(h, pre[pi]);
    gen_post_arr(pre, in, post, post_idx, h, ps - is + i + 1, ps, i + 1, is);
    gen_post_arr(pre, in, post, post_idx, h, pi + 1, pi + i - ii, ii, i - 1);
}

void gen_arr(int *pre, int *in, int *post, int size)
{
    ht *h = ht_create(hash);
    for (int i = 0; i < size; i++)
        ht_insert(h, in[i], i);

    int post_idx = size - 1;
    gen_post_arr(pre, in, post, &post_idx, h, 0, size - 1, 0, size - 1);
    ht_release(&h);
}

int main(int argc, char *argv[])
{
    int size = 8;
    treenode *root = bst_create(size);
    tree_draw(root);
    int *post = to_post_arr_(root);
    int *pre = to_pre_arr_(root);
    int *in = to_in_arr_(root);
    printArray(post, size);
    gen_arr(pre, in, post, size);
    printArray(post, size);
}
