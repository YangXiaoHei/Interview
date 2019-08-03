#include "ds.h"
#include <iostream>
#include <string>

using namespace std;

void serialize(treenode *root, string &str)
{
    if (!root) {
        str += "#!";
        return;
    }
    str += to_string(root->val) + "!";
    serialize(root->left, str);
    serialize(root->right, str);
}

string serialize(treenode *root)
{
    string str;
    serialize(root, str);
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
    idx += (end - (char *)str.c_str() - idx) + 1;
    treenode *n = treenode_create(v);
    n->left = deserialize(str, idx);
    n->right = deserialize(str, idx);
    return n;
}

treenode *deserialize(string &str)
{
    int idx = 0;
    return deserialize(str, idx);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);
    string str = serialize(root);
    cout << str << endl;
    tree_draw(deserialize(str));
}
