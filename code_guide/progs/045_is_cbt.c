#include "ds.h"

int is_cbt(treenode *root)
{
    int leaf = 0;
    queue *q = queue_create();
#define ENQUEUE(q, x) queue_enqueue(q, (long)(x))
#define DEQUEUE(q) ((treenode *)queue_dequeue(q))
    ENQUEUE(q, root);
    while (!queue_empty(q)) {
        root = DEQUEUE(q);
        treenode *l = root->left;
        treenode *r = root->right;

        if ((leaf && (l || r)) || (r && !l))
            return 0;

        if (l)
            ENQUEUE(q, l);

        if (r)
            ENQUEUE(q, r);
        else
            leaf = 1;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(5);
    tree_draw(root);
    printf("is cbt=%d\n", is_cbt(root));
}
