#include "ds.h"
#include <iostream>

using namespace std;

void serialize(treenode *root, string &str)
{
    str = "";
    if (!root) 
        return;

    stack *s = stack_create();
#define PUSH(s, x) stack_push(s, (long)(x))
#define POP(s) ((treenode *)stack_pop(s))
    PUSH(s, root);
    while (!stack_empty(s)) {
        root = POP(s);
        while (root) {
            PUSH(s, root->right);
            str += to_string(root->val) + "!";
            root = root->left;
        }
        str += "#!";
    }
    stack_release(&s);
}

treenode* deserialize(const string &str, int &i)
{
    if (str[i] == '#') {
        i += 2;
        return NULL;
    }
    char *ptr = (char *)str.c_str() + i;
    char *end = NULL;
    long v = strtol(ptr, &end, 10); 
    i += end - ptr + 1;

    treenode *n = treenode_create(v);
    n->left = deserialize(str, i);
    n->right = deserialize(str, i);
    return n;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(10);
    tree_draw(root);
    string str;
    serialize(root, str);
    cout << str << endl;
    int i = 0;
    treenode *copy = deserialize(str, i);
    tree_draw(copy);
}
