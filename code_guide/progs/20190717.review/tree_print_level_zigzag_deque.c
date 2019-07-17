#include "ds.h"

void tree_print_level_zigzag(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }

    int cur_level = 1;
    int next_level = 0;
    deque *d = deque_create();
#define PUSH_BACK(d, x) deque_push_back(d, (long)x)
#define PUSH_FRONT(d, x) deque_push_front(d, (long)x)
#define POP_FRONT(d) ((treenode *)deque_pop_front(d))
#define POP_BACK(d) ((treenode *)deque_pop_back(d))

    int get_from_front = 1;
    PUSH_BACK(d, root);
    while (!deque_empty(d)) {
        if (get_from_front) {
            root = POP_FRONT(d);
            if (root->left) {
                PUSH_BACK(d, root->left);
                next_level++;
            }
            if (root->right) {
                PUSH_BACK(d, root->right);
                next_level++;
            }
        } else {
            root = POP_BACK(d);
            if (root->right) {
                PUSH_FRONT(d, root->right);
                next_level++;
            }
            if (root->left) {
                PUSH_FRONT(d, root->left);
                next_level++;
            }
        }
        printf("%-3ld", root->val);
        if (--cur_level == 0) {
            printf("\n");
            get_from_front = !get_from_front;
            cur_level = next_level;
            next_level = 0;
        }
    }
    queue_release(&q);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(10);
    tree_draw(root);
    tree_print_level_zigzag(root);
}
