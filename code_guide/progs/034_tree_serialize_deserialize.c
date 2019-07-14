#include "ds.h"

char buf[1024] = { 0 };
int write_cursor;
int read_cursor;

void serialize_core(treenode *root)
{
    if (!root) {
        write_cursor += snprintf(buf + write_cursor, sizeof(buf), "#!");
        return;
    }

    write_cursor += snprintf(buf + write_cursor, sizeof(buf), "%ld!", root->val);
    serialize_core(root->left);
    serialize_core(root->right);
}

void serialize(treenode *root)
{
    write_cursor = 0;
    serialize_core(root);
    buf[write_cursor] = 0;
}

treenode *deserialize(void)
{
    if (read_cursor >= write_cursor)
        return NULL;

    if (buf[read_cursor] == '#') {
        read_cursor += 2;
        return NULL;
    }

    char *end = NULL;
    int val = strtol(buf + read_cursor, &end, 10);
    read_cursor += end - (buf + read_cursor) + 1;

    treenode *n = treenode_create(val);
    n->left = deserialize();
    n->right = deserialize();
    return n;
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
