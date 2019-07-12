#include "ds.h"

long normal_hash(long key)
{
    return key;
}

void remove_dup(lnode **listptr)
{
    if (!listptr || !*listptr)
        return;

    lnode *list = *listptr;

    lnode *sentinel = lnode_create(10);
    sentinel->next = list;

    ht *h = ht_create(normal_hash);

    lnode *prev = sentinel, *cur = sentinel->next;
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
    *listptr = sentinel->next;
    free(sentinel);
    ht_release(&h);
}

int main(int argc, char *argv[])
{
    lnode *list = list_create(10);
    list_print(list);
    remove_dup(&list);
    list_print(list);
}
