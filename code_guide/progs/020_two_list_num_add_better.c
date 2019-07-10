#include "ds.h"

lnode *reverse_list(lnode *list)
{
    if (!list)
        return NULL;

    lnode *head = list, *prev = NULL, *next = NULL;
    while (head) {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

lnode *two_list_add(lnode *list1, lnode *list2)
{
    if (!list1 || !list2)
        return NULL;
    
    list1 = reverse_list(list1);
    list2 = reverse_list(list2);
    
    lnode *newhead = NULL;
    lnode *newtail = NULL;
    int carry = 0;
    lnode *n1 = NULL, *n2 = NULL;
    for (n1 = list1, n2 = list2; carry || (n1 && n2); n1 = n1 ? n1->next : NULL, 
                                                      n2 = n2 ? n2->next : NULL) {
        long v1 = n1 ? n1->val : 0;
        long v2 = n2 ? n2->val : 0;
        long val = v1 + v2 + carry;
        carry = val / 10;
        val %= 10;
        lnode *n = lnode_create(val);
        if (newtail) {
            newtail->next = n;
            newtail = n;
        } else {
            newtail = newhead = n;
        }
    }

    lnode *left = n1 ? n1 : n2;
    for (lnode *nl = left; nl; nl = nl->next) {
        lnode *n = lnode_create(nl->val);
        newtail->next = n;
        newtail = n;
    }

    reverse_list(list1);
    reverse_list(list2);
    return reverse_list(newhead);
}

int main(int argc, char *argv[])
{
    int size1 = randWithRange(1, 10);
    int size2 = randWithRange(1, 10);
    int *arr1 = arrayWithRange(size1, 0, 10);
    int *arr2 = arrayWithRange(size2, 0, 10);

    lnode *l1 = list_create_with_arr(arr1, size1);
    lnode *l2 = list_create_with_arr(arr2, size2);
    list_print(l1);
    list_print(l2);
    lnode *l3 = two_list_add(l1, l2);
    list_print(l3);
}
