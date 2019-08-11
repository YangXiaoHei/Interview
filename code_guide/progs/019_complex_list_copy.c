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

cnode *copy_complex_list(cnode *list)
{
    ht *h = ht_create();

#define HT_INSERT(h, x, v) ht_insert(h, (long)x, (long)v);
#define HT_GET(h, x) ((cnode *)ht_get(h, (long)x))

    cnode *head = list;
    while (head) {
        cnode *copy_node = cnode_create(head->val);
        HT_INSERT(h, head, copy_node);
        head = head->next;
    }
    HT_INSERT(h, NULL, NULL);

    head = list;
    while (head) {
        HT_GET(h, head)->next = HT_GET(h, head->next);
        HT_GET(h, head)->rand = HT_GET(h, head->rand);
        head = head->next;
    }
    return HT_GET(h, list);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    cnode *list = clist_create(4);
    clist_print(list);
    cnode *copy = copy_complex_list(list);
    clist_print(copy);
}
