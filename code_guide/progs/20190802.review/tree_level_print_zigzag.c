#include "ds.h"

void zigzag_print(treenode *root)
{
    if (!root)
        return;

    deque *q = deque_create();
#define POP_BACK(q) ((treenode *)deque_pop_back(q))
#define POP_FRONT(q) ((treenode *)deque_pop_front(q))
#define PUSH_BACK(q, x) deque_push_back(q, (long)(x))
#define PUSH_FRONT(q, x) deque_push_front(q, (long)(x))

    int cur_level = 1;
    int next_level = 0;

    int pop_front = 1;
    PUSH_BACK(q, root);
    while (!deque_empty(q)) {
        if (pop_front) {
            root = POP_FRONT(q);
            if (root->left) {
                PUSH_BACK(q, root->left);
                next_level++;
            }
            if (root->right) {
                PUSH_BACK(q, root->right);
                next_level++;
            }
        } else {
            root = POP_BACK(q);
            if (root->right) {
                PUSH_FRONT(q, root->right);
                next_level++;
            }
            if (root->left) {
                PUSH_FRONT(q, root->left);
                next_level++;
            }
        }
        printf("%-3ld", root->val);
        if (--cur_level == 0) {
            printf("\n");
            cur_level = next_level;
            next_level = 0;
            pop_front = !pop_front;
        }
    }
    deque_release(&q);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);
    zigzag_print(root);
}
