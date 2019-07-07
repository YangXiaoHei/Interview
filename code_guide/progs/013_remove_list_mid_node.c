#include "ds.h"

void remove_mid_node(lnode **listptr)
{
    if (!listptr || !*listptr)
        return;

    lnode *list = *listptr;
    if (!list->next) {
        free(list);
        *listptr = NULL;
        return;
    }

    lnode *slow = list, *fast = list->next->next;
    if (!fast) {
        *listptr = slow->next;
        free(slow);
        return;
    }

    lnode *slowprev = NULL;
    while (1) {
        slowprev = slow;
        slow = slow->next;
        if (!(fast = fast->next))
            break;
        if (!(fast = fast->next))
            break;
    }

    slowprev->next = slowprev->next->next;
    free(slow);
}

int main(int argc, char *argv[])
{
    int size = randWithRange(1, 6);
    lnode *list = list_create(size);
    list_print(list);
    remove_mid_node(&list);
    list_print(list);
}
