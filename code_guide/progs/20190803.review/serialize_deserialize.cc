#include "ds.h"
#include <string>
#include <iostream>

using namespace std;

void pre(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }
    stack *s = stack_create();
#define PUSH(s, x) stack_push(s, (long)(x))
#define POP(s) ((treenode *)stack_pop(s))
    PUSH(s, root);
    while (!stack_empty(s)) {
        root = POP(s);
        printf("%-3ld", root->val);
        if (root->right) 
            PUSH(s, root->right);
        if (root->left)
            PUSH(s, root->left);
    }
    stack_release(&s);
    printf("\n");
}

string serialize(treenode *root)
{
    if (!root)
        return "#!";

    stack *s = stack_create();
    PUSH(s, root);
    string str;
    while (!stack_empty(s)) {
        root = POP(s);
        str += root ? to_string(root->val) + "!" : "#!";
        if (root) {
            PUSH(s, root->right);
            PUSH(s, root->left);
        }
    }
    stack_release(&s);
    return str;
}

treenode *deserialize(string &str, int &idx) 
{
    if (str[idx] == '#') {
        idx += 2;
        return NULL;
    }

    char *end = NULL;
    long v = strtol((char *)str.c_str() + idx, &end, 10);
    idx += (end - ((char *)str.c_str() + idx));
    idx++;
    treenode *n = treenode_create(v);
    n->left = deserialize(str, idx);
    n->right = deserialize(str, idx);
    return n;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);
    string str = serialize(root);
    cout << str << endl;
    int idx = 0;
    treenode *copy = deserialize(str, idx);
    tree_draw(copy);
}
