#include "ds.h"

void remove_dup(lnode *list)
{
    if (!list)
        return;

    if (!list->next)
        return;

    ht *h = ht_create();

    lnode *prev = list, *cur = list->next;
    ht_insert(h, prev->val, 1);

    while (cur) {
        if (ht_get(h, cur->val)) {
            prev->next = cur->next;
            free(cur);
            cur = prev->next;
        } else {
            ht_insert(h, cur->val, 1);
            prev = cur;
            cur = cur->next;
        }
    }
    ht_release(&h);
}

int main(int argc, char *argv[])
{
    lnode *list = list_create(10);
    list_print(list);
    remove_dup(list);
    list_print(list);
}
