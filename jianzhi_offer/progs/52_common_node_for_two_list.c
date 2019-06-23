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

node* list_insert(node **head, int val)
{
    node *n = node_create(val);
    if (!*head) {
        *head = n;
        return n;
    }
    node *cur = *head;
    while (cur->next)
        cur = cur->next;
    cur->next = n;
    return n;
}

/* 生成测试用例 */
void list_create(node **head1, node **head2)
{
    if (*head1 || *head2)
        return;

    int size1 = randWithRange(1, 10);
    int size2 = randWithRange(1, 20);
    int sz1 = size1, sz2 = size2;
    int beg1 = 0, beg2 = 30;
    node *last1 = NULL, *last2 = NULL;
    while (sz1--) 
        last1 = list_insert(head1, beg1++);

    while (sz2--)
        last2 = list_insert(head2, beg2++);

    node *be_common = NULL;
    int r = randWithRange(0, 2);
    if (r & 1) {
        node *cur = *head1;
        int kth = randWithRange(0, size1);
        while (kth--)
            cur = cur->next;
        last2->next = cur;

        printf("common node = %-3d\n", cur->val);
    } else {
        node *cur = *head2;
        int kth = randWithRange(0, size2);
        while (kth--)
            cur = cur->next;
        last1->next = cur;
        printf("common node = %-3d\n", cur->val);
    }
}

void list_print(node *head)
{
    while (head) {
        printf("%-3d", head->val);
        head = head->next;
    }
    printf("\n");
}

node* find_common_node(node *head1, node *head2)
{
    if (!head1 || !head2)
        return NULL;

    int size1 = 0, size2 = 0;
    node *cur1 = head1, *cur2 = head2;

    while (cur1)
        size1++, cur1 = cur1->next;

    while (cur2)
        size2++, cur2 = cur2->next;

    node *go_early = size1 > size2 ? head1 : head2;
    node *go_later = go_early == head1 ? head2 : head1;

    int diff = size1 - size2;
    diff = diff < 0 ? -diff : diff;

    while (diff--)
        go_early = go_early->next;

    while (go_early && go_later) {
        if (go_early == go_later)
            break;
        go_early = go_early->next;
        go_later = go_later->next;
    }

    return (!go_early || !go_later) ? NULL : go_later;
}

int main(int argc, char *argv[])
{
    node *head1 = NULL, *head2 = NULL;
    list_create(&head1, &head2);
    list_print(head1);
    list_print(head2);
    
    node *common = find_common_node(head1, head2);
    if (common)
        printf("result common node = %-3d\n", common->val);
    else
        printf("no common node\n");
}
