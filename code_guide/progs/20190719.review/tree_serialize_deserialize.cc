#include <iostream>
#include <string>
#include "ds.h"

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

treenode* deserialize(const string &str, int &i)
{
    if (str[i] == '#') {
       i += 2;
       return NULL; 
    }

    char *end = NULL;
    char *beg = (char *)str.c_str() + i;
    long val = strtol(beg, &end, 10);
    i += end - beg + 1; 
    treenode *root = treenode_create(val);
    root->left = deserialize(str, i);
    root->right = deserialize(str, i);
    return root;
}

int main()
{
    treenode *root = bst_create(6);
    tree_draw(root);
    string str;
    serialize(root, str);
    cout << str << endl;
    
    int i = 0;
    treenode *copy = deserialize(str, i);
    tree_draw(copy);

}
