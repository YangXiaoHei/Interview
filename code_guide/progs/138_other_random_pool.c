#include "ds.h"

typedef struct pool {
    int size; 
    ht *key_idx_map;
    ht *idx_key_map;
} pool;

pool *pool_create()
{
    pool *p = malloc(sizeof(pool));
    p->size = 0;
    p->key_idx_map = ht_create();
    p->idx_key_map = ht_create();
    return p;
}

void pool_insert(pool *p, long key)
{
    if (!p)
        return;

    ht_insert(p->key_idx_map, key, p->size);
    ht_insert(p->idx_key_map, p->size, key);
    p->size++;
}

int pool_size(pool *p)
{
    return !p ? 0 : p->size;
}

void pool_delete(pool *p, long delkey)
{
    if (!p || !ht_contain(p->key_idx_map, delkey))
        return;

    long lastidx = p->size - 1;
    long lastkey = ht_get(p->idx_key_map, lastidx);
    long delidx = ht_get(p->key_idx_map, delkey);

    ht_remove(p->idx_key_map, lastidx);
    ht_remove(p->idx_key_map, delidx);
    ht_remove(p->key_idx_map, delkey); 
    ht_remove(p->key_idx_map, lastkey); 

    ht_insert(p->idx_key_map, delidx, lastkey);
    ht_insert(p->key_idx_map, lastkey, delidx);
    p->size--;
}

long pool_random(pool *p)
{
    if (!p || p->size <= 0)
        return 0;
    
    long idx = rand() % p->size;
    return ht_get(p->idx_key_map, idx); 
}

void test(int times, pool *p)
{
    if (pool_size(p) <= 0)
        return;

    ht *stat = ht_create();
    for (int i = 0; i < times; i++) {
        long key = pool_random(p);
        if (ht_contain(stat, key)) {
            long count = ht_get(stat, key);
            ht_insert(stat, key, count + 1);
        } else {
            ht_insert(stat, key, 1);
        }
    }

    printf("standard : %.2f\n", 1.0 / pool_size(p));
    for (int i = 0; i < stat->bucket; i++) {
        for (htnode *hn = stat->slot[i]; hn; hn = hn->next) {
            long key = hn->key;
            long val = hn->val;
            printf("(%-3ld %4.2f) ", key, val * 1.0 / times);
        }
    }
    printf("\n\n");
}

int main()
{
    int times = 100000;
    pool *p = pool_create();
    for (int i = 0; i < 10; i++) {
        pool_insert(p, i);
    }
    test(times, p);

    for (int i = 10; i >= 0; i--) {
        printf("delete %d\n", i);
        pool_delete(p, i);
        test(times, p);
    }
}
