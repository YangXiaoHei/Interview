#include "ds.h"

#define HT_INSERT(h, k, v) ht_insert(h, (long)(k), (long)(v))
#define HT_CONTAIN(h, k) ht_contain(h, (long)(k))
#define HT_GET(h, k) ((trienode *)ht_get(h, (long)(k)))
#define HT_REMOVE(h, k) ht_remove(h, (long)(k))

struct trienode {
    int path;
    int end;
    ht *map;
};

trienode *trienode_create()
{
    trienode *n = malloc(sizeof(struct trienode));
    if (!n) exit(1);
    n->path = n->end = 0;
    n->map = ht_create();
    return n;
}

void trienode_release(trienode **n)
{
    if (!n || !*n)
        return;

    ht_release(&n->map);
    free(*n);
    *n = NULL;
}

void trie_insert(trienode *root, const char *str)
{
    if (!root || !str || !*str)
        return;

    tridenode *n = root;
    for (char *p = (char *)str; *p; p++) {
        if (!HT_CONTAIN(n->map, *p))
            HT_INSERT(n->map, *p, trienode_create());
        n = HT_GET(n->map, *p);
        n->path++;
    }
    n->end++;
}

int trie_find(trienode *root, const char *str)
{
    if (!root || !str || !*str)
        return 0;    

    trienode *n = root;
    for (char *p = (char *)str; *p; p++) {
        if (!HT_CONTAIN(n->map, *p))
            return 0;
        n = HT_GET(n->map, *p);
    }
    return n->end;
}

int trie_prefix(trienode *root, const char *prefix)
{
    if (!root || !prefix || !*prefix)
        return 0;

    trienode *n = root;
    for (char *p = (char *)root; *p; p++) {
        if (!HT_CONTAIN(n->map, *p))
            return 0;
        n = HT_GET(n->map, *p);
    }
    return n->path;
}

void trie_remove(trienode *root, const char *str)
{
    if (!root || !str || !*str)
       return; 

    if (!trie_find(root, str))
        return;

    trienode *prev = root;
    trienode *cur = HT_GET(root->map, *str);
    trienode *next = NULL;
    for (char *p = (char *)str + 1; *p; p++) {
        next = HT_GET(cur->map, *p); 
        if (--cur->path == 0) {
            HT_REMOVE(prev->map, p[-1]);
            trienode_release(&cur);
        }
        prev = cur;
        cur = next;
    }
}

int main(int argc, char *argv[])
{

}
