#include "ds.h"

void remove_node_of_value(lnode **listptr, int key)
{
    if (!listptr || !*listptr)
        return;

    lnode *list = *listptr;

    lnode *prev = list, *cur = list->next;
    while (cur) {
        if (cur->val == key) {
            prev->next = cur->next;
            free(cur);
            cur = prev->next;
        } else {
            prev = cur;
            cur = cur->next;
        }
    }

    if (list->val == key) {
        *listptr = (*listptr)->next;
        free(list);
    }
}

int main(int argc, char *argv[])
{
    {
        int arr[] = { 1, 2, 2, 2, 3, 4, 5, 9, 1, 1, 1 };
        int size = sizeof(arr) / sizeof(arr[0]);
        lnode *list = list_create_with_arr(arr, size);
        list_print(list);
        remove_node_of_value(&list, 1);
        list_print(list);
    }
    {
        int arr[] = { 1, 1, 1, 1, 1, 1, 1, 1 };
        int size = sizeof(arr) / sizeof(arr[0]);
        lnode *list = list_create_with_arr(arr, size);
        list_print(list);
        remove_node_of_value(&list, 1);
        list_print(list);
    }
    {
        int arr[] = { 1, 2, 1, 2, 1, 2, 1, 2, 1, 4, 1, 2, 2, 2 };
        int size = sizeof(arr) / sizeof(arr[0]);
        lnode *list = list_create_with_arr(arr, size);
        list_print(list);
        remove_node_of_value(&list, 1);
        list_print(list);
    }
    {
        int arr[] = { 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1 };
        int size = sizeof(arr) / sizeof(arr[0]);
        lnode *list = list_create_with_arr(arr, size);
        list_print(list);
        remove_node_of_value(&list, 1);
        list_print(list);
    }
    {
        int arr[] ={ 1 };
        int size = sizeof(arr) / sizeof(arr[0]);
        lnode *list = list_create_with_arr(arr, size);
        list_print(list);
        remove_node_of_value(&list, 1);
        list_print(list);
    }
}
