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
    /*
     * N 个节点的链表，k 代表倒数第几个节点，k = {1, 2, 3, 4, ...}
     * 若指针 s 指向链表头节点, s 移动到指向倒数第 k 个节点，需要走 N - k 步
     * 我们的方案是：让一个快指针 f 先走 x 步，然后以快指针 f->next == NULL 作为终止条件让 s 和 f
     * 一起走，当 f 指向最后一个节点，s 便指向倒数第 k 个节点。
     * 现在来反推 x 是多少 ? 
     * 因为 f 走 N - 1 就会指向最后一个节点，而 s 指向倒数第 k 个节点需要走 N - k 步，
     * 这 N - k 步是 s 和 f 一起走的，而 f 需要额外先走的步数为 N - 1 - N + k = k - 1 步
     */

    if (k == 0 || !list) 
        return -1;
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
