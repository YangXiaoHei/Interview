#include <stdio.h>
#include <stdlib.h>

typedef struct snode {
    void *val;
    struct snode *next;
} snode;

typedef struct lnode {
    int val;
    struct lnode *next;
} lnode;

typedef struct stack {
    int size;
    snode *top;
} stack;

stack *create_stack(void)
{
    stack *s = malloc(sizeof(stack));
    if (!s) return NULL;
    s->size = 0;
    s->top = NULL;
    return s;
}

lnode *create_lnode(int val)
{
    lnode *n = malloc(sizeof(lnode));
    if (!n) return NULL;
    n->val = val;
    n->next = NULL;
    return n;
}

snode *create_snode(void *val)
{
    snode *n = malloc(sizeof(snode));
    if (!n) return NULL;
    n->val = val;
    n->next = NULL;
    return n;
}

void push(stack *s, void *val)
{
    snode *n = create_snode(val);
    n->next = s->top;
    s->top = n;
    s->size++;
}

void *pop(stack *s)
{
    if (!s->top)
        return NULL;
    snode *topnode = s->top;
    void *val = topnode->val;
    s->top = topnode->next;
    free(topnode);
    s->size--;
    return val;
}

int stack_empty(stack *s)
{
    return s->size == 0;
}

lnode *list_create(int size)
{
    int i = 0;
    lnode *sential = create_lnode(size);
    while (size--) {
        lnode *n = create_lnode(i++);
        n->next = sential->next;
        sential->next = n;
    }
    lnode *list = sential->next;
    free(sential);
    return list;
}

void reverse_print_list(lnode *list)
{
    stack *s = create_stack();
    while (list) {
        push(s, list);
        list = list->next;
    }

    while (!stack_empty(s)) {
        lnode *n = pop(s);
        printf("%-3d", n->val);
    }
}

int main(int argc, char *argv[])
{
    lnode *list = list_create(10);
    reverse_print_list(list);
    printf("\n");
}



