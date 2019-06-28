#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

node *loop_create(int size)
{
    node *head = NULL;
    for (int i = 0; i < size; i++)
        list_insert(&head, i);

    node *last = head;
    while(last->next)
        last = last->next;
    last->next = head;
    return head;
}

void list_print(node *list)
{
    if (!list)
        return;

    node *old = list;
    do {
        printf("%-3d", list->val);
        list = list->next;
    } while (list != old);
    printf("\n");
}

void joseph_solve(node **listp, int k)
{
    if (!listp || !*listp || k <= 0)
        return;

    node *list = *listp;
    while (list->next != list) {
        for (int i = 1; i < k; i++)
            list = list->next;

        list->val = list->next->val;
        node *tmp = list->next;
        list->next = list->next->next;
        free(tmp);
    }
    *listp = list;
}

int main(int argc, char *argv[])
{
    int size = randWithRange(5, 20);
    int r = randWithRange(1, 15);
    printf("r = %d\n", r);
    node *list = loop_create(size);
    list_print(list); 
    joseph_solve(&list, r);
    list_print(list);
}
