#include "ds.h"

int joseph(lnode *list, int k)
{
    if (!list || k <= 0)
        return -1;

    int m = k;
    while (list->next != list) {
        m = k;
        while (--m)
            list = list->next;

        lnode *kill = list->next;
        list->val = kill->val;
        list->next = kill->next;
        free(kill);
    }
    return list->val;
}

int main(int argc, char *argv[])
{
    lnode *list = list_circle_create(7);
    list_print(list);
    printf("%d\n", joseph(list, 3));
}
