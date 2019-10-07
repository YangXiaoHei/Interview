#include "ds.h"

typedef struct cache {
    int size;
    int capacity;
    dlnode *head;
    ht *key_node_map;
    ht *node_key_map;
} cache;

cache *cache_create(int cap)
{
    if (cap < 2)
        return NULL;

    cache *c = malloc(sizeof(cache));
    c->capacity = cap;
    c->size = 0;
    c->head = NULL;
    c->key_node_map = ht_create();
    c->node_key_map = ht_create();
    return c;
}

long cache_get(cache *c, long key)
{
    if (!c || !ht_contain(c->key_node_map, key))
        return 0;

    dlnode *keynode = (dlnode *)ht_get(c->key_node_map, key);
    dlist_move_to_tail(&c->head, keynode);
    return keynode->val;
}

int cache_size(cache *c)
{
    return !c ? 0 : c->size;
}

void cache_set(cache *c, long key, long val)
{
    if (!c)
        return;

    if (ht_contain(c->key_node_map, key)) {
        dlnode *oldn = (dlnode *)ht_get(c->key_node_map, key);
        oldn->val = val;
        dlist_move_to_tail(&c->head, oldn);
    } else {
        dlnode *newn = dlist_insert(&c->head, val);
        ht_insert(c->key_node_map, key, (long)newn);
        ht_insert(c->node_key_map, (long)newn, key);
        if (++c->size > c->capacity) {
            dlnode *head = c->head;
            long headkey = ht_get(c->node_key_map, (long)head);
            ht_remove(c->key_node_map, headkey);
            ht_remove(c->node_key_map, (long)head);
            dlist_remove_head(&c->head);
            c->size--;
        }
    }
}

int main()
{
    cache *c = cache_create(4);    
    cache_set(c, 'A', 1);
    cache_set(c, 'B', 2);
    cache_set(c, 'C', 3);
    cache_set(c, 'D', 4);
    dlist_print_front(c->head);
    cache_get(c, 'C');
    printf("after get (C, 3)\n");
    dlist_print_front(c->head);
    printf("after get (A, 1)\n");
    cache_get(c, 'A');
    dlist_print_front(c->head);
    cache_set(c, 'E', 5);
    printf("set (E, 5)\n");
    dlist_print_front(c->head);
    cache_get(c, 'C');
    printf("after get (C, 3)\n");
    dlist_print_front(c->head);
    cache_set(c, 'F', 6);
    printf("set (F, 6)\n");
    dlist_print_front(c->head);
}
