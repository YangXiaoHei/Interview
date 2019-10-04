#include "ds.h"

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

int rand01p()
{
    double p = 0.83;
    p *= 100;
    return (rand() % 100 + 1) <= 83 ? 0 : 1;
}

int rand01()
{
    int num;
    while ((num = rand01p()) == rand01p());
    return num;
}

int rand6()
{
    int r, r1, r2;
beg:
    r1 = rand01() * 2 + rand01(); /* 0, 1, 2, 3 */
    r2 = r1  * 2 + rand01(); /* 0, 1, 2, 3, 4, 5, 6, 7 */
    if (r2 > 5) goto beg; /* 筛掉 6, 7, 等概率生成 0, 1, 2, 3, 4, 5 */
    return r2 + 1; /* 1, 2, 3, 4, 5, 6 */
}

int main()
{
    test(100000, rand01);
    test(100000, rand6);
}
