#include "ds.h" 

#define HT_MIN_BUCKET 5
#define HT_EXPAND_BOUND 7
#define HT_SHRINK_BOUND 3

treenode *treenode_create(long val)
{
    treenode *n = malloc(sizeof(treenode));
    if (!n) exit(1);
    n->val = val;
    n->left = n->right = NULL;
    return n;
}

void in_traverse(treenode *root)
{
    if (!root)
        return;

    in_traverse(root->left);
    printf("%-3ld", root->val);
    in_traverse(root->right);
}

void pre_traverse(treenode *root)
{
    if (!root)
        return;

    printf("%-3ld", root->val);
    pre_traverse(root->left);
    pre_traverse(root->right);
}

void post_traverse(treenode *root)
{
    if (!root)
        return;

    post_traverse(root->left);
    post_traverse(root->right);
    printf("%-3ld", root->val);
}

void in_print(treenode *root)
{
    printf("in   -> ");
    in_traverse(root);
    printf("\n");
}

void pre_print(treenode *root)
{
    printf("prev -> ");
    pre_traverse(root);
    printf("\n");
}

void post_print(treenode *root)
{
    printf("post -> ");
    post_traverse(root);
    printf("\n");
}

static int ht_is_prime(long num)
{
    if (num <= 3) 
        return num > 1;

    if (num % 6 != 1 && num % 6 != 5) 
        return 0;

    int s = (int)sqrt(num);
    for (int i = 5; i <= s; i += 6) 
        if (num % i == 0 || num % (i + 2) == 0) 
            return 0; return 1;
} 

static int ht_need_expand(ht *h)
{
    if (!h)
        return 0;
    
    return h->size / h->bucket > HT_EXPAND_BOUND;
}

static int ht_need_shrink(ht *h)
{
    if (!h)
        return 0;
    
    return h->bucket > HT_MIN_BUCKET && h->size / h->bucket < HT_SHRINK_BOUND;
}

static void ht_insert_internal(ht *h, long key, long val)
{
    unsigned long idx = h->hash(key);
    idx %= h->bucket;

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

static void ht_resize(ht *h, int shrink)
{
    if (!h)
        return;

    int old_bucket = h->bucket;

    if (shrink) {
        h->bucket >>= 1;
        int i = h->bucket;
        while (!ht_is_prime(i))
            i--;
        h->bucket = i;
        if (h->bucket < HT_MIN_BUCKET)
            h->bucket = HT_MIN_BUCKET;
    } else {
        h->bucket <<= 1;
        int i = h->bucket;
        while (!ht_is_prime(i))
            i++;
        h->bucket = i;
    }

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
            ht_insert_internal(h, cur->key, cur->val);
            if (cur->prev)
                free(cur->prev);
        }
    }
    free(old);
}

htnode *htnode_create(long key, long val)
{
    htnode *n = malloc(sizeof(htnode));
    if (!n) exit(1);
    n->key = key;
    n->val = val;
    n->prev = n->next = NULL;
    return n;
}

ht *ht_create(long (*hash)(long))
{
    ht *h = malloc(sizeof(ht));
    if (!h) exit(1);
    h->size = 0;
    h->bucket = HT_MIN_BUCKET;
    h->slot = malloc(sizeof(htnode *) * h->bucket);
    for (int i = 0; i < h->bucket; i++)
        h->slot[i] = NULL;
    h->hash = hash;
    return h;
}

void ht_insert(ht *h, long key, long val)
{
    if (ht_need_expand(h)) 
        ht_resize(h, 0);

    unsigned long idx = h->hash(key);
    idx %= h->bucket;

    htnode *head = h->slot[idx];
    if (!head) {
        h->slot[idx] = htnode_create(key, val);
        h->size++;
        return;
    }

    for (htnode *cur = head; cur; cur = cur->next) {
        if (cur->key == key)  {
            cur->val = val;
            return;
        }
    }

    htnode *n = htnode_create(key, val);
    n->next = head;
    head->prev = n;
    h->slot[idx] = n;
    h->size++;
}

void ht_remove(ht *h, long key)
{
    if (!h || ht_empty(h))
        return;

    unsigned long idx = h->hash(key);
    idx %= h->bucket;
    int find = 0;
    for (htnode *cur = h->slot[idx]; cur; cur = cur->next) {
        if (cur->key == key) {
            find = 1;
            if (cur->prev) {
                cur->prev->next = cur->next;
                if (cur->next)
                    cur->next->prev = cur->prev;
                free(cur);
                h->size--;
            } else {
                h->slot[idx] = cur->next;
                if (cur->next) 
                    cur->next->prev = NULL;
                h->size--;
            }
            break;
        }
    }

    if (find && ht_need_shrink(h))
        ht_resize(h, 1);
    return;
}

long ht_get(ht *h, long key)
{
    if (!h || ht_empty(h))
        return 0;

    unsigned long idx = h->hash(key);
    idx %= h->bucket;
    for (htnode *cur = h->slot[idx]; cur; cur = cur->next)
        if (cur->key == key)
            return cur->val;
    return 0;
}
int ht_empty(ht *h)
{
    return !h || h->size <= 0;
}

void ht_print_funptr(ht *h, void (*print_ptr)(htnode *))
{
    printf("--------------------------\n");
    printf("size = %d bucket = %d\n", h->size, h->bucket);
    for (int i = 0; i < h->bucket; i++)  {
        if (!h->slot[i]) {
            printf("-\n");
            continue;
        }
        for (htnode *cur = h->slot[i]; cur; cur = cur->next)
            print_ptr(cur);
        printf("\n");
    }
    printf("--------------------------\n");
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

void ht_release(ht **hh)
{
    if (!hh || !*hh)
        return;
    ht *h = *hh;
    for (int i = 0; i < h->bucket; i++) {
        htnode *n = h->slot[i];
        if (!n) continue;
        while (1) {
            if (!n->next) {
                free(n);
                break;
            }
            free((n = n->next)->prev);
        }
    }
    free(h->slot);
    *hh = NULL;
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
      return 0;

   if (deque_empty(d))
       return 0;

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
        return 0;

    if (deque_empty(d))
        return 0;

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
        return 0;

    if (deque_empty(d))
        return 0;

    return d->header->val;
}
long deque_back(deque *d)
{
    if (!d)
        return 0;

    if (deque_empty(d))
        return 0;

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
        return 0;

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

int stack_size(stack *s)
{
    if (!s)
        return 0;
    return s->size;
}

long stack_peek(stack *s)
{
    if (stack_empty(s))
        return 0;
    return s->top->val;
}

long stack_pop(stack *s)
{
    if (stack_empty(s))
        return 0;

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

void stack_print_s(stack *s)
{
    if (!s)
        return;

    for (stknode *cur = s->top; cur; cur = cur->next)
        printf("%-3ld", cur->val);
    printf("\n");
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

lnode *lnode_create(long val)
{
    lnode *n = malloc(sizeof(lnode));
    if (!n) exit(1);
    n->next = NULL;
    n->val = val;
    return n;
}
void list_insert(lnode **head, long val)
{
    if (!head)
        return;

    lnode *n = lnode_create(val);
    if (!*head) {
        *head = n;
        return;
    }
    lnode *last = *head;
    while (last->next)
        last = last->next;
    last->next = n;
}

lnode *list_create_with_arr(int *arr, int size)
{
    if (!arr || size <= 0)
        return NULL;

    lnode *head = NULL;
    lnode *last = NULL;
    for (int i = 0; i < size; i++) {
        lnode *n = lnode_create(arr[i]);
        if (!head) {
            head = n;
            last = n;
        } else {
            last->next = n;
            last = n;
        }
    }  
    return head;
}

lnode *list_create(int size)
{
    if (size <= 0)
        return NULL;

    lnode *head = NULL;
    while (size--)
        list_insert(&head, randWithRange(0, 20));
    return head;
}
lnode *list_loop_create(int size)
{
    if (size <= 0)
        return NULL;

    lnode *head = NULL;
    while (size--)
        list_insert(&head, randWithRange(0, 20));
    lnode *last = head;
    while (last->next)
        last = last->next;
    last->next = head;
    return head;
}
void list_print(lnode *head)
{
    if (!head)
        return;

    lnode *rawhead = head;
    while (head) {
        printf("%-3ld", head->val);
        head = head->next;
        if (head == rawhead)
            break;
    }
    printf("\n");
}
void list_release(lnode **head)
{
    if (!head || !*head)
        return;

    lnode *sentinel = lnode_create(1);
    sentinel->next = *head;
    while (sentinel->next) {
        lnode *tmp = sentinel->next;
        sentinel = sentinel->next;
        free(tmp);
    }

    free(sentinel);
    *head = NULL;
}

dlnode *dlnode_create(long val)
{
    dlnode *n = malloc(sizeof(dlnode));
    if (!n) exit(1);
    n->next = n->prev = NULL;
    n->val = val;
    return n;
}
void dlist_insert(dlnode **head, long val)
{
    if (!head)
        return;

    dlnode *n = dlnode_create(val);
    if (!*head) {
        *head = n;
        return;
    }
    dlnode *last = *head;
    while (last->next)
        last = last->next;
    last->next = n;
    n->prev = last;
}

dlnode *dlist_create(int size)
{
    if (size <= 0)
        return NULL;

    dlnode *head = NULL;
    while (size--)
        dlist_insert(&head, randWithRange(0, 20));
    return head;
}

dlnode *dlist_create_with_arr(int *arr, int size)
{
    if (!arr || size <= 0)
        return NULL;

    dlnode *head = NULL;
    dlnode *last = NULL;
    for (int i = 0; i < size; i++) {
        dlnode *n = dlnode_create(arr[i]);
        if (!head) {
            head = n;
            last = n;
        } else {
            last->next = n;
            n->prev = last;
            last = n;
        }
    }  
    return head;
    
}

void dlist_print_front(dlnode *head)
{
    for (dlnode *cur = head; cur; cur = cur->next)
        printf("%-3ld", cur->val);
    printf("\n");
}

void dlist_print_back(dlnode *head)
{
    dlnode *tail = head;
    while (tail->next)
       tail = tail->next;
   for (dlnode *cur = tail; cur; cur = cur->prev)
        printf("%-3ld", cur->val);
    printf("\n");
}

void dlist_release(dlnode **head)
{
    if (!head || !*head)
        return;

    dlnode *cur = *head;
    while (1) {
        if (!cur->next) {
            free(cur);
            break;
        }
        free((cur = cur->next)->prev);
    }
    *head = NULL;
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
    usleep(17);
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

long ht_hash(long key)
{
    return key;
}

void ht_test(void)
{
    setbuf(stdout, NULL);
    ht *h = ht_create(ht_hash);

    int size = 10000000;
    int lo = 1, hi = 10000000;

    srand((unsigned)time(NULL));

    long beg = getCurTime();
    for (int i = 0; i < size; i++)
        ht_insert(h, rand() % (hi - lo) + lo, 0);
    long end = getCurTime();
    printf("insert all elem finished, each insert cost %.3f us\n", (end - beg) * 1.0 / size); 

    int not_found = 0;
    int search_times = 100000;
    beg = getCurTime();
    for (int i = 0; i < search_times; i++)
        if (ht_get(h, rand() % (hi * 2)) < 0)
            not_found++;
    end = getCurTime();
    printf("not_found = %.3f%%, each get cost %.3f us\n", not_found * 1.0 / search_times * 100, (end - beg) * 1.0 / search_times); 

    beg = getCurTime();
    for (int i = lo; i < hi; i++)
        ht_remove(h, i);
    end = getCurTime();
    printf("remove all elem finished, each remove cost %.3f us\n", (end - beg) * 1.0 / size); 
}

/*
 * int main(int argc, char *argv[])
 * {
 *     ht_test();
 * }
 */
