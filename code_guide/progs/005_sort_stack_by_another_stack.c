#include "ds.h"

void sort_by_stack(stack *s)
{
    if (!s)
        return;

    if (stack_empty(s))
        return;

    stack *help = stack_create();
    while (!stack_empty(s)) {
        long top = stack_pop(s);
        while (!stack_empty(help) && stack_peek(help) > top)
            stack_push(s, stack_pop(help));
        stack_push(help, top);
    }

    while (!stack_empty(help))
        stack_push(s, stack_pop(help));
    stack_release(&help);
}

int main(int argc, char *argv[])
{
    stack *s = stack_create();
    int size = randWithRange(5, 10);
    int *arr = arrayWithRange(size, 1, 20);
    for (int i = 0; i < size; i++)
        stack_push(s, arr[i]);

    stack_print(s);
    sort_by_stack(s);
    stack_print(s);
}
