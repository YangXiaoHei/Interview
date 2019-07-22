#include "ds.h"

int is_bst(treenode *root)
{
    stack *s = stack_create();
#define PUSH(s, x) stack_push(s, (long)(x))
#define POP(s) ((treenode *)stack_pop(s))
    treenode *prev = NULL;
    int result = 1;
    while (!stack_empty(s) || root) {
        if (root) {
            PUSH(s, root);
            root = root->left;
        } else {
            root = POP(s);
            if (prev && prev->val > root->val) {
                result = 0;
                break;
            }
            prev = root;
            root = root->right;
        }
    }
    stack_release(&s);
    return result;
}

int main(int argc, char *argv[])
{
    /* treenode *root = bst_create(6); */
#define N(x) treenode_create(x)
    treenode *root = N(1);
    root->left = N(2);
    root->right = N(3);
    tree_draw(root);
    printf("is bst %d\n", is_bst(root));
}
