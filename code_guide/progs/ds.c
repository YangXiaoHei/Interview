#include "ds.h"

htnode *htnode_create(long key, long val)
{
    htnode *n = malloc(sizeof(htnode));
    if (!n) exit(1);
    n->key = key;
    n->val = val;
    n->prev = n->next = NULL;
    return n;
}

ht *ht_create(long (*hash)(ht *, void *))
{
    ht *h = malloc(sizeof(ht));
    if (!h) exit(1);
    h->size = 0;
    h->bucket = 4;
    h->slot = malloc(sizeof(htnode *) * h->bucket);
    for (int i = 0; i < h->bucket; i++)
        h->slot[i] = NULL;
    h->hash = hash;
    return h;
}

int ht_need_resize(ht *h)
{
    if (!h)
        return 0;
    
    return h->size * 1.0 / h->bucket > 8;    
}

static void ht_insert_not_resize(ht *h, long key, long val)
{
    int idx = h->hash(h, (void *)key);

    htnode *head = h->slot[idx];
    if (!head) {
        h->slot[idx] = htnode_create(key, val);
        h->size++;
        return;
    }
    
    htnode *n = htnode_create(key, val);
    n->next = head;
    head->prev = n;
    h->slot[idx] = n;
    h->size++;
}

void ht_resize(ht *h)
{
    if (!h)
        return;

    int old_bucket = h->bucket;
    /* h->bucket = ht_next_prim(h); */
    h->bucket *= 2;
    h->size = 0;
    htnode **new = malloc(sizeof(htnode *) * h->bucket);
    for (int i = 0; i < h->bucket; i++)
        new[i] = NULL;
    htnode **old = h->slot;
    h->slot = new;

    htnode *head = NULL;;
    for (int i = 0; i < old_bucket; i++) {
        if (!(head = old[i]))
            continue;

        for (htnode *cur = head; cur; cur = cur->next)  {
            ht_insert_not_resize(h, cur->key, cur->val);
            if (cur->prev)
                free(cur->prev);
        }
    }
    free(old);
}


void ht_insert(ht *h, long key, long val)
{
    if (ht_need_resize(h)) 
        ht_resize(h);

    int idx = h->hash(h, (void *)key);

    htnode *head = h->slot[idx];
    if (!head) {
        h->slot[idx] = htnode_create(key, val);
        h->size++;
        return;
    }
    
    htnode *n = htnode_create(key, val);
    n->next = head;
    head->prev = n;
    h->slot[idx] = n;
    h->size++;
}

long ht_get(ht *h, long key)
{
    if (!h || ht_empty(h))
        return -1;

    int idx = h->hash(h, (void *)key);
    for (htnode *cur = h->slot[idx]; cur; cur = cur->next)
        if (cur->key == key)
            return cur->val;
    return -1;
}
int ht_empty(ht *h)
{
    return !h || h->size <= 0;
}

void ht_print(ht *h)
{
    printf("--------------------------\n");
    printf("size = %d bucket = %d\n", h->size, h->bucket);
    for (int i = 0; i < h->bucket; i++)  {
        if (!h->slot[i]) {
            printf("-\n");
            continue;
        }
        for (htnode *cur = h->slot[i]; cur; cur = cur->next)
            printf("{%ld %ld} ", cur->key, cur->val);
        printf("\n");
    }
    printf("--------------------------\n");
}

deque *deque_create(void)
{
    deque *d = malloc(sizeof(deque));
    if (!d) exit(1);
    d->size = 0;
    d->header = d->tailer = NULL;
    return d; 
}
void deque_push_back(deque *d, long val)
{
    if (!d) 
        return;

    deque_node *n = deque_node_create(val);
    if (d->tailer) {
        d->tailer->next = n;
        n->prev = d->tailer;
    }
    d->tailer = n;
    if (!d->header)
        d->header = n;
    d->size++;
}
void deque_push_front(deque *d, long val)
{
    if (!d)
        return;

    deque_node *n = deque_node_create(val);
    if (d->header) {
        n->next = d->header;
        d->header->prev = n;
    }
    d->header = n;
    if (!d->tailer) 
        d->tailer = n;
    d->size++;
}
long deque_pop_back(deque *d)
{
   if (!d)
      return -1;

   if (deque_empty(d))
       return -1;

   long tmp = d->tailer->val;
   deque_node *todel = d->tailer;
   d->tailer = d->tailer->prev;
   free(todel);
   if (!d->tailer)
       d->header = NULL;
   else
       d->tailer->next = NULL;
    d->size--;
    return tmp;
}
long deque_pop_front(deque *d)
{
    if (!d)
        return -1;

    if (deque_empty(d))
        return -1;

   long tmp = d->header->val;
   deque_node *todel = d->header;
   d->header = d->header->next;
   free(todel);
   if (!d->header)
       d->tailer = NULL;
   else
       d->header->prev = NULL;
    d->size--;
    return tmp;

}
long deque_front(deque *d)
{
    if (!d)
        return -1;

    if (deque_empty(d))
        return -1;

    return d->header->val;
}
long deque_back(deque *d)
{
    if (!d)
        return -1;

    if (deque_empty(d))
        return -1;

    return d->tailer->val;
}
int deque_empty(deque *d)
{
    return !d || d->size <= 0;
}
void deque_print_front(deque *d)
{
    if (!d || deque_empty(d))
        return;     

    printf("----------------------------\n");
    printf("size = %d\n", d->size);
    printf("header -> ");
    for (deque_node *cur = d->header; cur; cur = cur->next)
        printf("%-3ld", cur->val);
    printf(" <- tailer\n");
    printf("----------------------------\n");
}
void deque_print_back(deque *d)
{
    if (!d || deque_empty(d))
        return;     

    printf("----------------------------\n");
    printf("size = %d\n", d->size);
    printf("tailer -> ");
    for (deque_node *cur = d->tailer; cur; cur = cur->prev)
        printf("%-3ld", cur->val);
    printf(" <- header\n");
    printf("----------------------------\n");
}

void deque_print_front_funptr(deque *d, void(*fun)(long))
{
    if (!d || deque_empty(d))
        return;     

    printf("----------------------------\n");
    printf("size = %d\n", d->size);
    printf("header -> ");
    for (deque_node *cur = d->header; cur; cur = cur->next)
        fun(cur->val);
    printf(" <- tailer\n");
    printf("----------------------------\n");
}

void deque_print_back_funptr(deque *d, void(*fun)(long))
{
    if (!d || deque_empty(d))
        return;     

    printf("----------------------------\n");
    printf("size = %d\n", d->size);
    printf("tailer -> ");
    for (deque_node *cur = d->tailer; cur; cur = cur->prev)
        fun(cur->val);
    printf(" <- header\n");
    printf("----------------------------\n");
}

void deque_release(deque **dd)
{
    if (!dd || !*dd)
        return;

    deque *d = *dd;

    while (!deque_empty(d))
        deque_pop_back(d);

    free(d);
    *dd = NULL;
}

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

void deque_test(void)
{
    deque *d = deque_create();
    for (int i = 0; i < 10; i++)
        deque_push_back(d, i);

    deque_print_front(d);
    deque_print_back(d);

    while (!deque_empty(d))
        deque_pop_back(d);

    deque_release(&d);
}


long ht_hash(ht *h, void *key)
{
    long k = (long)key;
    return k % h->bucket;
}
void ht_test(void)
{
    setbuf(stdout, NULL);
    ht *h = ht_create(ht_hash);
    int size = 300;
    for (int i = 0; i < size; i++)
        ht_insert(h, randWithRange(1, 100), 0);
    ht_print(h);
}

int main(int argc, char *argv[])
{
    ht_test();
}
