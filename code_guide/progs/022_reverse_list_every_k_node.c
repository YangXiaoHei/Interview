#include "ds.h"

lnode *reverse_part_list(lnode *fromprev, lnode *from, lnode *to, lnode *tonext)
{
    lnode *head = from, *prev = tonext, *next = NULL;
    while (head != tonext) {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    if (fromprev)
        fromprev->next = prev;
    return fromprev ? fromprev : prev;
}

void reverse_list_every_k_node(lnode **listptr, int k)
{
    if (!listptr || !*listptr || k <= 1)
        return;

    int n = 0;
    lnode *list = *listptr;
    lnode *cur = list;
    lnode *to = NULL, *tonext = NULL;
    lnode *fromprev = NULL, *from = list;
    lnode *newhead = NULL;
    while (cur) {
        to = cur;
        tonext = cur->next;
        if (++n == k) {
            newhead = reverse_part_list(fromprev, from, to, tonext);
            if (!fromprev) 
                *listptr = newhead;
            fromprev = from;
            from = tonext;
            n = 0;
        }
        cur = tonext;
#ifdef DEBUG
        printf("fromprev = %-3ld from = %-3ld to = %-3ld tonext = %-3ld\n", 
                fromprev ? fromprev->val : -1, from->val, to->val, tonext ? tonext->val : -1);
#endif
    } 
}

int main(int argc, char *argv[])
{
    int size = randWithRange(5, 15);
    int k = randWithRange(2, 9);
    printf("size = %d, k = %d\n", size, k);
    lnode *list = list_create(size);
    list_print(list);
    reverse_list_every_k_node(&list, k);
    list_print(list);
}
