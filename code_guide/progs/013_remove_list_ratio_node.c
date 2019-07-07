#include "ds.h"

void remove_ratio_node(lnode **listptr, int a, int b)
{
    if (!listptr || !*listptr || a <= 0 || b <= 0)
        return;

    lnode *list = *listptr;

    int n = 0;
    for (lnode *cur = list; cur; cur = cur->next)
        n++;
    int k = ceil(a * 1.0 * n / b);
    if (k == 1) {
        free(list);
        *listptr = (*listptr)->next;
        return;
    }
    lnode *prev = NULL, *cur = list;
    while (cur && k > 1) {
        prev = cur;
        cur = cur->next;
        k--;
    }
    if (!cur)
        return;

    prev->next = prev->next->next;
    free(cur);
}

int main(int argc, char *argv[])
{
    int a, b;
    lnode *list = list_create(5);
    list_print(list);
    printf("input a and b\n");
    scanf("%d%d", &a, &b);
    remove_ratio_node(&list, a, b);
    list_print(list);
}
