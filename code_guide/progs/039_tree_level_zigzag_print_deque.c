#include "ds.h"

void tree_level_print_zigzag(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }

    deque *d = deque_create();

#define PUSH_BACK(d, x) deque_push_back(d, (long)x)
#define PUSH_FRONT(d, x) deque_push_front(d, (long)x)
#define POP_BACK(d) ((treenode *)deque_pop_back(d))
#define POP_FRONT(d) ((treenode *)deque_pop_front(d))

    int cur_level = 1;
    int next_level = 0;
    int get_from_front = 1;
    PUSH_FRONT(d, root);
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
            get_from_front = !get_from_front;
            printf("\n");
            cur_level = next_level;
            next_level = 0;
        }
    }
    deque_release(&d);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(10);
    tree_draw(root);
    tree_level_print_zigzag(root);
}
