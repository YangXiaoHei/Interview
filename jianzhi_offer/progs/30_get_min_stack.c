#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tool.h"

typedef struct stack {
    int *data;
    int cap;
    int size;
} stack;

stack *stack_create(void)
{
    stack *s = malloc(sizeof(stack));
    if (!s) exit(1);
    s->data = malloc(10 * sizeof(int));
    if (!s->data) exit(1);
    s->cap = 10;
    s->size = 0;
    return s;
}

void stack_resize(stack *s, int newsize)
{
    int *newm = malloc(newsize * sizeof(int));
    if (!newm) exit(1);
    memcpy(newm, s->data, s->size * sizeof(int)); 
    free(s->data);
    s->data = newm; 
    s->cap = newsize;
}

int empty(stack *s)
{
    return s->size <= 0;
}

void push(stack *s, int val)
{
    if (!s) return;
    if (s->size >= s->cap)
        stack_resize(s, s->cap << 1);

    s->data[s->size++] = val;
}

int pop(stack *s)
{
    if (s->size <= 0) return -1;
    int p = s->data[--s->size];
    if (s->cap > 10 && s->size == s->cap >> 2)
        stack_resize(s, s->cap >> 1);
    return p;
}

int peek(stack *s)
{
    if (s->size <= 0) return -1;
    return s->data[s->size - 1];
}

void stack_test(void)
{
    stack *s = stack_create();
    for (int i = 0; i < 100; i++)
        push(s, i);

    while (!empty(s)) 
        printf("size=%d cap=%d %-3d\n", s->size, s->cap, pop(s));
    printf("\n");
}

typedef struct min_stack {
    stack *main_stack;
    stack *assit_stack;
    int size;
} min_stack;

min_stack *min_stack_create(void)
{
    min_stack *s = malloc(sizeof(min_stack));
    if (!s) exit(1);
    s->main_stack = stack_create();
    s->assit_stack = stack_create();
    s->size = 0;
    return s;
}

void m_push(min_stack *s, int val)
{
    if (!s || !s->main_stack || !s->assit_stack)
        return;
    push(s->main_stack, val);
    if (empty(s->assit_stack) || val < peek(s->assit_stack))
        push(s->assit_stack, val);
    else
        push(s->assit_stack, peek(s->assit_stack));
}

int m_empty(min_stack *s)
{
    return empty(s->main_stack) && empty(s->assit_stack);
}

int m_pop(min_stack *s)
{
    if (!s || !s->main_stack || !s->assit_stack)
        return -1;

    if (m_empty(s))
        return -1;
    int p = pop(s->main_stack);
    pop(s->assit_stack);
    return p;
}

int m_min(min_stack *s)
{
    if (!s || !s->main_stack || !s->assit_stack)
        return -1;

    if (m_empty(s))
        return -1;

    return peek(s->assit_stack);
}

int main(int argc, char *argv[])
{
    min_stack *s = min_stack_create();
    /*
     * int a[] = {7, 9, 6, 3, 1, 8, 4, 5, 2, 0};
     * for (int i = 0; i < 10; i++)
     *     m_push(s, a[i]);
     */
    int size = 20;
    int *arr = arrayWithRange(size, 0, 100);
    for (int i = 0; i < size; i++)
        m_push(s, arr[i]);
    while (!m_empty(s)) {
        printf("min = %d ", m_min(s));
        printf("pop %d\n", m_pop(s));
    }
}
