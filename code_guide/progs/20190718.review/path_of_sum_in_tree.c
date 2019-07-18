#include "ds.h"

#define PUSH(s, x) stack_push(s, (long)(x))
#define POP(s) ((treenode *)stack_pop(s))
#define PEEK(s) ((treenode *)stack_peek(s))
#define POP_BOTTOM(s) ((treenode *)stack_pop_bottom(s))

void __hanson_print(long v)
{
    treenode *t = (treenode *)v;
    printf("%-3ld", t->val);
}

void path_of_sum_in_tree(treenode *root, ht *h, int k, int *len, int level, int sum, stack *s, stack *path)
{
    if (!root)
        return;

    PUSH(s, root);
    sum += root->val;
    if (!ht_contain(h, sum)) 
        ht_insert(h, sum, level);

    if (ht_contain(h, sum - k)) {
        int l = ht_get(h, sum - k);
        if (level - l > *len) {
            *len = level - l;
            stack_copy(path, s);
        }
    }

    path_of_sum_in_tree(root->left, h, k, len, level + 1, sum, s, path);
    path_of_sum_in_tree(root->right, h, k, len, level + 1, sum, s, path);

    POP(s); 
}

long normal_hash(long key)
{
    return key;
}

void find_path(treenode *root, int k)
{
    ht *h = ht_create(normal_hash);
    stack *s = stack_create();
    stack *path = stack_create();
    ht_insert(h, 0, -1);

    int len = 0;
    path_of_sum_in_tree(root, h, k, &len, 0, 0, s, path);
    while (stack_size(path) > len)
        POP_BOTTOM(path);
    stack_print_funptr(path, __hanson_print);
}

/*
 * void path_of_sum_in_tree(treenode *root)
 * {
 *     if (!root)
 *         return;
 * 
 *     stack *s = stack_create();
 *     stack *s1 = stack_create();
 *     stack *path = stack_create();
 * 
 *     int sum = 0;
 *     int level = 0;
 * 
 *     PUSH(s, root);
 *     while (!stack_empty(s)) {
 *         root = POP(s);
 *         while (root) {
 *             PUSH(s1, root);
 *             sum += root->val;
 * 
 *             if (!ht_contain(h, sum))
 *                 ht_insert(h, sum, level);
 * 
 *             if (ht_contain(h, sum - k)) {
 *                 int l = ht_get(h, sum - k);
 *                 if (level - l > len) {
 *                     len = level - l;
 *                     stack_copy(path, s1);
 *                 }
 *             }
 *             root = root->left;
 *             level++;
 *         }
 * 
 *         while (PEEK(s1) != )
 *         level--;
 * 
 *     }
 * 
 * 
 *     stack_release(&s);
 *     stack_release(&s1);
 *     stack_release(&path);
 * }
 */

int main(int argc, char *argv[])
{
    /*
     * #define N(x) treenode_create(x)
     * treenode *root = N(-3);
     * root->left = N(3);
     * root->right = N(-9);
     * root->left->left = N(1);
     * root->left->right = N(0);
     * root->left->right->left = N(1);
     * root->left->right->right = N(6);
     * root->right->left = N(2);
     * root->right->right = N(1);
     */
    int size = 10;
    int *arr = arrayNoDupWithRange(size, -10, 10);
    treenode *root = bst_create_with_arr(arr, size);
    tree_draw(root);
    int k = randWithRange(1, 15);
    printf("k = %d\n", k);
    find_path(root, k);
}
