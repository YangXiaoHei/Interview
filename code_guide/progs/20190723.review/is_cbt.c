#include "ds.h"

int is_cbt(treenode *root)
{
    int is_cbt = 1;
    queue *q = queue_create();
#define ENQUEUE(q, x) queue_enqueue(q, (long)(x))
#define DEQUEUE(q) ((treenode *)queue_dequeue(q))
    ENQUEUE(q, root);
    int leaf = 0;
    while (!queue_empty(q)) {
        root = DEQUEUE(q);
        treenode *l = root->left;
        treenode *r = root->right;
        if ((leaf && (l || r)) || (!l && r)) {
            is_cbt = 0;
            break;
        }
        if (l)
            ENQUEUE(q, l);
        if (r)
            ENQUEUE(q, r);
        else
            leaf = 1;
    }
    queue_release(&q);
    return is_cbt;
}

int main(int argc, char *argv[])
{
    int size = randWithRange(1, 20);
    treenode *root = cbt_create(size);
    tree_draw(root); 
    printf("is cbt : %d\n", is_cbt(root));

    treenode *root2 = bst_create(size);
    tree_draw(root2);
    printf("is cbt : %d\n", is_cbt(root2));
}
