#include "ds.h"

void remove_mid_node(lnode **listptr)
{
    if (!listptr || !*listptr)
        return;

    lnode *list = *listptr;
    lnode *mid = list, *fast = list;
    lnode *midprev = NULL;
    while (fast->next && fast->next->next) {
        midprev = mid;
        mid = mid->next;
        fast = fast->next->next;
    }

    if (!midprev) {
        *listptr = (*listptr)->next;
        free(list);
        return;
    }

    midprev->next = midprev->next->next;
    free(mid);
}

int main(int argc, char *argv[])
{
    int size = randWithRange(1, 5);
    lnode *list = list_create(size);
    list_print(list);
    remove_mid_node(&list);
    list_print(list);
}
