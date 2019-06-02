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

node *list_create(int size)
{
    node *list = NULL;
    for (int i = 0; i < size; i++)
        list_insert(&list, i);    
    return list;
}

void list_print(node *list)
{
    while (list) {
        printf("%-3d", list->val);
        list = list->next;
    }
    printf("\n");
}

int backward_kth_node(node *list, unsigned k)
{
    if (k == 0 || !list) return -1;
    node *fast = list;
    while (--k && fast) 
        fast = fast->next;

    if (!fast) return -1;

    node *slow = list;
    while (fast->next) {
        fast = fast->next;
        slow = slow->next;
    }
    return slow->val;
}

int main(int argc, char *argv[])
{
    node *list = list_create(10);
    list_print(list);
    int r = randWithRange(1, 20);
    printf("backward %dth node = %d\n", r, backward_kth_node(list, r));
}
