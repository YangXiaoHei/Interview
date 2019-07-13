#include "ds.h"

lnode *get_kth_node(lnode *list, int k)
{
    if (!list || k < 0)
        return NULL;

    while (list && k > 0) 
        list = list->next, k--;
    return list;
}

lnode *get_random_node(lnode *list)
{
    int size = 0;
    for (lnode *cur = list; cur; cur = cur->next)
        size++;
    return get_kth_node(list, randWithRange(0, size));
}

void list_remove_node(lnode **list, lnode *target)
{
    if (target->next) {
        target->val = target->next->val;
        lnode *tmp = target->next;
        target->next = target->next->next;
        free(tmp);
    } else {
        lnode *cur = *list;
        while (cur && cur->next != target)
            cur = cur->next;
        
        if (cur) {
            cur->next = target->next;
            free(target);
        } else if (*list == target) {
            *list = (*list)->next;
            free(target);
        } else {
            printf("target not in list!\n");
        }
    }
}

int main(int argc, char *argv[])
{
    int size = randWithRange(1, 5);
    lnode *list = list_create(size);
    list_print(list);
    lnode *n = get_random_node(list);
    printf("remove node %-3ld\n", n->val);
    list_remove_node(&list, n);
    list_print(list);
}
