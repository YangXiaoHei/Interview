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

node *list_get_k(node *list, int k)
{
    while (k--)
        list = list->next;
    return list;
}

node *list_create(int size)
{
    node *list = NULL;
    for (int i = 0; i < size; i++)
        list_insert(&list, i);

    int r = randWithRange(0, size);
    printf("r=%d\n", r);
    node *kth = list_get_k(list, r);

    node *last = list_get_k(list, size - 1);
    last->next = kth;

    return list;
}

void list_print_size(node *list, int size)
{
    if (!list || size <= 0) return;
    while (size--) {
        printf("%-3d", list->val);
        list = list->next;
    }
    printf("\n");
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

int list_find_loop(node *list)
{
    if (!list) return 0;

    node *slow = list;
    node *fast = list;
    do {
        fast = fast->next;
        if (!fast) return 0;

        fast = fast->next;
        if (!fast) return 0;

        slow = slow->next;
    } while (fast != slow);

    int n = 1;
    node *tmp = slow;
    while (slow->next != tmp) {
        n++;
        slow = slow->next;
    }
    return n;
}

node *list_find_loop_entry(node *list)
{
    if (!list) return NULL;
    int nodes_in_loop = list_find_loop(list);
    if (nodes_in_loop <= 0) return NULL;

    node *fast = list;
    while (nodes_in_loop--)
        fast = fast->next;

    node *slow = list;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

int main(int argc, char *argv[])
{
    node *list = list_create(10);
    list_print_size(list, 20);

    printf("nodes in loop=%d\n", list_find_loop(list));

    node *entry = list_find_loop_entry(list);
    if (!entry)
        exit(0);
    printf("list loop entry=%d\n", entry->val);
}
