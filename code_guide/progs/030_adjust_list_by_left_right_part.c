#include "ds.h"

void adjust_list(lnode *list)
{
    if (!list || !list->next || !list->next->next || !list->next->next->next)
        return;

    lnode *mid = list;
    lnode *cur = list->next;
    while (cur->next && cur->next->next) {
        mid = mid->next;
        cur = cur->next->next;
    }

    lnode *ln = list, *rn = mid->next;
    lnode *l = NULL, *r = NULL;
    mid->next = NULL;
    while (ln) {
        l = ln, r = rn;
        ln = ln->next;
        rn = rn->next;

        r->next = l->next;
        l->next = r;
    }
    r->next = rn;
}

int main(int argc, char *argv[])
{
    int size = randWithRange(1, 15);
    lnode *list = list_create(size);
    list_print(list);
    adjust_list(list);
    printf("after adjust\n");
    list_print(list);
}
