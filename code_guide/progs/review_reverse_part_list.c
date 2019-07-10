#include "ds.h"

lnode *get_kth_node(lnode *list, int k)
{
    if (!list || k <= 0)
        return NULL;

    while (list && k > 1)
        list = list->next, k--;
    return list;
}

lnode *reverse_part_list(lnode *list, int f, int t)
{
    if (!list || f <= 0 || t <= 0 || f >= t)
        return list;
    lnode *fromprev = get_kth_node(list, f - 1); 
    lnode *from = get_kth_node(list, f); 
    lnode *to = get_kth_node(list, t); 
    if (!from || !to)
        return list;
    lnode *head = from, *prev = to->next, *next = NULL;
    lnode *succ = to->next;
    while (head != succ) {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    if (fromprev)
        fromprev->next = prev;
    return fromprev ? list : prev;
}

int main(int argc, char *argv[])
{
    int from, to;
    printf("input from, to\n");
    lnode *list = list_create(5);
    list_print(list);
    while (scanf("%d%d", &from, &to) > 0) {
        list = reverse_part_list(list, from, to);
        list_print(list);
    }
}
