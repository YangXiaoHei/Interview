#include "ds.h"

#define PUSH(s, x) stack_push(s, (long)x)
#define POP(s) ((treenode *)stack_pop(s))
#define PEEK(s) ((treenode *)stack_peek(s))

void __hanson_print(long val)
{
    treenode *n = (treenode *)val;
    printf("%-3ld", n->val);
}

void get_kth_node(treenode *root, treenode **target, int *k)
{
    if (!root)
        return;

    if (*target)
        return;

    get_kth_node(root->left, target, k);    

    if ((*k)-- == 0) 
        *target = root;

    get_kth_node(root->right, target, k);    
}

void gen_two_treenode(treenode *root, int size, treenode **n1, treenode **n2)
{
    int k = randWithRange(0, size);
    int m = randWithRange(0, size);
    get_kth_node(root, n1, &k);
    get_kth_node(root, n2, &m);
}

void collect_path(treenode *root, treenode *target, stack *s)
{
    if (!root)
        return;

    if (PEEK(s) == target)
        return;

    PUSH(s, root);
    collect_path(root->left, target, s);
    collect_path(root->right, target, s);

    if (PEEK(s) != target)
        POP(s);
}

treenode *lowest_common_parent_in_tree(treenode *root, treenode *n1, treenode *n2)
{
    if (!root || !n1 || !n2)
       return NULL;

    if (n1 == n2)
        return n1;

    stack *s1 = stack_create();
    stack *s2 = stack_create();

    collect_path(root, n1, s1);
    collect_path(root, n2, s2);

    stack *bigger = NULL;
    int diff = 0;
    if (stack_size(s1) > stack_size(s2)) {
        bigger = s1;
        diff = stack_size(s1) - stack_size(s2);
    } else {
        bigger = s2;
        diff = stack_size(s2) - stack_size(s1);
    }

    while (diff-- > 0) 
        POP(bigger);

    while (!stack_empty(s1) && !stack_empty(s2)) {
        if (PEEK(s1) == PEEK(s2))
            break;
        POP(s1);
        POP(s2);
    }
    if (stack_empty(s1) || stack_empty(s2)) {
        printf("what a fuck?!\n");
        return NULL;
    }

    treenode *lowest_common_parent = POP(s1);

    stack_release(&s1);  
    stack_release(&s2);  
    return lowest_common_parent;
}

void helper_fun_test(void)
{
    treenode *root = bst_create(10);
    tree_draw(root);
    treenode *target = NULL;
    int k = randWithRange(0, 10);
    printf("k = %d\n", k);
    get_kth_node(root, &target, &k);
    if (target)
        printf("target = %ld\n", target->val);

    stack *s = stack_create();
    collect_path(root, target, s);
    stack_print_funptr(s, __hanson_print);
}

int main(int argc, char *argv[])
{
    int size = 10;
    treenode *root = bst_create(size);
    tree_draw(root);
    treenode *n1 = NULL, *n2 = NULL;
    gen_two_treenode(root, size, &n1, &n2);
    printf("n1 = %ld n2 = %ld\n", n1->val, n2->val);

    treenode *common_parent = lowest_common_parent_in_tree(root, n1, n2);
    if (common_parent)
        printf("common parent is %-3ld\n", common_parent->val);
}
