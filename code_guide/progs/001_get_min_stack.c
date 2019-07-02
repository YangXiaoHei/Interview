#include "ds.h"

typedef struct mstack {
    stack *min;
    stack *normal;
} mstack;

mstack *mstack_create(void)
{
    mstack *s = malloc(sizeof(mstack));
    if (!s) exit(1);
    s->min = stack_create();
    s->normal = stack_create();
    return s;
}

int mstack_empty(mstack *s)
{
    return stack_empty(s->normal) && stack_empty(s->min);
}

int mstack_pop(mstack *s)
{
    if (mstack_empty(s))
        return -1;

    stack_pop(s->min);
    return stack_pop(s->normal);
}

int mstack_min(mstack *s)
{
    if (mstack_empty(s))
       return -1; 

    return stack_peek(s->min);
}

void mstack_push(mstack *s, int val)
{
    if (mstack_empty(s)) {
        stack_push(s->normal, val);
        stack_push(s->min, val);
        return;
    }

    stack_push(s->normal, val);

    if (val < stack_peek(s->min))
        stack_push(s->min, val);
    else
        stack_push(s->min, stack_peek(s->min));
}

void mstack_print(mstack *s)
{
    stack_print(s->normal);
    stack_print(s->min);
}

void mstack_test(void)
{
    mstack *m = mstack_create();
    int size = 10;
    int *arr = arrayWithRange(size, 1, 30);
    printArray(arr, size);
    for (int i = 0; i < size; i++)
        mstack_push(m, arr[i]);

    mstack_print(m);

    while (!mstack_empty(m)) {
        printf("pop %-3d ", mstack_pop(m));
        printf("min value = %-3d\n", mstack_min(m));
    }
}

int main(int argc, char *argv[])
{
    mstack_test();
}
