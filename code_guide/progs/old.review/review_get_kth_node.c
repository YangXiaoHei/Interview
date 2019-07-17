#include "ds.h"

int get_kth_node(lnode *list, int k)
{
    if (!list)
        return -1;
    
    lnode *fast = list;
    while (fast && k > 0)
        fast = fast->next, k--;

    if (k > 0)
        return -1;

    lnode *slow = list;
    while (fast)
        fast = fast->next, slow = slow->next;

    return slow->val;
}

int main(int argc, char *argv[])
{
    lnode *list = list_create(5);
    list_print(list);
    int k = randWithRange(1, 7);
    printf("k = %-3d val = %-3d\n", k, get_kth_node(list, k));    
}
