#include "ds.h"

int list_has_loop(lnode *list)
{
    if (!list)
        return 0;

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
    return fast != NULL;
}

int main(int argc, char *argv[])
{
    lnode *list = NULL;
    if (randWithRange(0, 2))
        list = list_loop_create(10);
    else 
        list = list_create(10);
    list_print_with_size(list, 15);
    printf("has loop: %d\n", list_has_loop(list));
}
