#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} node;

node *node_create(int val)
{
    node *n = malloc(sizeof(node));
    if (!n) exit(1);
    n->val = val;
    n->next = NULL;
    return n;
}

typedef struct stack {
    node *top;
    int size;
} stack;

stack *stack_create(void)
{
    stack *s = malloc(sizeof(stack));
    if (!s) exit(1);
    s->top = NULL;
    s->size = 0;
    return s;
}

void push(stack *s, int val)
{
    node *n = node_create(val);
    n->next = s->top;
    s->top = n;
    s->size++;
}

int pop(stack *s)
{
    if (s->size <= 0)
        return -1;

    int p = s->top->val;
    node *t = s->top;
    s->top = s->top->next;
    free(t);
    s->size--;
    return p;
}

int peek(stack *s)
{
    if (s->size <= 0)
        return -1;

    return s->top->val;
}

int empty(stack *s)
{
    return s->size <= 0;
}

void stack_print(stack *s)
{
    if (!s)
        return;

    node *cur = s->top;
    while (cur)
        printf("%-3d", cur->val), cur = cur->next;
    printf("\n");
}

void stack_release(stack **s)
{
    if (!s || !*s)
        return;
    
    stack *ss = *s;
    while (!empty(ss)) {
        node *t = ss->top;
        ss->top = ss->top->next;
        free(t);
        ss->size--;
    }
    free(ss);
    *s = NULL;
}

int is_seq_valid(int *arr1, int size1, int *arr2, int size2)
{
    if (!arr1 || !arr2 || size1 <= 0 || size2 <= 0)
        return 0;

    stack *s = stack_create();
    int i = 0, j = 0;
    do {
        if (i < size1)
            push(s, arr1[i++]);

        while (!empty(s) && peek(s) == arr2[j]) {
            pop(s);
            j++;
        }

        if (i >= size1 && !empty(s))
            break;

    } while (!empty(s));
    int valid = empty(s);
    stack_release(&s);
    return valid;
}

int main(int argc, char *argv[])
{
    int arr1[] = { 1, 2, 3, 4, 5 };
    /* int arr2[] = { 4, 5, 3, 2, 1 }; */
    int arr2[] = { 4, 3, 5, 1, 2 };

    printf("%d\n", is_seq_valid(arr1, 5, arr2, 5));
}
