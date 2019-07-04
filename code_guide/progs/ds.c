#include "ds.h"

deque_node *deque_node_create(long val)
{
    deque_node *n = malloc(sizeof(deque_node));
    if (!n) exit(1);
    n->val = val;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

queue *queue_create(void)
{
    queue *q = malloc(sizeof(queue));
    if (!q) exit(1);
    q->size = 0;
    q->header = q->tailer = NULL;
    return q;
}

int queue_empty(queue *q)
{
    return q->size <= 0 && !q->header && !q->tailer;
}

void queue_enqueue(queue *q, long val)
{
    deque_node *n = deque_node_create(val);
    if (q->tailer)
        q->tailer->next = n;
    q->tailer = n;
    if (!q->header)
        q->header = n;
    q->size++;
}

long queue_dequeue(queue *q)
{
    if (queue_empty(q))
        return -1;

    long tmp = q->header->val;
    deque_node *todel = q->header;
    q->header = q->header->next;
    if (!q->header)
        q->tailer = NULL;
    q->size--;
    free(todel);
    return tmp;
}

void queue_print(queue *q)
{
    if (!q)
        return;

    printf("-----------------------------\n");
    printf("queue size = %d\n", q->size);
    printf("header -> ");
    for (deque_node *cur = q->header; cur; cur = cur->next)
        printf("%-3ld", cur->val);
    printf("<- tailer");
    printf("\n");
    printf("-----------------------------\n");
}

static void queue_test(void)
{
    queue *q = queue_create();
    for (int i = 0; i < 10; i++)
        queue_enqueue(q, i);

    queue_print(q);

    while (!queue_empty(q))
        printf("%-3ld", queue_dequeue(q));
    printf("\n");
}

stknode *stknode_create(long val)
{
    stknode *n = malloc(sizeof(stknode));
    if (!n) exit(1);
    n->val = val;
    n->next = NULL;
    return n;
}

stack *stack_create(void)
{
    stack *s = malloc(sizeof(stack));
    if (!s) exit(1);
    s->size = 0;
    s->top = NULL;
    return s;
}

void stack_push(stack *s, long val)
{
    if (!s)
        return;

    stknode *n = stknode_create(val);
    n->next = s->top;
    s->top = n;
    s->size++;
}

int stack_empty(stack *s)
{
    if (!s)
        return 1;
    return s->size <= 0;
}

long stack_peek(stack *s)
{
    if (stack_empty(s))
        return -1;
    return s->top->val;
}

long stack_pop(stack *s)
{
    if (stack_empty(s))
        return -1;

    long tmp = s->top->val;
    stknode *todel = s->top;
    s->top = s->top->next;
    s->size--;
    free(todel);
    return tmp;
}

void stack_print(stack *s)
{
    if (!s)
        return;

    printf("-----------------------------\n");
    printf("stack size = %ld\n", s->size);
    printf("top -> ");
    for (stknode *cur = s->top; cur; cur = cur->next)
        printf("%-3ld", cur->val);
    printf("\n");
    printf("-----------------------------\n");
}

void stack_release(stack **s)
{
    if (!s || !*s)
        return;

    stack *ss = *s;
    while (!stack_empty(ss))
        stack_pop(ss);

    free(ss);
    *s = NULL;
}

static void stack_test(void)
{
    stack *s = stack_create();
    for (int i = 0; i < 10; i++)
        stack_push(s, i);

    stack_print(s);

    while (!stack_empty(s)) {
        printf("peed %-3ld\n", stack_peek(s));
        printf("pop %-3ld\n", stack_pop(s));
    }
    printf("\n");
}

static void sort_core(int *arr, int size, int lo, int hi)
{
    if (hi - lo + 1 < 30) {
        for (int i = lo; i <= hi; i++) {
            int t = arr[i], j;
            for (j = i - 1; j >= lo && t < arr[j]; j--)
                arr[j + 1] = arr[j];
            arr[j + 1] = t;
        }
        return;
    }

    int pivot = arr[lo];
    int i = lo, j = hi + 1;
    while (1) {
        while (i < hi && arr[++i] < pivot);
        while (j > lo && arr[--j] > pivot);
        if (i >= j) break;
        swap(arr + i, arr + j);
    }
    swap(arr + lo, arr + j);

    sort_core(arr, size, lo, j - 1);
    sort_core(arr, size, j + 1, hi);
}

void sort(int *arr, int size)
{
    if (!arr || size <= 1)
       return;

    sort_core(arr, size, 0, size - 1);
}

int is_sorted(int *arr, int size)
{
    for (int i = 1; i < size; i++)
        if (arr[i] < arr[i - 1])
            return 0;
    return 1;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

long getCurTime(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

void parseArray(int *arr, int *len, char *str)
{
    if (!arr || !len || *len <= 0 || !str) return;
    char *p = str, *q = p;
    int i = 0, n = 0;
    while (*p && *p >= '0' && *p <= '9' && i < *len) {
        n = strtol(q, &p, 10);
        arr[i++] = n;
        while (*p && (*p < '0' || *p > '9')) p++;
        if (!*p) break;
        q = p;
    }
    *len = i;
}

int randWithRange(int lo, int hi)
{
    if (lo == hi)
        return 0;
    usleep(19);
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec + tv.tv_sec * 1000000);
    return rand() % (hi - lo) + lo;
}

void printArray(int *array, int size)
{
    printf("size=%d\n", size);
    for (int i = 0; i < size; i++)
        printf("%-4d", array[i]);
    printf("\n");
}

int *copyArray(int *arr, int size)
{
    int *copy = malloc(sizeof(int) * size);
    memcpy(copy, arr, sizeof(int) * size);
    return copy;
}

int *array(int size)
{
    int *array = malloc(sizeof(int) * size);
    if (!array) {
        printf("memory alloc fail!\n");
        exit(1);
    }
    for (int i = 0; i < size; i++)
        array[i] = i;
    return array;
}

int *arrayWithRange(int size, int lo, int hi)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec);
    int *array = malloc(sizeof(int) * size);
    if (!array) {
        printf("memory alloc fail!\n");
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        int elem = rand() % (hi - lo) + lo;
        array[i] = elem;
    }
    return array;
}

int *arrayWithSize(int size)
{
    return arrayWithRange(size, 0, size);
}
