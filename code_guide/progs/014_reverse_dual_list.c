#include "ds.h"

void reverse_dual_list(dlnode **listptr)
{
    if (!listptr || !*listptr)
        return;

    dlnode *head = *listptr, *prev = NULL, *next = NULL;
    while (head) {
        next = head->next;
        head->next = prev;
        head->prev = next;
        prev = head;
        head = next;
    }
    *listptr = prev;
}

int main(int argc, char *argv[])
{
    dlnode *list = dlist_create(10);
    dlist_print_front(list);
    dlist_print_back(list);
    printf("-----\n");
    reverse_dual_list(&list);
    dlist_print_front(list);
    dlist_print_back(list);
}
