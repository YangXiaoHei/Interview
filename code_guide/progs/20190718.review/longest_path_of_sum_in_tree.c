#include "ds.h"

long normal_hash(long key)
{
    return key;
}

void __hanson_print(long v)
{
    treenode *n = (treenode *)v;
    printf("%-3ld", n->val);
}

void path_of_sum_in_tree(treenode *root, int k)
{
    if (!root)
        return;

    stack *s = stack_create();
    stack *path = stack_create();
#define PUSH(s, x) stack_push(s, (long)(x))
#define POP(s) ((treenode *)stack_pop(s))
#define PEEK(s) ((treenode *)stack_peek(s))
#define POP_BOTTOM(s) ((treenode *)stack_pop_bottom(s))

    ht *h = ht_create(normal_hash);
    ht_insert(h, 0, -1);
    long sum = 0;
    int len = 0;
    int level = 0;

    treenode *cur1 = root, *cur2 = NULL;
    while (cur1) {
        cur2 = cur1->left;
        if (cur2) {
            while (cur2->right && cur2->right != cur1)
                cur2 = cur2->right;

            if (!cur2->right) {
                PUSH(s, cur1);
                printf("%-3ld push to s level=%d\n", cur1->val, level);
                sum += cur1->val;

                if (!ht_contain(h, sum))
                    ht_insert(h, sum, level);

                if (ht_contain(h, sum - k)) {
                    int l = ht_get(h, sum - k); 
                    if (level - l > len) {
                        len = level - l;
                        stack_copy(path, s);
                        printf("1 stack copy\n");
                    }
                }
                level++;

                cur2->right = cur1;
                cur1 = cur1->left;
                continue;
            }

            cur2->right = NULL;
            while (!stack_empty(s) && PEEK(s) != cur1) {
                level--;
                treenode *n = POP(s);
                sum -= n->val;
                printf("%-3ld pop from s\n", n->val);
            }
        } else {
            PUSH(s, cur1);
            printf("%-3ld push to s level=%d\n", cur1->val, level);
            sum += cur1->val;

            if (!ht_contain(h, sum))
                ht_insert(h, sum, level);

            if (ht_contain(h, sum - k)) {
                int l = ht_get(h, sum - k); 
                if (level - l > len) {
                    len = level - l;
                    stack_copy(path, s);
                    printf("2 stack copy\n");
                }
            }
            level++;
        }
        cur1 = cur1->right;
    }

    while (stack_size(path) > len) 
        POP_BOTTOM(path);
    stack_print_funptr(path, __hanson_print);
    stack_release(&s);
    stack_release(&path);
}

int main(int argc, char *argv[])
{
    int size = 10;
    int *arr = arrayNoDupWithRange(size, -10, 10);
    treenode *root = bst_create_with_arr(arr, size);
/* #define N(x) treenode_create(x) */
    /* treenode *root = N(-3); */
    /* root->left = N(3); */
    /* root->right = N(-9); */
    /* root->left->left = N(1); */
    /* root->left->right = N(0); */
    /* root->left->right->left = N(1); */
    /* root->left->right->right = N(6); */
    /* root->right->left = N(2); */
    /* root->right->right = N(1); */
    tree_draw(root);
    int k = randWithRange(1, 10);
    printf("k = %d\n", k);
    path_of_sum_in_tree(root, k);
}
