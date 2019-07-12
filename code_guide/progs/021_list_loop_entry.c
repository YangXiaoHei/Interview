#include "ds.h"

lnode *list_loop_entry(lnode *list)
{
    if (!list)
        return NULL;

    lnode *fast = list;
    lnode *slow = list;
    while (1) {
        if (!(fast = fast->next))
            break;
        if (!(fast = fast->next))
            break;
        slow = slow->next;
        if (slow == fast)
            break;
    }
    if (!fast)
        return NULL;

    int n = 1;
    while (slow->next != fast)
        slow = slow->next, n++;
    
    fast = list;
    while (n--)
        fast = fast->next;

    slow = list;
    while (slow != fast) 
        slow = slow->next, fast = fast->next;

    return slow;
}

int main(int argc, char *argv[])
{
    lnode *list = NULL;
    if (randWithRange(0, 2))
        list = list_loop_create(10);
    else
        list = list_create(10);
    list_print_with_size(list, 15);
    lnode *entry = list_loop_entry(list);
    if (entry)
        printf("entry is %-3ld\n", entry->val);
    else
        printf("no loop\n");
}
