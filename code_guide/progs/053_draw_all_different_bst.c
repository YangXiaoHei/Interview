#include "ds.h"

#define ENQUEUE(q, x) queue_enqueue(q, (long)(x))
#define DEQUEUE(q) ((treenode *)queue_dequeue(q))

queue *gen_all_bst(int start, int end)
{
    queue *q = queue_create();
    if (start > end) {
        ENQUEUE(q, NULL);
        return q;
    }

    for (int i = start; i <= end; i++) {
        treenode *n = treenode_create(i);
        queue *left = gen_all_bst(start, i - 1);
        queue *right = gen_all_bst(i + 1, end);
        // 这里写得比较丑陋... 直接访问数据结构内部, 有更精巧的方法, 比如实现一个遍历的宏
        // 但意思到位就行了... 学习算法不要分心
        for (deque_node *l = left->header; l; l = l->next) {
            for (deque_node *r = right->header; r; r = r->next) {
                n->left = (treenode *)l->val;
                n->right = (treenode *)r->val;
                treenode *newtree = tree_clone(n);
                ENQUEUE(q, newtree);
            }
        }
        tree_release(&n);
        queue_release(&left);
        queue_release(&right);
    }
    return q;
}

int main(int argc, char *argv[])
{
    queue *all_bst = gen_all_bst(1, 4);    
    while (!queue_empty(all_bst)) 
        tree_draw(DEQUEUE(all_bst));
    queue_release(&all_bst);
}
