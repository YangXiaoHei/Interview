#include "ds.h"

void tree_level_zigzag_print(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }

    stack *fleft = stack_create();
    stack *fright = stack_create();

#define PUSH(s, x) stack_push(s, (long)x)
#define POP(s) ((treenode *)stack_pop(s))

    int i = 0;
    PUSH(fleft, root);
    while (!stack_empty(fleft) || !stack_empty(fright)) {
        if (i++ & 1) {
            while (!stack_empty(fright)) {
                root = POP(fright);
                printf("%-3ld", root->val);
                if (root->right)
                    PUSH(fleft, root->right);
                if (root->left)
                    PUSH(fleft, root->left);
            }
            printf("\n");
        } else {
            while (!stack_empty(fleft)) {
                root = POP(fleft);
                printf("%-3ld", root->val);
                if (root->left)
                    PUSH(fright, root->left);
                if (root->right)
                    PUSH(fright, root->right);
            }
            printf("\n");
        }
    }
    stack_release(&fleft);
    stack_release(&fright);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(10);
    tree_draw(root);
    tree_level_zigzag_print(root);
}
