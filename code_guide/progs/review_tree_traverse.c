#include "ds.h"

#define PUSH(s, x) stack_push(s, (long)x)
#define POP(s) ((treenode *)stack_pop(s))

#define ENQUEUE(q, x) queue_enqueue(q, (long)x)
#define DEQUEUE(q) ((treenode *)queue_dequeue(q))

void tree_in(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }
    stack *s = stack_create();
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

void tree_pre(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }

    stack *s = stack_create();
    PUSH(s, root);
    while (!stack_empty(s)) {
        root = POP(s);
        while (root) {
            printf("%-3ld", root->val);
            if (root->right)
                PUSH(s, root->right);
            root = root->left;
        }
    }
    printf("\n");
    stack_release(&s);
}

void tree_post(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }
    stack *s1 = stack_create();
    stack *s2 = stack_create();
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
    treenode *root = bst_create(10);
    tree_draw(root);
    tree_pre(root);
    tree_in(root);
    tree_post(root);
}
