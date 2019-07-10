#include "ds.h"

lnode *two_list_add(lnode *list1, lnode *list2)
{
    if (!list1 || !list2)
        return NULL;

    stack *s1 = stack_create();
    stack *s2 = stack_create();

#define STACK_PUSH(s, x) stack_push(s, (long)x)
#define STACK_POP(s) ((lnode *)stack_pop(s))

    for (lnode *cur = list1; cur; cur = cur->next)
        STACK_PUSH(s1, cur);

    for (lnode *cur = list2; cur; cur = cur->next)
        STACK_PUSH(s2, cur);

    lnode *new = NULL;
    int carry = 0;
    while (carry || (!stack_empty(s1) && !stack_empty(s2))) {
        lnode *n1 = STACK_POP(s1);
        lnode *n2 = STACK_POP(s2);
        long v1 = n1 ? n1->val : 0;
        long v2 = n2 ? n2->val : 0;
        long val = v1 + v2 + carry;
        carry = val / 10;
        val %= 10;
        lnode *n = lnode_create(val);
        n->next = new;
        new = n;
    }

    stack *left = stack_empty(s1) ? s2 : s1;
    while (!stack_empty(left)) {
        lnode *nt = STACK_POP(left);
        lnode *n = lnode_create(nt->val);
        n->next = new;
        new = n;
    }

    stack_release(&s1);
    stack_release(&s2);
    return new;
}

int main(int argc, char *argv[])
{
    int size1 = randWithRange(1, 10);
    int size2 = randWithRange(1, 10);
    int *arr1 = arrayWithRange(size1, 0, 10);
    int *arr2 = arrayWithRange(size2, 0, 10);

    lnode *l1 = list_create_with_arr(arr1, size1);
    lnode *l2 = list_create_with_arr(arr2, size2);
    list_print(l1);
    list_print(l2);
    lnode *l3 = two_list_add(l1, l2);
    list_print(l3);
}
