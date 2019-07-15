#include "ds.h"

void tree_in(treenode *root)
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
        }
        printf("%-3ld", cur1->val);
        cur1 = cur1->right;
    }
    printf("\n");
}

void tree_pre(treenode *root)
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
                printf("%-3ld", cur1->val);
                cur1 = cur1->left;
                continue;
            }

            cur2->right = NULL;
        } else {
            printf("%-3ld", cur1->val);
        }
        cur1 = cur1->right;
    }
    printf("\n");
}

treenode *reverse_edge(treenode *from)
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

void print_edge_reverse(treenode *from)
{
    treenode *tail = reverse_edge(from);
    treenode *cur = tail;
    while (cur) {
        printf("%-3ld", cur->val);
        cur = cur->right;
    }
    reverse_edge(tail);
}

void tree_post(treenode *root)
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
            print_edge_reverse(cur1->left);
        }
        cur1 = cur1->right;
    }
    print_edge_reverse(root);
    printf("\n");
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(10);
    tree_draw(root);
    tree_pre(root);
    tree_in(root);
    tree_post(root);
}
