#include "ds.h"

long remove_stack_bottom(stack *s)
{
    long val = stack_pop(s);
    if (stack_empty(s))
        return val;

    int bottom = remove_stack_bottom(s);
    stack_push(s, val);
    return bottom;
}

void reverse_stack(stack *s)
{
    if (!s)
        return;

    if (stack_empty(s))
        return;

    long bottom = remove_stack_bottom(s);
    reverse_stack(s);
    stack_push(s, bottom);
}

int main(int argc, char *argv[])
{
    stack *s = stack_create();
    for (int i = 0; i < 10; i++)
        stack_push(s, i);

    stack_print(s);
    reverse_stack(s);
    stack_print(s);
}
