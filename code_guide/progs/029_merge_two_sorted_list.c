#include "ds.h"

lnode *gen_sorted_list(int size)
{
    int *arr = arrayWithRange(size, 0, size * 2);
    sort(arr, size);
    lnode *list = list_create_with_arr(arr, size);
    free(arr);
    return list;
}

lnode *merge_two_list(lnode *list1, lnode *list2)
{
    if (!list1 || !list2)
        return NULL;

    lnode *cur1 = list1;
    lnode *cur2 = list2;
    lnode *head = NULL, *tail = NULL;
    
    lnode *smaller = NULL;
    while (cur1 || cur2) {
        if (cur1 && cur2) {
            if (cur1->val < cur2->val) {
                smaller = cur1;
                cur1 = cur1->next;
            } else {
                smaller = cur2;
                cur2 = cur2->next;
            }
        } else if (cur1) {
            smaller = cur1;
            cur1 = cur1->next;
        } else if (cur2) {
            smaller = cur2;
            cur2 = cur2->next;
        }

        if (!head) {
            head = tail = smaller;
        } else {
            tail->next = smaller;
            tail = smaller;
        }
    }
    return head;
}

int main(int argc, char *argv[])
{
    lnode *list1 = gen_sorted_list(10);
    lnode *list2 = gen_sorted_list(5);
    list_print(list1);
    list_print(list2);
    lnode *list = merge_two_list(list1, list2);
    list_print(list);
}
