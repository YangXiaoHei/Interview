#include "ds.h"

treenode *get_kth_node(treenode *root, int k)
{
#define PUSH(s, x) stack_push(s, (long)(x))
#define POP(s) ((treenode *)stack_pop(s))

    if (!root || k < 0)
        return NULL;

    treenode *target = NULL;
    stack *s = stack_create();
    while (!stack_empty(s) || root) {
        if (root) {
            PUSH(s, root);
            root = root->left;
        } else {
            root = POP(s);
            if (k-- <= 0) {
                target = root;
                break;
            }
            root = root->right;
        }
    }
    stack_release(&s);
    return target;
}

void gen_two_treenode(treenode *root, int size, treenode **n1, treenode **n2)
{
    int k = randWithRange(0, size);
    int m = randWithRange(0, size);
    *n1 = get_kth_node(root, k);
    *n2 = get_kth_node(root, m);
}

#define HT_INSERT(h, k, v) ht_insert(h, (long)(k), (long)(v))
#define HT_CONTAIN(h, k) ht_contain(h, (long)(k))
#define HT_GET(h, k) ((treenode *)ht_get(h, (long)k))

void set_map(treenode *root, ht *h)
{
    if (!root)
        return;

    if (root->left)
        HT_INSERT(h, root->left, root);

    if (root->right)
        HT_INSERT(h, root->right, root);

    set_map(root->left, h);
    set_map(root->right, h);
}

void print_fun(long key, long value)
{
    treenode *tn = (treenode *)key;
    treenode *tn1 = (treenode *)value;
    printf("{ ");
    if (tn)
        printf("%ld ", tn->val);
    else
        printf("null ");

    if (tn1)
        printf("%ld ", tn1->val);
    else
        printf("null ");
    printf("}");
}

void print_fun2(long key, long value)
{
    treenode *tn = (treenode *)key;
    printf("{%ld %ld}", tn->val, value);
}

treenode* lowest_common_parent(treenode *root, treenode *n1, treenode *n2)
{
    if (!root || !n1 || !n2)
        return NULL;
    ht *h = ht_create();
    HT_INSERT(h, root, NULL);
    set_map(root, h); 

    ht_print_funptr(h, print_fun);

    ht *path = ht_create();
    while (HT_CONTAIN(h, n1)) {
        HT_INSERT(path, n1, 0);
        n1 = HT_GET(h, n1);
    }
    ht_print_funptr(path, print_fun2);

    while (!HT_CONTAIN(path, n2))
        n2 = HT_GET(h, n2);

    ht_release(&h);
    ht_release(&path);

    return n2;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(5);        
    tree_draw(root);
    treenode *n1 = NULL, *n2 = NULL;
    gen_two_treenode(root, 5, &n1, &n2);
    printf("n1 = %ld, n2 = %ld\n", n1->val, n2->val);
    treenode *comm = lowest_common_parent(root, n1, n2);
    if (comm) 
        printf("common %ld\n", comm->val);
    else
        printf("common not exist!\n");
}
