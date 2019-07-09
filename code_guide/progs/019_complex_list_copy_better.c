#include "ds.h"

typedef struct cnode {
    long val;
    struct cnode *next;
    struct cnode *rand;
} cnode;

cnode *cnode_create(long val)
{
    cnode *n = malloc(sizeof(cnode));
    if (!n) exit(1);
    n->val = val;
    n->next = NULL;
    n->rand = NULL;
    return n;
}

cnode *clist_get_kth_node(cnode *list, int k)
{
    while (list && k > 1)
        list = list->next, k--;
    return list;
}

void clist_insert(cnode **list, long val)
{
    cnode *n = cnode_create(val);
    if (!*list) {
        *list = n;
        return;
    }

    cnode *last = *list;
    while (last->next)
        last = last->next;
    last->next = n;
}

cnode *clist_create(int size)
{
    int sz = size;
    cnode *list = NULL;
    while (sz--)
       clist_insert(&list, randWithRange(1, 30));

    cnode *head = list;
    while (list) {
        cnode *r = clist_get_kth_node(head, rand() % size + 1);
        list->rand = r;
        list = list->next;
    }
    return head;
}

void clist_print(cnode *list)
{
    while (list) {
        printf("%ld(%ld) ", list->val, list->rand ? list->rand->val : -1);
        list = list->next;
    }
    printf("\n");
}

cnode *complex_list_copy(cnode *list)
{
    if (!list)
        return NULL;

    // 复制
    for (cnode *cur = list; cur; cur = cur->next->next) {
        cnode *copy = cnode_create(cur->val);
        copy->next = cur->next;
        cur->next = copy;
    }

    // 连接复制节点的 rand
    for (cnode *cur = list; cur; cur = cur->next->next) 
        cur->next->rand = cur->rand ? cur->rand->next : NULL;

    // 拆解
    cnode *newhead = NULL;
    cnode *newlast = NULL;
    for (cnode *cur = list; cur; cur = cur->next) {
        if (!newhead) {
            newhead = newlast = cur->next;
        } else {
            newlast->next = cur->next;
            newlast = newlast->next;
        }
        cur->next = cur->next->next;
    }
    return newhead;
}

int main(int argc, char *argv[])
{
    cnode *list = clist_create(5);
    clist_print(list);
    cnode *copy = complex_list_copy(list);
    clist_print(copy);
}
