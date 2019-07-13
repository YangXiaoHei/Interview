#include "ds.h"

void remove_dup(lnode *list)
{
    if (!list)
        return;

    lnode *prev = NULL, *cur = list, *next = NULL;
    while (cur) {
        prev = cur;
        next = cur->next;
        while (next) {
            if (cur->val == next->val) {
                prev->next = next->next;
                free(next);
                next = prev->next;
            } else {
                prev = next;
                next = next->next;
            }
        }
        cur = cur->next;
    }
}

int main(int argc, char *argv[])
{
    lnode *list = list_create(10);
    list_print(list);
    remove_dup(list);
    list_print(list);
}
