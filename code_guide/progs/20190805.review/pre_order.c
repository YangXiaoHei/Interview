#include "ds.h"

void pre(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }
    stack *s = stack_create();
#define PUSH(x) stack_push(s, (long)(x))
#define POP() ((treenode *)stack_pop(s))

    PUSH(root);
    while (!stack_empty(s)) {
        root = POP();
        printf("%-3ld", root->val);
        if (root->right)
            PUSH(root->right);
        if (root->left)
            PUSH(root->left);
    }
    stack_release(&s);
    printf("\n");
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);

    pre(root);
}
