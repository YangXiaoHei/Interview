#include "ds.h"

int is_cbt(treenode *root)
{
    if (!root)
        return 0;

    int iscbt = 1;
    queue *q = queue_create();
#define ENQUEUE(x) queue_enqueue(q, (long)(x))
#define DEQUEUE() ((treenode *)queue_dequeue(q))
    ENQUEUE(root);
    int leaf = 0;
    while (!queue_empty(q)) {
        root = DEQUEUE();
        treenode *l = root->left;
        treenode *r = root->right;
        if ((leaf && (l || r)) || (r && !l)) {
            iscbt = 0;
            break;
        }
        if (l)
            ENQUEUE(l);

        if (r)
            ENQUEUE(r);
        else
            leaf = 1;
    }
    queue_release(&q);
    return iscbt;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(5);
    tree_draw(root);
    printf("%d\n", is_cbt(root));
}
