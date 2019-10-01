#include "ds.h"

#define HEAP_INSERT(h, v) heap_insert(h, (long)(v))
#define HEAP_POP(h) ((myinfo *)heap_pop(h))

/* 包裹类 */
typedef struct myinfo {
    int value;   /* 值 */
    int arr; /* 该值在哪个数组中 */
    int index; /* 该值在数组中的索引是啥 */
} myinfo;

/* 最大堆比较器 */
int maxcmp(long a, long b)
{
    myinfo *ap = (myinfo *)a;
    myinfo *bp = (myinfo *)b;
    int res = ap->value == bp->value ? 0 : ap->value > bp->value ? 1 : -1;
    return -res;
}

/* 打印堆中内容, 用于 debug */
void heap_elem_print(long a)
{
    myinfo *ap = (myinfo *)a;
    printf("{ %-2d %-2d %-3d } ", ap->arr, ap->index, ap->value);
}

/* 从 N 个已排序, 长度不等的数组中找出整体最大的 top K 元素  */
void N_arr_top_k(myinfo **infos, int *sizes, int N, int k)
{
    heap *h = heap_create_(maxcmp);
    for (int i = 0; i < N; i++) {
        HEAP_INSERT(h, &infos[i][sizes[i] - 1]);
    }     

    /* ❌ what a fuck ???? */
/*
 *     heap_print_funptr(h, heap_elem_print);
 * 
 *     int cur = 0;
 *     int *res = malloc(sizeof(int) * k);
 *     memset(res, 0, sizeof(int) * k);
 * 
 *     heap_print_funptr(h, heap_elem_print);
 */

    printf("------ 华丽的分割线 -----------\n");
    while (k > 0 && !heap_empty(h)) {
        myinfo *top = HEAP_POP(h);
        printf("%-4d", top->value);
        k--;
        if (top->index > 0) 
            HEAP_INSERT(h, &infos[top->arr][top->index - 1]);
    }
    printf("\n");
    heap_release(&h);
}

int main()
{
    setbuf(stdout, NULL);

    int N = 8;   /* N 个数组 */
    int *sizes = arrayWithRange(N, 1, 10);  /* 生成 N 个长度，给 N 个数组用 */

    /* N 个整形的指针数组 */
    int **arrs = malloc(sizeof(int *) * N); 
    memset(arrs, 0, sizeof(int *) * N);

    /* 生成 N 个长度不同的数组，并分别排序 */
    for (int i = 0; i < N; i++) {
        arrs[i] = arrayWithRange(sizes[i], 0, 50);
        sort(arrs[i], sizes[i]);
    }

    /* debug */
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < sizes[i]; j++) 
            printf("%-4d", arrs[i][j]);
        printf("\n");
    }

    /* N 个结构体的指针数组 */
    myinfo **infos = malloc(sizeof(myinfo *) * N);
    memset(infos, 0, sizeof(myinfo *) * N);

    /* 根据已排序数组生成包裹类, 同时记录数组值, 数组索引和索引 */
    for (int i = 0; i < N; i++) {
        infos[i] = malloc(sizeof(myinfo) * sizes[i]);
        for (int j = 0; j < sizes[i]; j++) {
            infos[i][j].value = arrs[i][j];
            infos[i][j].arr = i;
            infos[i][j].index = j;
        }
    }

    /* debug */
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < sizes[i]; j++) 
            printf("{ %-2d %-2d %-4d } ", infos[i][j].arr, infos[i][j].index, infos[i][j].value);
        printf("\n");
    }

    int k = 20;
    N_arr_top_k(infos, sizes, N, k);
}
