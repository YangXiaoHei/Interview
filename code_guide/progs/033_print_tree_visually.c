#include "ds.h"

int max(int a, int b)
{
    return a > b ? a : b;
}

int tree_height(treenode *root)
{
    if (!root) 
        return 0;

    return 1 + max(tree_height(root->left), tree_height(root->right));
}

int tree_size(treenode *root)
{
    if (!root) 
        return 0;

    return 1 + tree_size(root->left) + tree_size(root->right);
}

int get_num_width(int num)
{
    int width = 1;
    while (num /= 10)
        width++;
    return width;
}

int get_width_num(int w)
{
    int i = 0;
    while (w--)
        i = i * 10 + 9;
    return i;
}

void print_tree_visually(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }

    queue *q = queue_create();

#define ENQUEUE(q, x) queue_enqueue(q, (long)x)
#define DEQUEUE(q)  ((treenode *)queue_dequeue(q))

#define CHAR_NULL ' ' /* null 节点用什么符号来表示 */
#define CHAR_FILL ' ' /* 数字不足宽度用什么符号来填充 */
#define CHAR_SPACE ' ' /* 不同的节点间用什么符号来分隔 */
#define NUM_WIDTH 2  /* 数字的最大宽度，比如 12 的宽度是 2，999 的宽度是 3 */

    ENQUEUE(q, root);
    int h = tree_height(root);
    int s = tree_size(root);
    int slots = pow(2, h) - 1;
    int cur_level = 1;
    int next_level = 0;
    char buf[1024];
    int len = 0;
    int numwidth = NUM_WIDTH; /* 999 .9. 90. */

    int slotwidth = numwidth; /* 桶宽度和数字宽度要一样 */
    printf("--------------- num_width=%d, height=%d, size=%d -----------------\n", numwidth, h, s);

    int cur_height = 1;
    while (cur_height <= h) {
        treenode *n = DEQUEUE(q);
        if (n) {
            ENQUEUE(q, n->left);
            ENQUEUE(q, n->right);
        } else {
            ENQUEUE(q, NULL);
            ENQUEUE(q, NULL);
        }
        next_level += 2;

        int nslot = slots / pow(2, cur_height); 
        len = 0;

        long num = n ? n->val : get_width_num(numwidth);
        int width = n ? get_num_width(num) : 1;
        int left_nfill = (numwidth - width) / 2;
        int right_nfill = numwidth - width - left_nfill;

        // 该行左边填充
        for (int i = 0; i < nslot * slotwidth; i++)
            buf[i] = CHAR_SPACE;
        len += nslot * slotwidth;

        // 数字左边填充空格
        for (int i = 0; i < left_nfill; i++)
            buf[i + len] = CHAR_FILL;
        len += left_nfill;

        if (n)
            len += snprintf(buf + len, sizeof(buf), "%ld", num);
        else
            len += snprintf(buf + len, sizeof(buf), "%c", CHAR_NULL);

        // 数字右边填充空格
        for (int i = 0; i < right_nfill; i++)
            buf[i + len] = CHAR_FILL;
        len += right_nfill;

        // 该行右边填充
        for (int i = 0; i < nslot * slotwidth; i++)
            buf[i + len] = CHAR_SPACE;
        len += nslot * slotwidth;

        for (int i = 0; i < 1 * slotwidth; i++)
            buf[i + len] = CHAR_SPACE;
        len += 1 * slotwidth;

        buf[len] = 0;
        printf("%s", buf);

        if (--cur_level == 0) {
            cur_level = next_level;
            next_level = 0;
            printf("\n\n");
            cur_height++;
        }
    }
    printf("---------------------------------------------------------------\n");
}

int main(int argc, char *argv[])
{
#define N(x) treenode_create(x)
    treenode *root = bst_create(10);
    print_tree_visually(root);
}
