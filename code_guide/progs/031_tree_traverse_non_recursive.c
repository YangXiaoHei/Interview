#include "ds.h"

#define STACK_PUSH(s, v) stack_push(s, (long)v)
#define STACK_POP(s) ((treenode *)stack_pop(s))

void pre_traverse_nr(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }

    stack *s = stack_create();

    STACK_PUSH(s, root);
    treenode *n = NULL;
    printf("prev -> ");
    while (!stack_empty(s)) {
        n = STACK_POP(s);
        while (n) {
            printf("%-3ld", n->val);
            if (n->right)
                STACK_PUSH(s, n->right);
            n = n->left;
        }
    }
    printf("\n");
    stack_release(&s);
}

void in_traverse_nr(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }    

    stack *s = stack_create();

    printf("in   -> ");
    while (!stack_empty(s) || root) {
        if (root) {
            STACK_PUSH(s, root);
            root = root->left;
        } else {
            root = STACK_POP(s);
            printf("%-3ld", root->val);
            root = root->right;
        }
    }
    printf("\n");
    stack_release(&s);
}

void post_traverse_nr(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }    

    stack *s1 = stack_create();
    stack *s2 = stack_create();

    printf("post -> ");
    STACK_PUSH(s1, root);
    while (!stack_empty(s1)) {
        treenode *n = STACK_POP(s1);
        STACK_PUSH(s2, n);
        if (n->left)
            STACK_PUSH(s1, n->left);
        if (n->right)
            STACK_PUSH(s1, n->right);
    }
    while (!stack_empty(s2)) 
        printf("%-3ld", STACK_POP(s2)->val);

    stack_release(&s1);
    stack_release(&s2);
    printf("\n");
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(10);
    pre_print(root);
    pre_traverse_nr(root);
    in_print(root);
    in_traverse_nr(root);
    post_print(root);
    post_traverse_nr(root);
}
