#include "ds.h"

typedef struct trienode {
    int path;
    int end;
    struct trienode *map[26]; 
} trienode;

trienode *trienode_create()
{
    trienode *n = malloc(sizeof(trienode));
    n->path = n->end = 0;
    memset(n->map, 0, sizeof(void *) * 26);
    return n;
}

void trie_insert(trienode *root, const char *str)
{
    for (char *p = (char *)str; *p; p++) {
        int idx = *p - 'a';
        if (!root->map[idx])
            root->map[idx] = trienode_create();
        root->map[idx]->path++;
        root = root->map[idx];
    }
    root->end++;
}

int trie_find(trienode *root, const char *str)
{
    for (char *p = (char *)str; *p; p++) {
        int idx = *p - 'a';
        if (!root->map[idx])
            return 0;
        root = root->map[idx];
    }
    return root->end > 0;
}

int trie_prefix(trienode *root, const char *prefix)
{
    for (char *p = (char *)prefix; *p; p++) {
        int idx = *p - 'a';
        if (!root->map[idx])
            return 0;
        root = root->map[idx];
    }
    return root->path;
}

int main()
{
    trienode *root = trienode_create();
    trie_insert(root, "abcd");
    trie_insert(root, "abd");
    printf("%d\n", trie_find(root, "abcd"));
    printf("%d\n", trie_find(root, "abd"));
    printf("%d\n", trie_prefix(root, "ab"));
    printf("%d\n", trie_prefix(root, "abc"));
    printf("%d\n", trie_prefix(root, "abcd"));
    printf("%d\n", trie_find(root, "abc"));
}
