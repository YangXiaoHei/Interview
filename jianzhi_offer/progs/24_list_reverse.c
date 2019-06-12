#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

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

void list_insert(node **head, int val)
{
    node *n = node_create(val);
    if (!*head) {
        *head = n;
        return;
    }

    node *last = *head;
    while (last->next)
        last = last->next;
    last->next = n;
}

node* list_create(int size)
{
    node *list = NULL;
    for (int i = 0; i < size; i++)
        list_insert(&list, i);
    return list;
}

void list_print(node *list)
{
    if (!list) return;
    while (list) {
        printf("%-3d", list->val);
        list = list->next;
    }
    printf("\n");
}

void list_reverse(node **list)
{
    if (!list) 
        return;
    if (!*list) 
        return;
    if (!(*list)->next) 
        return;

    node *p = NULL, *q = *list, *tmp = NULL;
    while (q) {
        tmp = q->next; 
        q->next = p;
        p = q;
        q = tmp;
    }
    *list = p;
}


int main(int argc, char *argv[])
{
    int r = randWithRange(1, 20);
    node *list = list_create(r);
    list_print(list);
    list_reverse(&list);
    list_print(list);
}

