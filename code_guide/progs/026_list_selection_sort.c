#include "ds.h"

void find_min(lnode *list, lnode **prevptr, lnode **minptr)
{
    lnode *minprev = NULL, *minnode = list;
    lnode *prev = NULL, *cur = list;
    while (cur) {
        if (cur->val < minnode->val) {
            minprev = prev;
            minnode = cur; 
        }
        prev = cur;
        cur = cur->next;
    }
    *prevptr = minprev;
    *minptr = minnode;
}

void selection_sort(lnode **listptr)
{
    if (!listptr || !*listptr)
        return;

    lnode *list = *listptr;
    if (!list->next)
        return;

    lnode *head = NULL, *tail = NULL;
    lnode *prev = NULL, *min = NULL;
    while (list) {
        find_min(list, &prev, &min);
        if (prev) 
            prev->next = min->next;
        else
            list = list->next;

        if (!head) {
            head = tail = min;
        } else {
            tail->next = min;
            tail = min;
        }
    }
    *listptr = head;
}

int main(int argc, char *argv[])
{
    lnode *list = list_create(10);
    list_print(list);
    selection_sort(&list);
    list_print(list);
}
