#include "ds.h"

void reverse_part_list(lnode **listptr, int f, int t)
{
    if (!listptr || !*listptr || f <= 0 || t <= 0 || f >= t)
       return;

    lnode *from = *listptr, *to = from, *fromprev = NULL;
    while (from && f > 1) {
        fromprev = from;
        from = from->next;
        f--;
    }

    if (!from)
        return;

    while (to && t > 1) 
        to = to->next, t--;

    if (!to)
        return;

    lnode *succ = to->next;
    lnode *prev = succ, *head = from, *next = NULL;
    while (head != succ) {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    if (fromprev)
        fromprev->next = prev;
    else
        *listptr = prev;
}

int main(int argc, char *argv[])
{
    int from, to;
    lnode *list = list_create(5);
    list_print(list);
    printf("input from, to\n");
    scanf("%d%d", &from, &to);
    reverse_part_list(&list, from, to);
    list_print(list);
}
