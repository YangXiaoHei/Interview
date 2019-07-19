#include <iostream>
#include <string>
#include "ds.h"

using namespace std;

void serialize(treenode *root, string &str)
{
    queue *q = queue_create();
#define ENQUEUE(q, x) queue_enqueue(q, (long)(x))
#define DEQUEUE(q) ((treenode *)queue_dequeue(q))
    ENQUEUE(q, root);
    while (!queue_empty(q)) {
        root = DEQUEUE(q);
        if (!root)
            str += "#!";
        else {
            str += to_string(root->val) + "!";
            ENQUEUE(q, root->left);
            ENQUEUE(q, root->right);
        }
    }
    queue_release(&q);
}

treenode *parse_and_create(const string &str, int &i)
{
    if (str[i] == '#') {
        i += 2;
        return NULL;
    }
    char *beg = (char *)str.c_str() + i;
    char *end = NULL;
    long v = strtol(beg, &end, 10);
    i += end - beg + 1;
    treenode *root = treenode_create(v);
    return root;
}

treenode *deserialize(const string &str) 
{
    queue *q = queue_create();
    int i = 0;
    treenode *root = parse_and_create(str, i);
    treenode *head = root;
    ENQUEUE(q, root);
    while (!queue_empty(q)) {
        root = DEQUEUE(q);
        root->left = parse_and_create(str, i);
        root->right = parse_and_create(str, i);
        if (root->left)
            ENQUEUE(q, root->left);
        if (root->right)
            ENQUEUE(q, root->right);
    }
    queue_release(&q);
    return head;
}

int main()
{
    treenode *root = bst_create(7);
    tree_draw(root);
    string str;
    serialize(root, str);
    cout << str << endl;

    treenode *copy = deserialize(str);
    tree_draw(copy);
}
