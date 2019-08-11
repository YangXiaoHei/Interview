#include "ds.h"

#define HT_INSERT(h, k, v) ht_insert(h, (long)(k), (long)(v))
#define HT_CONTAIN(h, k) ht_contain(h, (long)(k))
#define HT_GET_H(h, k) ((ht *)ht_get(h, (long)(k)))
#define HT_GET(h, k) ht_get(h, (long)(k))

long string_hash(long key)
{
    char *str = (char *)key;
    unsigned h = 0;
    for (char *p = str; *p; p++)
        h += (h << 5) - h + *p;
    return h & 0x7fffffff;
}

int string_eq(long key1, long key2)
{
    return strcmp((char *)key1, (char *)key2) == 0;
}

void string_ht_print(long key, long val)
{
    printf("%s\n", (char *)key);
    ht *h = (ht *)val;
    for (int i = 0; i < h->bucket; i++) {
        if (!h->slot[i])
            continue;
        printf("\t");
        for (htnode *hn = h->slot[i]; hn; hn = hn->next) 
            printf("{%s %d} ", (char *)hn->key, (int)hn->val);
        printf("\n");
    }
}

void update_record(ht *index, ht *record, const char *str, int i)
{
    if (!HT_CONTAIN(record, str)) 
        HT_INSERT(record, str, ht_create_(string_hash, string_eq));

    ht *str_ht = HT_GET_H(record, str);
    for (int j = 0; j < index->bucket; j++) {
        for (htnode *hn = index->slot[j]; hn; hn = hn->next) {
            long key = hn->key;
            long idx = hn->val;
            if (!string_eq(key, (long)str)) {
                ht *key_ht = HT_GET_H(record, key);
                int cur_diff = i - idx;
                if (HT_CONTAIN(str_ht, key)) {
                    if (cur_diff < HT_GET(str_ht, key)) {
                        HT_INSERT(str_ht, key, cur_diff);
                        HT_INSERT(key_ht, str, cur_diff);
                    }
                } else {
                    HT_INSERT(str_ht, key, cur_diff);
                    HT_INSERT(key_ht, str, cur_diff);
                }
            }
        }
    }
}

void init_record(const char *str[], int size, ht *record)
{
    ht *index = ht_create_(string_hash, string_eq);
    for (int i = 0; i < size; i++) {
        const char *s = str[i];
        update_record(index, record, s, i);
        HT_INSERT(index, s, i);
    } 
    ht_release(&index);
}

int query(ht *record, const char *str1, const char *str2)
{
    if (!str1 || !str2 || !*str1 || !*str2)
        return -1;

    if (string_eq((long)str1, (long)str2))
        return 0;

    if (HT_CONTAIN(record, str1) && HT_CONTAIN(HT_GET_H(record, str1), str2))
        return HT_GET(HT_GET_H(record, str1), str2);

    return -1;
}

int main(int argc, char *argv[])
{
    const char *str[] = { "1", "3", "3", "3", "2", "3", "1" };
    int size = sizeof(str) / sizeof(str[0]);
    ht *record = ht_create_(string_hash, string_eq);
    init_record(str, size, record);

    printf("%d\n", query(record, "1", "2"));
    printf("%d\n", query(record, "2", "1"));
    printf("%d\n", query(record, "3", "2"));
    printf("%d\n", query(record, "2", "3"));
    printf("%d\n", query(record, "3", "3"));
}
