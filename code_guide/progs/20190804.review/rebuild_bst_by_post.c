#include "ds.h"

treenode *rebuild_core(int *post, int start, int end)
{
    if (start > end)
        return NULL;

    treenode *root = treenode_create(post[end]);
    int less = -1, more = end;
    for (int i = start; i < end; i++) {
        if (post[i] < post[end])
            less = i;
        else if (more == end)
            more = i;
    }
    if (less == -1)
        root->right = rebuild_core(post, start, end - 1);
    else if (more == end)
        root->left = rebuild_core(post, start, end - 1);
    else if (less == more - 1) {
        root->right = rebuild_core(post, more, end - 1);
        root->left = rebuild_core(post, start, less);
    } else {
        printf("invalid post order\n");
        free(root);
        return NULL;
    }
    return root;
}

treenode *rebuild(int *post, int size)
{
    if (!post || size <= 0)
        return NULL;

    return rebuild_core(post, 0, size - 1);
}

int main(int argc, char *argv[])
{
    int size = 8;
    treenode *bst = bst_create(size);
    tree_draw(bst);

    int *post = to_post_arr_(bst);
    printArray(post, size);

    treenode *copy = rebuild(post, size);
    tree_draw(copy);
}
