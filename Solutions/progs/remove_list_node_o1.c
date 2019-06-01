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
    n->next = NULL;
    n->val = val;
    return n;
}

node *list_create(int size)
{
    node *n = node_create(size);
    while (--size) {
        node *tmp = node_create(size);
        tmp->next = n;
        n = tmp;
    }
    return n;
}

void list_print(node *n)
{
    while (n) {
        printf("%-3d", n->val);
        n = n->next;
    }
    printf("\n");
}

void remove_node(node **head, node *todel)
{
    if (!head || !*head) return;
    if (!todel) return;

    if (*head == todel) {
        node *tmp = *head;
        *head = (*head)->next;
        free(tmp);
        return;
    }

    if (!todel->next) {
        node *cur = *head;
        while (cur->next != todel)
            cur = cur->next;     
        free(todel);
        cur->next = NULL;
        return;
    }

    todel->val = todel->next->val;
    node *tmp = todel->next;
    todel->next = todel->next->next;
    free(tmp);
}

int main(int argc, char *argv[])
{
    node *list = list_create(10);
    list_print(list);

    remove_node(&list, list);    
    list_print(list);

    node *last = list;
    while (last->next)
        last = last->next;
    remove_node(&list, last);
    list_print(list);

    node *middle = list;
    int k = 4;
    while (k--)
        middle = middle->next;
    remove_node(&list, middle);
    list_print(list);
}
