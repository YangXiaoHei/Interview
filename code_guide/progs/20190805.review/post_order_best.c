#include "ds.h"

treenode *reverse_edge(treenode *head)
{
    treenode *prev = NULL;
    treenode *next = NULL;
    while (head) {
        next = head->right;
        head->right = prev;
        prev = head;
        head = next;
    }
    return prev;
}

void print_edge(treenode *root)
{
    treenode *tail = reverse_edge(root);
    while (tail) {
        printf("%-3ld", tail->val);
        tail = tail->right;
    }
    reverse_edge(tail);
}

void post(treenode *root)
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
    treenode *root = bst_create(8);
    tree_draw(root);
    post(root);
}
