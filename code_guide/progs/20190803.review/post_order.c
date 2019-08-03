#include "ds.h"

void post(treenode *root)
{
    if (!root)
        return;

    stack *s1 = stack_create();
    stack *s2 = stack_create();

#define PUSH(s, x) stack_push(s, (long)(x))
#define POP(s) ((treenode *)stack_pop(s))
    PUSH(s1, root);
    while (!stack_empty(s1)) {
        root = POP(s1);
        PUSH(s2, root);
        if (root->left)
            PUSH(s1, root->left);
        if (root->right)
            PUSH(s1, root->right);
    }
    while (!stack_empty(s2))
        printf("%-3ld", POP(s2)->val);
    printf("\n");
    stack_release(&s1);
    stack_release(&s2);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);
    post(root);
}
