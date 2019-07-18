#include "ds.h"

void tree_in_traverse(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }

    stack *s = stack_create();
#define PUSH(s, x) stack_push(s, (long)(x))
#define POP(s) ((treenode *)stack_pop(s))
    while (!stack_empty(s) || root) {
        if (root) {
            PUSH(s, root);
            root = root->left;
        } else {
            root = POP(s);
            printf("%-3ld", root->val);
            root = root->right;
        }
    }
    printf("\n");
    stack_release(&s);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(10);
    tree_draw(root);
    tree_in_traverse(root);
}
