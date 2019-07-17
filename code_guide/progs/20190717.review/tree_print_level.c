#include "ds.h"

void tree_print_level(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }

    queue *q = queue_create();
#define ENQUEUE(q, x) queue_enqueue(q, (long)x)
#define DEQUEUE(q) ((treenode *)queue_dequeue(q))

    int next_level = 0;
    int cur_level = 1;
    ENQUEUE(q, root);
    while (!queue_empty(q)) {
        root = DEQUEUE(q);
        if (root->left) {
            ENQUEUE(q, root->left);
            next_level++;
        }
        if (root->right) {
            ENQUEUE(q, root->right);
            next_level++;
        }
        printf("%-3ld", root->val);
        if (--cur_level == 0) {
            printf("\n");
            cur_level = next_level;
            next_level = 0;
        }
    }
    queue_release(&q);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(10);
    tree_draw(root);
    tree_print_level(root);
}
