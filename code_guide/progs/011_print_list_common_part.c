#include "ds.h"

lnode *gen_sorted_list(int size)
{
    int *arr = arrayWithRange(size, 1, 30);
    sort(arr, size);
    return list_create_with_arr(arr, size);
}

void print_list_common_part(lnode *list1, lnode *list2)
{
    lnode *l1 = list1;
    lnode *l2 = list2;

    while (l1 && l2) {
        if (l1->val == l2->val) {
            printf("%-3ld", l1->val);
            l1 = l1->next;
            l2 = l2->next;
            continue;
        } 

        if (l1->val < l2->val)
            l1 = l1->next;
        else
            l2 = l2->next;
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    lnode *list1 = gen_sorted_list(10);
    lnode *list2 = gen_sorted_list(10);

    list_print(list1);
    list_print(list2);

    print_list_common_part(list1, list2);
}
