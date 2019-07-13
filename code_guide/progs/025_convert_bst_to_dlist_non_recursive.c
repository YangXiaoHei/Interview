#include "ds.h"

void convert(treenode **rootptr)
{
    if (!rootptr || !*rootptr)
        return;

    treenode *root = *rootptr;

    stack *s = stack_create();

#define STACK_PUSH(x, v) stack_push(x, (long)v)
#define STACK_POP(x) ((treenode *)stack_pop(x))

    treenode *head = NULL, *tail = NULL;

    treenode *cur = root;
    while (!stack_empty(s) || cur) {
        if (cur) {
            STACK_PUSH(s, cur);
            cur = cur->left;
        } else {
            cur = STACK_POP(s);
            if (!head) {
                head = tail = cur;
            } else {
                tail->right = cur;
                cur->left = tail;
                tail = cur;
            }
            cur = cur->right;
        }
    }
    stack_release(&s);
    *rootptr = head;
}

void bst_list_print(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }
    for (treenode *cur = root; cur; cur = cur->right)
        printf("%-3ld", cur->val);
    printf("\n");
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(10);
    in_print(root);
    convert(&root);
    bst_list_print(root);
}
