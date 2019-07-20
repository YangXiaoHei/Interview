#include "ds.h"

int is_bst(treenode *root)
{
    if (!root)
        return 0;

    int is = 1;
    treenode *prev = NULL;
    stack *s = stack_create();
#define PUSH(s, x) stack_push(s, (long)(x))
#define POP(s) ((treenode *)stack_pop(s))
    while (!stack_empty(s) || root) {
        if (root) {
            PUSH(s, root);
            root = root->left;
        } else {
            root = POP(s);
            if (!prev)
                prev = root;
            else if (prev->val > root->val) {
                is = 0;
                break;
            }
            root = root->right;
        }
    }
    stack_release(&s);
    return is;
}

int main(int argc, char *argv[])
{
    /* treenode *root = bst_create(7); */
#define N(x) treenode_create(x)
    treenode *root = N(1);
    root->left = N(2);
    root->right = N(3);
    root->left->left = N(4);
    root->left->right = N(5);
    root->right->left = N(6);
    root->right->right = N(7);
    tree_draw(root);
    printf("is_bst : %d\n", is_bst(root));
}
