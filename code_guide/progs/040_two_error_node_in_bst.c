#include "ds.h"

void two_error_node(treenode *root, treenode **arr)
{
    if (!root || !arr)
        return;

    stack *s = stack_create();
#define PUSH(s, x) stack_push(s, (long)x)
#define POP(s) ((treenode *)stack_pop(s))
    treenode *prev = NULL;
    while (!stack_empty(s) || root) {
        if (root) {
            PUSH(s, root);
            root = root->left;
        } else {
            root = POP(s);
            if (prev && prev->val > root->val) {
                if (!arr[0])
                    arr[0] = prev;
                arr[1] = root;
            }
            prev = root;
            root = root->right;
        }
    }
}

int main(int argc, char *argv[])
{
#define N(x) treenode_create(x)
    treenode *root = N(5);

    root->left = N(7);
    /* root->left = N(3); */

    root->left->left = N(2);
    root->left->left->left = N(1);
    root->left->right = N(4);

    root->right = N(3);
    /* root->left = N(3); */

    root->right->left = N(6);
    root->right->right = N(8);
    tree_draw(root);
    treenode *arr[2] = { 0 };

    two_error_node(root, arr);

    if (arr[0])
        printf("error node : %ld\n", arr[0]->val);
    if (arr[1])
        printf("error node : %ld\n", arr[1]->val);
}
