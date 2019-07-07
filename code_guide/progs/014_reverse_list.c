#include "ds.h"

void reverse_list(lnode **listptr)
{
    if (!listptr || !*listptr)
        return;

    lnode *head = *listptr, *prev = NULL, *next = NULL;
    while (head) {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    *listptr = prev;
}

int main(int argc, char *argv[])
{
    lnode *list = list_create(10);
    list_print(list);
    reverse_list(&list);
    list_print(list);
}
