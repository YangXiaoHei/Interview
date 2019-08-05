#include "ds.h"

#define ENQUEUE(q, x) queue_enqueue(q, (long)(x))
#define DEQUEUE(q) ((treenode *)queue_dequeue(q))

queue *gen_all_bst_core(int start, int end)
{
    queue *q = queue_create();
    if (start > end) {
        ENQUEUE(q, NULL);
        return q;
    }

    for (int i = start; i <= end; i++) {
        treenode *n = treenode_create(i);
        queue *lq = gen_all_bst_core(start, i - 1);
        queue *rq = gen_all_bst_core(i + 1, end);
        for (deque_node *pp = lq->header; pp; pp = pp->next) {
            for (deque_node *qq = rq->header; qq; qq = qq->next) {
                n->left = (treenode *)pp->val;
                n->right = (treenode *)qq->val;
                ENQUEUE(q, tree_clone(n));
            }
        }
        tree_release(&n);
        queue_release(&lq);
        queue_release(&rq);
    }
    return q;
}

queue* gen_all_bst(int n)
{
    return gen_all_bst_core(1, n); 
}

int main(int argc, char *argv[])
{
    queue *q = gen_all_bst(4);
    while (!queue_empty(q))
        tree_draw(DEQUEUE(q));
}
