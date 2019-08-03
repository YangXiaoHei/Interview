#include "ds.h"

void zigzag(treenode *root)
{
    if (!root)
        return;

    stack *left = stack_create();
    stack *right = stack_create();

    int pop_from_left = 1;
    int cur_level = 1;
    int next_level = 0;
#define PUSH(s, x) stack_push(s, (long)(x))
#define POP(s) ((treenode *)stack_pop(s))

    PUSH(left, root);
    while (!stack_empty(left) || !stack_empty(right)) {
        if (pop_from_left) {
            root = POP(left);
            if (root->left) {
                PUSH(right, root->left);
                next_level++;
            }
            if (root->right) {
                PUSH(right, root->right);
                next_level++;
            }
        } else {
            root = POP(right);
            if (root->right) {
                PUSH(left, root->right);
                next_level++;
            }
            if (root->left) {
                PUSH(left, root->left);
                next_level++;
            }
        }

        printf("%-3ld", root->val);
        if (--cur_level == 0) {
            printf("\n");
            pop_from_left = !pop_from_left;
            cur_level = next_level;
            next_level = 0;
        }
    }
    stack_release(&left);
    stack_release(&right);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(7);
    tree_draw(root);
    zigzag(root);
}
