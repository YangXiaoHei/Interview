#include "ds.h"

int post_seq[100], post_size = 0;
int in_seq[100], in_size = 0;

void post_trav(long v)
{
    post_seq[post_size++] = v;
}
void in_trav(long v)
{
    in_seq[in_size++] = v;
}

treenode *rebuild_tree_by_in_post(int *in, int *post, int *post_idx, int start, int end)
{
    if (start > end)
        return NULL;

    int root = post[(*post_idx)--];
    int in_mid = start;
    for (; in_mid <= end && in[in_mid] != root; in_mid++)
        ;

    if (in_mid > end) {
        printf("invalid sequence\n");
        exit(1);
    }

    treenode *n = treenode_create(root);
    n->right = rebuild_tree_by_in_post(in, post, post_idx, in_mid + 1, end);
    n->left = rebuild_tree_by_in_post(in, post, post_idx, start, in_mid - 1);
    return n;
}

treenode *rebuild_tree(int *in, int *post, int size)
{
    if (!in || !post || size <= 0)
        return NULL;

    int post_idx = size - 1;
    return rebuild_tree_by_in_post(in, post, &post_idx, 0, size - 1);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);
    in_traverse_funptr(root, in_trav);
    post_traverse_funptr(root, post_trav);
    printArray(in_seq, in_size);
    printArray(post_seq, post_size);
    treenode *copy = rebuild_tree(in_seq, post_seq, post_size);
    tree_draw(copy);

}
