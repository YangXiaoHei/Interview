#include "ds.h"

typedef struct trienode {
    int path;
    int end;
    struct trienode *parent;
    struct trienode *map[256];
} trienode;

trienode *trienode_create()
{
    trienode *n = malloc(sizeof(struct trienode));
    if (!n) exit(1);
    n->path = n->end = 0;
    n->parent = NULL;
    memset(n->map, 0, sizeof(trienode *) * 256);
    return n;
}

void trienode_release(trienode **n)
{
    if (!n || !*n)
        return;

    free(*n);
    *n = NULL;
}

void trie_insert(trienode *root, const char *str)
{
    if (!root || !str || !*str)
        return;

    trienode *n = root;
    for (char *p = (char *)str; *p; p++) {
        if (!n->map[*p]) {
            trienode *newn = trienode_create();
            n->map[*p] = newn; 
            newn->parent = n;
        }
        n = n->map[*p];
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
        if (!n->map[*p])
            return 0;
        n = n->map[*p];
    }
    return n->end;
}

int trie_prefix(trienode *root, const char *prefix)
{
    if (!root || !prefix || !*prefix)
        return 0;

    trienode *n = root;
    for (char *p = (char *)prefix; *p; p++) {
        if (!n->map[*p])
            return 0;
        n = n->map[*p];
    }
    return n->path;
}

void trie_remove(trienode *root, const char *str)
{
    if (!root || !str || !*str)
       return; 

    if (!trie_find(root, str))
        return;

    int len = 0;
    trienode *cur = root;
    for (char *p = (char *)str; *p; p++, len++) {
        cur->map[*p]->path--;
        cur = cur->map[*p];
    }
    cur->end--;

    trienode *prev = NULL;
    int del = 0;
    while (cur != root && cur->path == 0) {
        del = 1;
        prev = cur->parent; 
        free(cur);
        cur = prev;
        len--;
    }
    if (del) 
        cur->map[str[len]] = NULL;
}

int main(int argc, char *argv[])
{
    trienode *root = trienode_create();
    trie_insert(root, "1234");
    trie_insert(root, "123");
    trie_insert(root, "12");
    trie_insert(root, "1");

    printf("prefix of 1234 : %d\n", trie_prefix(root, "1234"));
    printf("prefix of 123 : %d\n", trie_prefix(root, "123"));
    printf("prefix of 12 : %d\n", trie_prefix(root, "12"));
    printf("prefix of 1 : %d\n", trie_prefix(root, "1"));

    printf("before remove 1, find 1 : %d\n", trie_find(root, "1"));
    trie_remove(root, "1");
    printf("after remove 1, find 1 : %d\n", trie_find(root, "1"));

    printf("before remove 123, find 123 : %d\n", trie_find(root, "123"));
    trie_remove(root, "123");
    printf("after remove 123, find 123 : %d\n", trie_find(root, "123"));

    printf("prefix of 1234 : %d\n", trie_prefix(root, "1234"));
    printf("prefix of 123 : %d\n", trie_prefix(root, "123"));
    printf("prefix of 12 : %d\n", trie_prefix(root, "12"));
    printf("prefix of 1 : %d\n", trie_prefix(root, "1"));
}
