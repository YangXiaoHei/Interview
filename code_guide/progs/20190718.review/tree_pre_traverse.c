#include "ds.h"

void tree_pre_traverse(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }

    stack *s = stack_create();
#define PUSH(s, x) stack_push(s, (long)(x))
#define POP(s) ((treenode *)stack_pop(s))

    PUSH(s, root);
    while (!stack_empty(s)) {
        root = POP(s);
        while (root) {
            if (root->right)
                PUSH(s, root->right);
            printf("%-3ld", root->val);
            root = root->left;
        }
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(10); 
    tree_draw(root);
    tree_pre_traverse(root);
}
