#include "ds.h"

char buf[1024] = { 0 };
int write_cursor = 0;
int read_cursor = 0;

#define ENQUEUE(q, x) queue_enqueue(q, (long)x)
#define DEQUEUE(q) ((treenode *)queue_dequeue(q))

void serialize(treenode *root)
{
    write_cursor = 0;
    queue *q = queue_create();

    ENQUEUE(q, root);
    while (!queue_empty(q)) {
        treenode *n = DEQUEUE(q);
        if (n) {
            write_cursor += snprintf(buf + write_cursor, sizeof(buf), "%ld!", n->val); 
            ENQUEUE(q, n->left);
            ENQUEUE(q, n->right);
        } else
            write_cursor += snprintf(buf + write_cursor, sizeof(buf), "#!");
    }
    queue_release(&q);
    buf[write_cursor] = 0;
}

treenode* deserialize()
{
    queue *q = queue_create();
    char *end = NULL;
    long val = strtol(buf + read_cursor, &end, 10);
    read_cursor += end - (buf + read_cursor) + 1;
    treenode *root = treenode_create(val);
    treenode *cur = NULL;
    ENQUEUE(q, root);
    while (!queue_empty(q)) {
        cur = DEQUEUE(q);

        if (buf[read_cursor] == '#') {
            cur->left = NULL;
            read_cursor += 2;
        } else {
            val = strtol(buf + read_cursor, &end, 10);
            read_cursor += end - (buf + read_cursor) + 1;
            cur->left = treenode_create(val);
            ENQUEUE(q, cur->left);
        }

        if (buf[read_cursor] == '#') {
            cur->right = NULL;
            read_cursor += 2;
        } else {
            val = strtol(buf + read_cursor, &end, 10);
            read_cursor += end - (buf + read_cursor) + 1;
            cur->right = treenode_create(val);
            ENQUEUE(q, cur->right);
        }
    }

    queue_release(&q);

    return root;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(10);
    tree_draw(root);
    serialize(root);
    printf("%s\n", buf);
    treenode *copy = deserialize();
    tree_draw(copy);
}
