#include "ds.h"
#include <string>
#include <iostream>

using namespace std;

#define BLANK ' '
#define XNULL ' '
#define NLEFT ' '
#define NRIGHT ' '

string xget_string(treenode *root, int leftslot, int rightmost, int slotwidth)
{
    if (!root) 
        return rightmost ? 
            string(leftslot * slotwidth, BLANK) + string(slotwidth, XNULL): 
            string(leftslot * slotwidth, BLANK) + string(slotwidth, XNULL) + string(leftslot * slotwidth, BLANK) + string(slotwidth, BLANK);

    long val = root->val;
    int width = get_num_width((int)val);
    int l = (slotwidth - width) / 2;
    int r = slotwidth - width - l;
    string valstr = string(l, NLEFT) + to_string(val) + string(r, NRIGHT);
    return rightmost ? 
        string(leftslot * slotwidth, BLANK) + valstr :
        string(leftslot * slotwidth, BLANK) + valstr + string(leftslot * slotwidth, BLANK) + string(slotwidth, BLANK);
}

void draw(treenode *root)
{
    if (!root) 
        return;

    int height = tree_height(root);
    int slots = pow(2, height) - 1;

    int cur_level = 1;
    int next_level = 0;

    int cur_depth = 1;
    int slotwidth = 3;

    queue *q = queue_create();
#define ENQUEUE(x) queue_enqueue(q, (long)(x))
#define DEQUEUE() ((treenode *)queue_dequeue(q))
    ENQUEUE(root);
    while (cur_depth <= height) {
        root = DEQUEUE();
        ENQUEUE(root ? root->left : NULL);
        ENQUEUE(root ? root->right : NULL);
        next_level += 2;

        int leftslot = slots / pow(2, cur_depth);
        cout << xget_string(root, leftslot, cur_level == 1, slotwidth);

        if (--cur_level == 0) {
            cout << endl << endl;
            cur_level = next_level;
            next_level = 0;
            cur_depth++;
        }
    }

    queue_release(&q);
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(10);
    draw(root);
}
