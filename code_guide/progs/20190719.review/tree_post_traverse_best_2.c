#include "ds.h"

treenode* reverse_edge(treenode *from)
{
    treenode *prev = NULL, *next = NULL;
    while (from) {
        next = from->right;
        from->right = prev;
        prev = from;
        from = next;
    }
    return prev;
}

void print_edge(treenode *root)
{
    treenode *tail = reverse_edge(root);
    for (treenode *cur = tail; cur; cur = cur->right)
        printf("%-3ld", cur->val);
    reverse_edge(tail);
}

void tree_post_traverse_best(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }

    treenode *cur1 = root, *cur2 = NULL;
    while (cur1) {
        cur2 = cur1->left;
        if (cur2) {
            while (cur2->right && cur2->right != cur1) 
                cur2 = cur2->right;

            if (!cur2->right) {
                cur2->right = cur1;
                cur1 = cur1->left;
                continue;
            }

            cur2->right = NULL;
            print_edge(cur1->left);
        } 
        cur1 = cur1->right;
    }
    print_edge(root);
    printf("\n");
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(7);
    tree_draw(root);
    tree_post_traverse_best(root);
}
