#include "ds.h"
#include <string>
#include <iostream>

using namespace std;

string serialize(treenode *root)
{
    queue *q = queue_create();
#define ENQUEUE(x) queue_enqueue(q, (long)(x))
#define DEQUEUE() ((treenode *)queue_dequeue(q))
    ENQUEUE(root);
    string str;
    while (!queue_empty(q)) {
        root = DEQUEUE();
        str += !root ? "#!" : to_string(root->val) + "!";
        if (root) {
            ENQUEUE(root->left);
            ENQUEUE(root->right);
        }
    }
    queue_release(&q);
    return str;
}

treenode *next_node(string &str, int &idx)
{
    if (str[idx] == '#') {
        idx += 2;
        return NULL;
    }
    char *end = NULL;
    long v = strtol((char *)str.c_str() + idx, &end, 10);
    idx += (end - (char *)str.c_str() - idx) + 1;
    return treenode_create(v);
}

treenode *deserialize(string &str)
{
    queue *q = queue_create();
    int idx = 0;
    treenode *n = next_node(str, idx);
    treenode *root = n;
    ENQUEUE(n);
    while (!queue_empty(q)) {
        n = DEQUEUE();
        n->left = next_node(str, idx);
        n->right = next_node(str, idx);
        if (n->left) 
            ENQUEUE(n->left);
        if (n->right)
            ENQUEUE(n->right);
    }
    queue_release(&q);
    return root;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);
    string str = serialize(root);
    treenode *copy = deserialize(str);
    tree_draw(copy);
}
