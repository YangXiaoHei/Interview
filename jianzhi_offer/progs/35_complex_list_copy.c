#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tool.h"

typedef struct node {
    int val;
    struct node *next;
    struct node *sibling;
} node;

node *node_create(int val)
{
    node *n = malloc(sizeof(node));
    n->val = val;
    n->next = n->sibling = NULL;
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

node *list_get_k(node *head, int k)
{
    while (head->next && k--)
        head = head->next;
    return head;
}

void list_random_connect(node *head)
{
    if (!head) return;
    int size = 0;
    node *cur = head;
    while (cur) {
        cur = cur->next;
        size++;
    }
    int a = randWithRange(0, size);
    usleep(10);
    int b = randWithRange(0, size);
    node *anode = list_get_k(head, a);
    node *bnode = list_get_k(head, b);
    anode->sibling = bnode;
}

node *list_create(int size)
{
    node *head = NULL;
    for (int i = 0; i < size; i++) 
        list_insert(&head, i);
    for (int i = 0; i < 4; i++)
        list_random_connect(head);
    return head;
}

void list_print(node *head)
{
    node *cur = head;
    while (cur) {
        printf("%-3d", cur->val);
        cur = cur->next;
    }
    printf("\n");

    cur = head;
    while (cur) {
        if (cur->sibling)
            printf("%-3d->%3d\n", cur->val, cur->sibling->val);
        cur = cur->next;
    }
}

void copy_list(node *head)
{
    node *cur = head;
    while (cur) {
        node *newnode = node_create(cur->val);
        newnode->next = cur->next;
        cur->next = newnode;
        cur = newnode->next;
    }
}

void connect_sibling(node *head)
{
    node *cur = head;
    while (cur) {
        if (cur->sibling) 
            cur->next->sibling = cur->sibling->next;
        cur = cur->next->next;
    }
}

node *split_list(node *head)
{
    node *cur = head;
    node *copy = cur->next;
    node *copyhead = copy;
    while (cur) {
        cur->next = cur->next->next;
        if (!cur->next) 
            break;
        copy->next = copy->next->next;
        cur = cur->next;
        copy = copy->next;
    }
    return copyhead;
}

node *copy(node *head)
{
    copy_list(head);
    connect_sibling(head);
    return split_list(head); 
}

int main(int argc, char *argv[])
{
    node *list = list_create(10);
    list_print(list);
    node *copylist = copy(list);
    list_print(copylist);
}
