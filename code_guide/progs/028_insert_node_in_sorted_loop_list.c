#include "ds.h"

void list_insert_in_sorted_loop(lnode **list, long val)
{
    if (!list)
        return;

    lnode *n = lnode_create(val);
    if (!*list) {
        *list = n;
        n->next = n;
        return;
    }

    lnode *cur = *list;
    while (cur->next != *list && !(val >= cur->val && val <= cur->next->val)) 
        cur = cur->next;

    n->next = cur->next;
    cur->next = n;

    lnode *minnode = *list;
    cur = *list;
    do {
        if (cur->val < minnode->val) 
            minnode = cur;
        cur = cur->next;
    } while (cur != *list);
    *list = minnode;
}

int main(int argc, char *argv[])
{
    int size = 10;
    int *arr = arrayWithRange(size, 0, 10);
    printArray(arr, size);
    lnode *list = NULL;
    for (int i = 0; i < size; i++)
        list_insert_in_sorted_loop(&list, arr[i]);
    list_print_with_size(list, 15);
}
