#include "ds.h"

int rand5()
{
    return rand() % 5 + 1;
}

int rand7()
{
    int r1, r2, r; 
beg:
    r1 = rand5() - 1; /* 0, 1, 2, 3, 4 */
    r2 = (rand5() - 1) * 5; /* 0, 5, 10, 15, 20 */
    r = r1 + r2; /* 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, ... 20, 21, 22, 23, 24 */
    if (r > 20) goto beg;
    return r % 7 + 1;
}

void test(int times, int(*rfun)(void))
{
    ht *h = ht_create();
    for (int i = 0; i < times; i++) {
        int r = rfun();
        if (ht_contain(h, r)) {
            int pre_times = ht_get(h, r);
            ht_insert(h, r, pre_times + 1);
        } else {
            ht_insert(h, r, 1);
        }
    }
    printf("standard : %-8.2f\n", 1.0 / ht_size(h));
    for (int i = 0; i < h->bucket; i++) {
        for (htnode *hn = h->slot[i]; hn; hn = hn->next) {
            int key = hn->key;
            int val = hn->val;
            printf("%d - %-8.2f",  key, val * 1.0 / times);
        }
    }
    printf("\n");
    ht_release(&h);
}

int main()
{
    test(100000, rand5);
    test(100000, rand7);
}
