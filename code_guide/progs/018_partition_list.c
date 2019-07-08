#include "ds.h"

lnode *partition_list(lnode *list, int pivot)
{
    if (!list || !list->next)
        return NULL;

    lnode *bigh, *bigt, *smallh, *smallt, *equalh, *equalt;
    bigh = bigt = smallh = smallt = equalh = equalt = NULL;

    lnode *cur = list, *next = list;
    while (cur) {
        next = cur->next;
        cur->next = NULL;
        if (cur->val > pivot) {
            if (!bigh) {
                bigh = bigt = cur;
            } else {
                bigt->next = cur;
                bigt = cur;
            }
        } else if (cur->val < pivot) {
            if (!smallh) {
                smallh = smallt = cur;
            } else {
                smallt->next = cur;
                smallt = cur;
            }
        } else {
            if (!equalh) {
                equalh = equalt = cur;
            } else {
                equalt->next = cur;
                equalt = cur;
            }
        }
        cur = next;
    }

    printf("small: ");
    list_print(smallh);
    printf("equal: ");
    list_print(equalh);
    printf("big: ");
    list_print(bigh);

    if (smallh) {
        if (!equalh)
            smallt->next = bigh;
        else
            smallt->next = equalh;
    }

    if (equalh) 
        equalt->next = bigh;

    return smallh ? smallh : (equalh ? equalh : bigh);
}

int main(int argc, char *argv[])
{
    lnode *list = list_create(10);
    list_print(list);
    int pivot = randWithRange(1, 20);
    printf("pivot = %d\n", pivot);
    list = partition_list(list, pivot);
    list_print(list);
}
