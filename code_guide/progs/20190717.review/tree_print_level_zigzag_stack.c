#include "ds.h"

void tree_print_level_zigzag(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }

    int get_from_left = 1;
    int cur_level = 1;
    int next_level = 0;

    stack *s1 = stack_create();
    stack *s2 = stack_create();
#define PUSH(s, x) stack_push(s, (long)(x))
#define POP(s)  ((treenode *)stack_pop(s)) 

    PUSH(s1, root);
    while (!stack_empty(s1) || !stack_empty(s2)) {
        if (get_from_left) {
            root = POP(s1);
            if (root->left) {
                PUSH(s2, root->left);
                next_level++;
            }
            if (root->right) {
                PUSH(s2, root->right);
                next_level++;
            }
        } else {
            root = POP(s2);
            if (root->right) {
                PUSH(s1, root->right);
                next_level++;
            }
            if (root->left) {
                PUSH(s1, root->left);
                next_level++;
            }
        }
        printf("%-3ld", root->val);
        if (--cur_level == 0) {
            printf("\n");
            cur_level = next_level;
            next_level = 0;
            get_from_left = !get_from_left;
        }
    }

    stack_release(&s1);
    stack_release(&s2);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(10);
    tree_draw(root);
    tree_print_level_zigzag(root);
}
