#include "ds.h"

#define ENQUEUE(q, x) queue_enqueue(q, (long)(x))
#define DEQUEUE(q) ((treenode *)queue_dequeue(q))

queue *gen_all_bst(int start, int end)
{
    // 这个 queue 用来装 start -> end 产生的所有形态
    // 的二叉树的根节点
    queue *q = queue_create();
    if (start > end) {
        ENQUEUE(q, NULL);
        return q;
    }

    // 对于 start -> end 之间所有的值
    // 分别让他们各自充当头节点
    for (int i = start; i <= end; i++) {
        // 创建头节点
        treenode *root = treenode_create(i);
        // 当 i 成为头节点时，左右子树各有多少种形态?
        // left, right 是装有左右子树不同形态根节点的队列
        queue *left = gen_all_bst(start, i - 1);
        queue *right = gen_all_bst(i + 1, end);
        // 对于每种左右子树
        for (deque_node *ln = left->header; ln; ln = ln->next) {
            for (deque_node *rn = right->header; rn; rn = rn->next) {
                treenode *l = (treenode *)ln->val;
                treenode *r = (treenode *)rn->val;
                root->left = l;
                root->right = r;
                treenode *newtree = tree_clone(root);
                ENQUEUE(q, newtree);
            }
        }
        tree_release(&root);
        queue_release(&left);
        queue_release(&right);
    }
    return q;
}


int main(int argc, char *argv[])
{
    int n = 4;
    queue *q = gen_all_bst(1, n);    
    while (!queue_empty(q))
        tree_draw(DEQUEUE(q));
}
