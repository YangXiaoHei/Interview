#include <iostream>
#include <string>
#include "ds.h"

using namespace std;

string get_node_str(treenode *root, int slotwidth)
{
    if (!root) 
        return string(slotwidth, ' ');

    int width = get_num_width(root->val);
    int left = (slotwidth - width) / 2;
    int right = slotwidth - left - width;
    return string(left, ' ') + to_string(root->val) + string(right, ' ');
}

void print_tree_visually(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }

    int height = tree_height(root);
    int nslots = pow(2, height) - 1;
    int slotwidth = 3;

    queue *q = queue_create();
#define ENQUEUE(q, x) queue_enqueue(q, (long)(x))
#define DEQUEUE(q) ((treenode *)queue_dequeue(q))
    int cur_level = 1;
    int next_level = 0;
    int cur_height = 1;
    string cur_line;
    ENQUEUE(q, root);
    while (cur_height <= height) {
        root = DEQUEUE(q);
        ENQUEUE(q, !root ? NULL : root->left);
        ENQUEUE(q, !root ? NULL : root->right);
        next_level += 2;

        cur_line = "";
        int leftfill = nslots / pow(2, cur_height); 
        leftfill *= slotwidth;
        int rightfill = leftfill;

        cur_line += string(leftfill, ' ');
        cur_line += get_node_str(root, slotwidth);
        cur_line += string(rightfill, ' ');
        cur_line += string(slotwidth, ' ');
        
        cout << cur_line;
        
        if (--cur_level == 0) {
            cout << endl << endl;
            cur_level = next_level;
            next_level = 0;
            cur_height++;
        }
    }
    queue_release(&q);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(5);
    print_tree_visually(root);
    tree_draw(root);
}
