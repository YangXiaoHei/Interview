#include "ds.h"

void gen_intersect_list(lnode **list1, lnode **list2)
{
    if (!list1 || !list2)
        return;
    *list1 = *list2 = NULL;
    int r1 = randWithRange(1, 10);
    int r2 = randWithRange(1, 10);
    if (randWithRange(0, 2)) {
        lnode *l1 = list_create(r1);
        lnode *l2 = list_create(r2);
        int r = randWithRange(0, r1);
        lnode *intersect = l1;
        while (r--)
            intersect = intersect->next;
        lnode *l2tail = l2;
        while (l2tail->next)
            l2tail = l2tail->next;
        l2tail->next = intersect;
        *list1 = l1;
        *list2 = l2;
    } else {
        *list1 = list_create(r1);
        *list2 = list_create(r2);
    }
}

int list_intersect(lnode *l1, lnode *l2)
{
    int n1 = 0;
    lnode *cur1 = NULL;
    for (cur1 = l1; cur1; cur1 = cur1->next)
        n1++;

    int n2 = 0;
    lnode *cur2 = NULL;
    for (lnode *cur2 = l2; cur2; cur2 = cur2->next)
        n2++;

    if (cur1 != cur2)
        return 0;

    int diff = n1 - n2;
    diff = diff < 0 ? -diff : diff;

    lnode *longer = n1 > n2 ? l1 : l2;
    lnode *shorter = longer == l1 ? l2 : l1;
    while (diff--)
        longer = longer->next;

    while (longer && shorter) {
        if (longer == shorter)
            break;
        longer = longer->next;
        shorter = shorter->next;
    }

    if (longer && shorter) {
        printf("common part : ");
        for (lnode *cur = longer; cur; cur = cur->next)
            printf("%-3ld", cur->val);
        printf("\n");
    }

    return longer && shorter;
}

int main(int argc, char *argv[])
{
    lnode *l1 = NULL, *l2 = NULL;
    gen_intersect_list(&l1, &l2);
    list_print(l1);
    list_print(l2);
    printf("is intersect : %d\n", list_intersect(l1, l2));
}
