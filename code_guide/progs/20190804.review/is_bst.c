#include "ds.h"

int is_bst(treenode *root)
{
    if (!root)
        return 0;

    treenode *prev = NULL;
    int isbst = 1;

    stack *s = stack_create();
#define PUSH(x) stack_push(s, (long)(x))
#define POP() ((treenode *)stack_pop(s))
    while (!stack_empty(s) || root) {
        if (root) {
            PUSH(root);
            root = root->left;
        } else {
            root = POP();
            if (prev && prev->val > root->val) {
                isbst = 0;
                break;
            }
            prev = root;
            root = root->right;
        }
    }
    stack_release(&s);
    return isbst;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);
    printf("%d\n", is_bst(root));
}
