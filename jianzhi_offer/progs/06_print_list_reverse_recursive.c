#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next; 
} node;

node *node_create(int val)
{
    node *n = malloc(sizeof(node));
    if (!n) return NULL;
    n->val = val;
    n->next = NULL;
    return n;
}

node *list_create(int size)
{
    int i = 0;
    node *sential = node_create(size);
    while (size--) {
        node *n = node_create(i++);
        n->next = sential->next;
        sential->next = n;
    } 
    node *list = sential->next;
    free(sential);
    return list;
}

void reverse_print_list(node *n)
{
    if (!n) return;

    reverse_print_list(n->next);
    printf("%-3d", n->val);
}

int main(int argc, char *argv[])
{
    node *list = list_create(10);
    reverse_print_list(list);    
    printf("\n");
}
