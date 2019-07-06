#include "ds.h"

lnode *get_kth_node(lnode *list, int k, int *headprev)
{
    lnode *fast = list;
    while (fast && k)
        fast = fast->next, k--;

    if (!fast && k >= 1) {
        *headprev = k == 1;
        return NULL;
    }

    lnode *slow = list;
    while (fast)
        fast = fast->next, slow = slow->next;
    return slow;
}

void delete_kth_node(lnode **list, int k)
{
    if (!list || !*list)
        return;
    int headprev = 0;
    lnode *kprev = get_kth_node(*list, k + 1, &headprev); 
    if (!kprev) {
        if (headprev) {
            lnode *tmp = *list;
            *list = (*list)->next;
            free(tmp);
        }
        return;
    }
    lnode *tmp = kprev->next;
    kprev->next = kprev->next->next;
    free(tmp);
}

int main(int argc, char *argv[])
{
    int arr[] = { 1, 2, 3, 4, 5 };
    lnode *list = list_create_with_arr(arr, 5);
    list_print(list);
    int k = randWithRange(1, 6);
    printf("delete %d th node\n", k);
    delete_kth_node(&list, k);
    list_print(list);
}
