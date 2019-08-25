#include "ds.h"

ht *record = NULL;

int eq(long key1, long key2)
{
    return strcmp((char *)key1, (char *)key2) == 0;
}

long hash(long key)
{
    char *str = (char *)key;
    long h = 0;
    for (char *p = str; *p; p++)
        h += h * 131 + *p;
    return h;
}

#define HT_INSERT(h, k, v) ht_insert(h, (long)(k), (long)(v))
#define HT_CONTAIN(h, k) ht_contain(h, (long)(k))
#define HT_GET_H(h, k) ((ht *)ht_get(h, (long)(k)))
#define HT_GET(h, k) ht_get(h, (long)k)

void update(ht *index, const char *str, int i)
{
    ht *strmap = NULL, *keymap = NULL;
    if (!HT_CONTAIN(record, str)) 
        HT_INSERT(record, str, ht_create_(hash, eq));

    strmap = HT_GET_H(record, str);
    for (int j = 0; j < index->bucket; j++) {
        for (htnode *hn = index->slot[j]; hn; hn = hn->next) {
            const char *key = (const char *)hn->key;
            int value = (int)hn->val;
            if (eq((long)key, (long)str)) 
                continue;

            keymap = HT_GET_H(record, key);
            int cur_min = i - value;
            if (HT_CONTAIN(strmap, key)) {
                int pre_min = HT_GET(strmap, key);
                if (cur_min < pre_min) {
                    HT_INSERT(strmap, key, cur_min);
                    HT_INSERT(keymap, str, cur_min);
                }
            } else {
                HT_INSERT(strmap, key, cur_min);
                HT_INSERT(keymap, str, cur_min);
            }
        }
    }
}

void init(const char *arr[], int size)
{
    ht *index = ht_create_(hash, eq);
    record = ht_create_(hash, eq);
    for (int i = 0; i < size; i++) {
        update(index, arr[i], i);
        HT_INSERT(index, arr[i], i);
    }
    ht_release(&index);
}

int query(const char *str1, const char *str2)
{
    if (!str1 || !str2 || !*str1 || !*str2)
        return 0;

    if (eq((long)str1, (long)str2))
        return 0;

    if (HT_CONTAIN(record, str1) && HT_CONTAIN(HT_GET_H(record, str1), str2))
        return HT_GET(HT_GET_H(record, str1), str2);

    return -1;
}

int main()
{
    const char *str[] = { "1", "3", "2", "3", "3", "3", "1", "4", "4", "2" };
    int size = sizeof(str) / sizeof(str[0]);
    init(str, size);
    printf("%d\n", query("1", "2"));
    printf("%d\n", query("2", "3"));
    printf("%d\n", query("3", "2"));
    printf("%d\n", query("1", "4"));
    printf("%d\n", query("2", "4"));
}
