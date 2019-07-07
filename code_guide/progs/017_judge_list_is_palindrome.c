#include "ds.h"

lnode *gen_palindrome(int size)
{
    int left = ceil(size / 2.0);
    int right = size - left;
    int *arr = arrayWithRange(left, 1, 10);
    int *copy = copyArray(arr, right);
    int i = 0, j = right - 1;
    while (i < j) {
        swap(copy + i, copy + j);
        i++; j--;
    }
    int *total = malloc(sizeof(int) * size);
    memcpy(total, arr, sizeof(int) * left);
    memcpy(total + left, copy, sizeof(int) * right);
    free(arr);
    free(copy);

    lnode *list = list_create_with_arr(total, size);
    free(total);
    return list;
}

int is_list_palindrome(lnode *list)
{
    if (!list)
        return 0;

    if (!list->next)
        return 1;

#define STACK_PUSH(s, x) stack_push(s, (long)x)
#define STACK_POP(s) ((lnode *)stack_pop(s))
    stack *s = stack_create(); 
    lnode *fast = list, *slow = list;
    while (fast->next && fast->next->next)
        slow = slow->next, fast = fast->next->next;

    slow = slow->next;
    while (slow) {
        STACK_PUSH(s, slow);
        slow = slow->next;
    }

    lnode *head = list;
    while (!stack_empty(s)) {
        if (head->val != STACK_POP(s)->val)
            return 0;
        head = head->next;
    }
    stack_release(&s);
    return 1;
}

int main(int argc, char *argv[])
{
    int size = randWithRange(1, 10);
    lnode *list = NULL;
    if (randWithRange(0, 2))
        list = gen_palindrome(size);
    else
        list = list_create(size);
    list_print(list);
    printf("is palindrome : %d\n", is_list_palindrome(list));
}
