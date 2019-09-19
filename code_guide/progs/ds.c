#include "ds.h" 

#define HT_MIN_BUCKET 5
#define HT_EXPAND_BOUND 7
#define HT_SHRINK_BOUND 3

/***************************** heap ************************************/
static void heap_sink(heap *h, int k)
{
    long t = h->keys[k];
    while (k * 2 <= h->size) {
        int j = k * 2;
        if (j < h->size && h->cmp(h->keys[j], h->keys[j + 1]) > 0) j++;
        if (h->cmp(t, h->keys[j]) <= 0) break;
        h->keys[k] = h->keys[j];
        k = j;
    }    
    h->keys[k] = t;
}

static void heap_swim(heap *h, int k)
{
    long t = h->keys[k];
    while (k > 1 && h->cmp(t, h->keys[k / 2]) < 0) {
        h->keys[k] = h->keys[k / 2];
        k /= 2;
    }
    h->keys[k] = t;
}

static void heap_resize(heap *h, int size)
{
    long *oldk = h->keys;    
    long *newk = malloc(sizeof(*h->keys) * size);
    memcpy(newk + 1, oldk + 1, sizeof(*h->keys) * h->size);
    free(oldk);
    h->keys = newk;
}

static int __heap_cmp(long a, long b)
{
    if (a == b) return 0;
    return a > b ? 1 : -1;
}

heap *heap_create_(int (*cmp)(long, long))
{
    heap *h = malloc(sizeof(heap));
    h->size = 0;
    h->cap = 8;    
    h->keys = malloc(sizeof(*h->keys) * h->cap);
    h->cmp = cmp;
    return h;
}

heap *heap_create()
{
    return heap_create_(__heap_cmp);
}

long heap_pop(heap *h)
{
    if (!h) {
        fprintf(stderr, "null h\n");
        exit(1);
    }
        
    long t = h->keys[1];
    h->keys[1] = h->keys[h->size];
    h->size--;
    heap_sink(h, 1);
    return t;
}

int heap_empty(heap *h)
{
    if (!h) {
        fprintf(stderr, "null h\n");
        exit(1);
    }
    return h->size <= 0;
}

long heap_peek(heap *h)
{
    if (!h) {
        fprintf(stderr, "null h\n");
        exit(1);
    }
    if (heap_empty(h))
       return 0; 

    return h->keys[1];
}

void heap_insert(heap *h, long key)
{
    if (!h) {
        fprintf(stderr, "null h\n");
        exit(1);
    }
    
    if (h->size == h->cap)
        heap_resize(h, h->size * 2);

    h->keys[++h->size] = key;
    heap_swim(h, h->size);
}

void heap_release(heap **h)
{
    if (!h || !*h)
        return;

    heap *hh = *h;
    free(hh->keys);
    free(hh);
    *h = NULL;
}
/******************************************************************************/


/***************************** binary tree ************************************/
int *to_pre_arr_(treenode *root)
{
    int size = tree_size(root);
    int *pre = (int *)malloc(sizeof(int) * size);
    int pre_size = 0;

    stack *s1 = stack_create();
#define PUSH(s, x) stack_push(s, (long)(x))
#define POP(s) ((treenode *)stack_pop(s))
    PUSH(s1, root);
    while (!stack_empty(s1)) {
        root = POP(s1);
        while (root) {
            pre[pre_size++] = root->val;
            if (root->right)
                PUSH(s1, root->right);
            root = root->left;
        }
    }
    stack_release(&s1);
    return pre;
}

int *to_in_arr_(treenode *root)
{
    int size = tree_size(root);
    int *in = (int *)malloc(sizeof(int) * size);
    int in_size = 0;

    stack *s1 = stack_create();

#define PUSH(s, x) stack_push(s, (long)(x))
#define POP(s) ((treenode *)stack_pop(s))
    while (!stack_empty(s1) || root) {
        if (root) {
            PUSH(s1, root);
            root = root->left;
        } else {
            root = POP(s1);
            in[in_size++] = root->val;
            root = root->right;
        }
    }
    stack_release(&s1);
    return in;
}

int *to_post_arr_(treenode *root)
{
    int size = tree_size(root);
    int *post = (int *)malloc(sizeof(int) * size);
    int post_size = size - 1;

    stack *s1 = stack_create();

#define PUSH(s, x) stack_push(s, (long)(x))
#define POP(s) ((treenode *)stack_pop(s))
    PUSH(s1, root);
    while (!stack_empty(s1)) {
        root = POP(s1);
        post[post_size--] = root->val;
        if (root->left)
            PUSH(s1, root->left);
        if (root->right)
            PUSH(s1, root->right);
    }
    stack_release(&s1);
    return post;
}

long *to_pre_arr(treenode *root)
{
    int size = tree_size(root);
    long *pre = (long *)malloc(sizeof(long) * size);
    int pre_size = 0;

    stack *s1 = stack_create();
#define PUSH(s, x) stack_push(s, (long)(x))
#define POP(s) ((treenode *)stack_pop(s))
    PUSH(s1, root);
    while (!stack_empty(s1)) {
        root = POP(s1);
        while (root) {
            pre[pre_size++] = root->val;
            if (root->right)
                PUSH(s1, root->right);
            root = root->left;
        }
    }
    stack_release(&s1);
    return pre;
}

long *to_in_arr(treenode *root)
{
    int size = tree_size(root);
    long *in = (long *)malloc(sizeof(long) * size);
    int in_size = 0;

    stack *s1 = stack_create();

#define PUSH(s, x) stack_push(s, (long)(x))
#define POP(s) ((treenode *)stack_pop(s))
    while (!stack_empty(s1) || root) {
        if (root) {
            PUSH(s1, root);
            root = root->left;
        } else {
            root = POP(s1);
            in[in_size++] = root->val;
            root = root->right;
        }
    }
    stack_release(&s1);
    return in;
}

long *to_post_arr(treenode *root)
{
    int size = tree_size(root);
    long *post = (long *)malloc(sizeof(long) * size);
    int post_size = size - 1;

    stack *s1 = stack_create();

#define PUSH(s, x) stack_push(s, (long)(x))
#define POP(s) ((treenode *)stack_pop(s))
    PUSH(s1, root);
    while (!stack_empty(s1)) {
        root = POP(s1);
        post[post_size--] = root->val;
        if (root->left)
            PUSH(s1, root->left);
        if (root->right)
            PUSH(s1, root->right);
    }
    stack_release(&s1);
    return post;
}

void in_traverse_funptr(treenode *root, void(*trav)(long))
{
    if (!root)
        return;

    in_traverse_funptr(root->left, trav);
    trav(root->val);
    in_traverse_funptr(root->right, trav);
}
void pre_traverse_funptr(treenode *root, void(*trav)(long))
{
    if (!root)
        return;

    trav(root->val);
    pre_traverse_funptr(root->left, trav);
    pre_traverse_funptr(root->right, trav);
}
void post_traverse_funptr(treenode *root, void(*trav)(long))
{
    if (!root)
        return;

    post_traverse_funptr(root->left, trav);
    post_traverse_funptr(root->right, trav);
    trav(root->val);
}

treenode *bst_create_with_arr(int *arr, int size)
{
    if (size <= 0 || !arr)
        return NULL;

    treenode *root = NULL;
    for (int i = 0; i < size; i++)
        bst_insert(&root, arr[i]);
    return root;
}

treenode *cbt_create(int size)
{
    if (size <= 0)
        return NULL;

    int *arr = NULL;
    while (1) {
        arr = arrayWithRange(size, 0, size * 2);
        if (!arrayHasDup(arr, size)) 
            break;
        free(arr);
    }
    treenode *head = cbt_create_with_arr(arr, size);
    free(arr);
    return head;
}

treenode *cbt_create_with_arr(int *arr, int size)
{
    queue *q = queue_create();
#define ENQUEUE(q, x) queue_enqueue(q, (long)(x))
#define DEQUEUE(q) ((treenode *)queue_dequeue(q))
#define N(x) treenode_create(x)
    int i = 0;
    treenode *head = N(arr[i++]);
    ENQUEUE(q, head);
    size--;
    while (size) {
        treenode *cur = DEQUEUE(q);
        cur->left = N(arr[i++]);
        if (--size <= 0)
            break;
        cur->right = N(arr[i++]);
        if (--size <= 0)
            break;
        ENQUEUE(q, cur->left);
        ENQUEUE(q, cur->right);
    }
    queue_release(&q);
    return head;
#undef ENQUEUE
#undef DEQUEUE
#undef N
}

treenode* bst_create(int size)
{
    if (size <= 0)
        return NULL;

    int *arr = NULL;
    while (1) {
        arr = arrayWithRange(size, 0, size * 2);
        if (!arrayHasDup(arr, size)) 
            break;
        free(arr);
    }
    treenode *root = NULL;
    for (int i = 0; i < size; i++)
        bst_insert(&root, arr[i]);
    free(arr);
    return root;
}

treenode *tree_kth_node(treenode *root, int k)
{
    if (k < 0 || !root)
        return NULL;

    treenode *target = NULL;
    stack *s = stack_create();
#define PUSH(s, x) stack_push(s, (long)(x))
#define POP(s) ((treenode *)stack_pop(s))
    while (!stack_empty(s) || root) {
        if (root) {
            PUSH(s, root);
            root = root->left;
        } else {
            root = POP(s);
            if (k-- <= 0) {
                target = root;
                break;
            }
            root = root->right;
        }
    }
    stack_release(&s);
    return target;
}

void tree_random_twonodes(treenode *root, treenode **n1, treenode **n2)
{
    if (!root)
        return;

    int size = tree_size(root);
    int k = randWithRange(0, size);
    int m = randWithRange(0, size);
    if (n1)
        *n1 = tree_kth_node(root, k);
    if (n2)
        *n2 = tree_kth_node(root, m);
}

void bst_insert(treenode **root, long val)
{
    treenode *n = treenode_create(val);
    if (!*root) {
        *root = n;
        return;
    }

    treenode *parent = NULL, *cur = *root;
    while (cur) {
        if (cur->val == val) {
            free(n);
            return;
        }
        parent = cur;
        if (val < cur->val)
            cur = cur->left;
        else
            cur = cur->right;
    }
    if (val < parent->val)
        parent->left = n;
    else
        parent->right = n;
    n->parent = parent;
}

treenode *tree_clone(treenode *root)
{
    if (!root)
        return NULL;

    treenode *copy = treenode_create(root->val);
    copy->left = tree_clone(root->left);
    copy->right = tree_clone(root->right);
    return copy;
}

void bst_remove(treenode **root, long val)
{
    
}

static void _tree_release(treenode *root)
{
    if (!root)
        return;

    _tree_release(root->left);
    _tree_release(root->right);
    free(root);
}

void tree_release(treenode **root)
{
    _tree_release(*root);
    *root = NULL;
}

int tree_size(treenode *root)
{
    if (!root)
        return 0;

    return 1 + tree_size(root->left) + tree_size(root->right);
}

int tree_height(treenode *root)
{
    if (!root)
        return 0;

    int left = tree_height(root->left);
    int right = tree_height(root->right);
    return 1 + (left > right ? left : right); 
}

void tree_draw(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }

    queue *q = queue_create();

#define ENQUEUE(q, x) queue_enqueue(q, (long)(x))
#define DEQUEUE(q)  ((treenode *)queue_dequeue(q))

#define CHAR_NULL ' ' /* null 节点用什么符号来表示 */
#define CHAR_FILL ' ' /* 数字不足宽度用什么符号来填充 */
#define CHAR_SPACE ' ' /* 不同的节点间用什么符号来分隔 */
#define NUM_WIDTH 3  /* 数字的最大宽度，比如 12 的宽度是 2，999 的宽度是 3 */

    ENQUEUE(q, root);
    int h = tree_height(root);
    int s = tree_size(root);
    int slots = pow(2, h) - 1;
    int cur_level = 1;
    int next_level = 0;
    char *buf = (char *)malloc(10 << 20);
    if (!buf) exit(1);
    long buflen = 10 << 20;
    int len = 0;
    int numwidth = NUM_WIDTH; /* 999 .9. 90. */

    int slotwidth = numwidth; /* 桶宽度和数字宽度要一样 */
    printf("--------------- num_width=%d, height=%d, size=%d -----------------\n", numwidth, h, s);

    int cur_height = 1;
    while (cur_height <= h) {
        treenode *n = DEQUEUE(q);
        ENQUEUE(q, !n ? NULL : n->left);
        ENQUEUE(q, !n ? NULL : n->right);
        next_level += 2;

        int nslot = slots / pow(2, cur_height); 
        len = 0;

        long num = n ? n->val : 0;
        int width = n ? get_num_width(num) : 1;
        int left_nfill = (numwidth - width) / 2;
        int right_nfill = numwidth - width - left_nfill;

        // 该行左边填充
        for (int i = 0; i < nslot * slotwidth; i++)
            buf[i] = CHAR_SPACE;
        len += nslot * slotwidth;

        // 数字左边填充空格
        for (int i = 0; i < left_nfill; i++)
            buf[i + len] = CHAR_FILL;
        len += left_nfill;

        if (n)
            len += snprintf(buf + len, buflen - len, "%ld", num);
        else
            len += snprintf(buf + len, buflen - len, "%c", CHAR_NULL);

        // 数字右边填充空格
        for (int i = 0; i < right_nfill; i++)
            buf[i + len] = CHAR_FILL;
        len += right_nfill;

        // 该行右边填充
        for (int i = 0; i < nslot * slotwidth; i++)
            buf[i + len] = CHAR_SPACE;
        len += nslot * slotwidth;

        for (int i = 0; i < 1 * slotwidth; i++)
            buf[i + len] = CHAR_SPACE;
        len += 1 * slotwidth;

        buf[len] = 0;
        printf("%s", buf);

        if (--cur_level == 0) {
            cur_level = next_level;
            next_level = 0;
            printf("\n\n");
            cur_height++;
        }
    }
    printf("---------------------------------------------------------------\n");
    queue_release(&q);
    free(buf);
}

void bst_test(void)
{
    int size = randWithRange(1, 10);
    printf("size=%d\n", size);
    treenode *root = bst_create(size);
    pre_print(root);
    in_print(root);
    post_print(root);
}

treenode *treenode_create(long val)
{
    treenode *n = (treenode *)malloc(sizeof(treenode));
    if (!n) exit(1);
    n->height = 0;
    n->size = 1;
    n->val = val;
    n->left = n->right = NULL;
    n->parent = NULL;
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
    if (!root) {
        printf("null\n");
        return;
    }
    printf("in   -> ");
    in_traverse(root);
    printf("\n");
}

void pre_print(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }
    printf("prev -> ");
    pre_traverse(root);
    printf("\n");
}

void post_print(treenode *root)
{
    if (!root) {
        printf("null\n");
        return;
    }
    printf("post -> ");
    post_traverse(root);
    printf("\n");
}
/******************************************************************************/

/********************************** math **************************************/
int get_num_width(int num)
{
    int sign = num < 0;
    int width = 1;
    while (num /= 10)
        width++;
    return width + sign;
}

int get_width_num(int w)
{
    int i = 0;
    while (w--)
        i = i * 10 + 9;
    return i;
}
/******************************************************************************/

/********************************** hash table ********************************/
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
    htnode **newbucket = (htnode **)malloc(sizeof(htnode *) * h->bucket);
    for (int i = 0; i < h->bucket; i++)
        newbucket[i] = NULL;
    htnode **old = h->slot;
    h->slot = newbucket;

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
    htnode *n = (htnode *)malloc(sizeof(htnode));
    if (!n) exit(1);
    n->key = key;
    n->val = val;
    n->prev = n->next = NULL;
    return n;
}

void ht_clear(ht *h)
{
    if (!h)
        return;
   
    for (int i = 0; i < h->bucket; i++) {
        htnode *n = h->slot[i];
        if (!n)
            continue;
        while (1) {
            if (!n->next) {
                free(n);
                break;
            }
            free((n = n->next)->prev);
        }
    }     
    h->size = 0;
    free(h->slot);
    h->bucket = HT_MIN_BUCKET;
    h->slot = (htnode **)malloc(sizeof(htnode *) * h->bucket);
    for (int i = 0; i < h->bucket; i++)
        h->slot[i] = NULL;
}

ht *ht_create(void)
{
    ht *h = (ht *)malloc(sizeof(ht));
    if (!h) exit(1);
    h->size = 0;
    h->bucket = HT_MIN_BUCKET;
    h->slot = (htnode **)malloc(sizeof(htnode *) * h->bucket);
    for (int i = 0; i < h->bucket; i++)
        h->slot[i] = NULL;
    h->hash = _hash;
    h->eq = _eq;
    return h;
}

ht *ht_create_(long (*hash)(long), int(*eq)(long, long))
{
    ht *h = (ht *)malloc(sizeof(ht));
    if (!h) exit(1);
    h->size = 0;
    h->bucket = HT_MIN_BUCKET;
    h->slot = (htnode **)malloc(sizeof(htnode *) * h->bucket);
    for (int i = 0; i < h->bucket; i++)
        h->slot[i] = NULL;
    h->hash = hash;
    h->eq = eq;
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
        if (h->eq(cur->key, key))  {
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
        if (h->eq(cur->key, key)) {
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
        if (h->eq(cur->key, key))
            return cur->val;
    return 0;
}

int ht_contain(ht *h, long key)
{
    if (!h || ht_empty(h))
        return 0;
    
    unsigned long idx = h->hash(key);
    idx %= h->bucket;
    for (htnode *cur = h->slot[idx]; cur; cur = cur->next)
        if (h->eq(cur->key, key))
            return 1;
    return 0;
}

int ht_empty(ht *h)
{
    return !h || h->size <= 0;
}

void ht_print_funptr(ht *h, void (*print_ptr)(long key, long value))
{
    if (!h) {
        printf("null\n");
        return;
    }
    printf("--------------------------\n");
    printf("size = %d bucket = %d\n", h->size, h->bucket);
    for (int i = 0; i < h->bucket; i++)  {
        if (!h->slot[i]) {
            printf("-\n");
            continue;
        }
        for (htnode *cur = h->slot[i]; cur; cur = cur->next)
            print_ptr(cur->key, cur->val);
        printf("\n");
    }
    printf("--------------------------\n");
}
void ht_print(ht *h)
{
    if (!h) {
        printf("null\n");
        return;
    }
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
/******************************************************************************/


/********************************* deque **************************************/
deque *deque_create(void)
{
    deque *d = (deque *)malloc(sizeof(deque));
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
    if (!d) {
        printf("null\n");
        return;
    }
    if (deque_empty(d)) {
        printf("empty\n");
        return;
    }

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
    if (!d) {
        printf("null\n");
        return;
    }
    if (deque_empty(d)) {
        printf("empty\n");
        return;
    }

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
    if (!d) {
        printf("null\n");
        return;
    }
    if (deque_empty(d)) {
        printf("empty\n");
        return;
    }

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
    if (!d) {
        printf("null\n");
        return;
    }
    if (deque_empty(d)) {
        printf("empty\n");
        return;
    }

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
    deque_node *n = (deque_node *)malloc(sizeof(deque_node));
    if (!n) exit(1);
    n->val = val;
    n->next = NULL;
    n->prev = NULL;
    return n;
}
/******************************************************************************/

/********************************* queue **************************************/
queue *queue_create(void)
{
    queue *q = (queue *)malloc(sizeof(queue));
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

void queue_release(queue **q)
{
    if (!q || !*q)
        return;

    while (!queue_empty(*q))
        queue_dequeue(*q);
    free(*q);
    *q = NULL;
}

void queue_print(queue *q)
{
    if (!q) {
        printf("null\n");
        return;
    }

    if (queue_empty(q)) {
        printf("empty\n");
        return;
    }

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

/******************************************************************************/

/********************************* stack **************************************/

stknode *stknode_create(long val)
{
    stknode *n = (stknode *)malloc(sizeof(stknode));
    if (!n) exit(1);
    n->val = val;
    n->next = NULL;
    return n;
}

stack *stack_create(void)
{
    stack *s = (stack *)malloc(sizeof(stack));
    if (!s) exit(1);
    s->size = 0;
    s->top = NULL;
    return s;
}

void stack_clear(stack *s)
{
    if (!s)
        return;

    while (!stack_empty(s))
        stack_pop(s);
}

void stack_copy(stack *dst, stack *src)
{
    stack_clear(dst);
    stknode *last = NULL;
    for (stknode *n = src->top; n; n = n->next) {
        stknode *newn = stknode_create(n->val);
        if (!last) {
            dst->top = newn;
            last = newn;
        } else {
            last->next = newn;
            last = newn;
        }
    }
    dst->size = src->size;
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

long stack_pop_bottom(stack *s)
{
    if (stack_empty(s))
        return 0;

    stknode *prev = NULL;
    for (stknode *cur = s->top; cur->next; cur = cur->next)
        prev = cur;

    if (!prev) {
        stknode *tofree = s->top;
        long v = tofree->val;
        free(tofree);
        s->size = 0;
        s->top = NULL;
        return v;
    }

    stknode *tofree = prev->next;
    long v = tofree->val;
    prev->next = NULL;
    free(tofree);
    s->size--;
    return v;
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
void stack_print_r(stack *s)
{
    if (!s) {
        printf("null\n");
        return;
    }

    if (stack_empty(s)) {
        printf("empty\n");
        return;
    }

    stack *r = stack_create();
    while (!stack_empty(s)) 
        stack_push(r, stack_pop(s));

    printf("\n-----------------------------\n");
    printf("stack size = %ld\n", r->size);
    for (stknode *cur = r->top; cur; cur = cur->next)
        printf("%-3ld", cur->val);
    printf("<- top");
    printf("\n");
    printf("-----------------------------\n");

    while (!stack_empty(r))
        stack_push(s, stack_pop(r));

    stack_release(&r);
}

void stack_print_funptr(stack *s, void(*printfun)(long val))
{
    if (!s) {
        printf("null\n");
        return;
    }

    if (stack_empty(s)) {
        printf("empty\n");
        return;
    }

    printf("\n-----------------------------\n");
    printf("stack size = %ld\n", s->size);
    printf("top -> ");
    for (stknode *cur = s->top; cur; cur = cur->next)
        if (printfun)
            printfun(cur->val);
    printf("\n");
    printf("-----------------------------\n");
}
void stack_print(stack *s)
{
    if (!s) {
        printf("null\n");
        return;
    }

    if (stack_empty(s)) {
        printf("empty\n");
        return;
    }

    printf("\n-----------------------------\n");
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
/******************************************************************************/

/********************************* list ***************************************/

lnode *lnode_create(long val)
{
    lnode *n = (lnode *)malloc(sizeof(lnode));
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

    int sz = size;
    lnode *head = NULL;
    while (size--)
        list_insert(&head, randWithRange(0, 20));

    lnode *last = head;
    while (last->next)
        last = last->next;

    lnode *tail = head;
    int r = randWithRange(0, sz);
    while (r--)
        tail = tail->next;

    last->next = tail;
    return head;
}
lnode *list_circle_create(int size)
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

void list_print_with_size(lnode *head, int size)
{
    if (!head || size <= 0) {
        printf("null\n");
        return;
    }

    while (head && size > 0) {
        printf("%-3ld", head->val);
        head = head->next;
        size--;
    }
    printf("\n");
}

void list_print(lnode *head)
{
    if (!head) {
        printf("null\n");
        return;
    }

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
/******************************************************************************/

/********************************* dual list **********************************/

dlnode *dlnode_create(long val)
{
    dlnode *n = (dlnode *)malloc(sizeof(dlnode));
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
    if (!head) {
        printf("null\n");
        return;
    }

    for (dlnode *cur = head; cur; cur = cur->next)
        printf("%-3ld", cur->val);
    printf("\n");
}

void dlist_print_back(dlnode *head)
{
    if (!head) {
        printf("null\n");
        return;
    }
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
/******************************************************************************/

/********************************* basic algorithm ****************************/

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
/******************************************************************************/

/********************************* tool **************************************/

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

void printArrayL(long *array, int size)
{
    if (!array || size <= 0) {
        printf("null\n");
        return;
    }
    printf("size=%d\n", size);
    for (int i = 0; i < size; i++)
        printf("%-4ld", array[i]);
    printf("\n");
}
void printArray(int *array, int size)
{
    if (!array || size <= 0) {
        printf("null\n");
        return;
    }
    printf("size=%d\n", size);
    for (int i = 0; i < size; i++)
        printf("%-4d", array[i]);
    printf("\n");
}

int *copyArray(int *arr, int size)
{
    int *copy = (int *)malloc(sizeof(int) * size);
    memcpy(copy, arr, sizeof(int) * size);
    return copy;
}

int *array(int size)
{
    int *array = (int *)malloc(sizeof(int) * size);
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
    int *array = (int *)malloc(sizeof(int) * size);
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

static long __normal_hash(long key)
{
    return key;
}

int arrayHasDup(int *arr, int size)
{
    if (!arr || size <= 1)
        return 0;
    int has_dup = 0;
    ht *h = ht_create();
    for (int i = 0; i < size; i++) {
        if (ht_get(h, arr[i])) {
            has_dup = 1;
            break;
        } 
        ht_insert(h, arr[i], 1);
    }
    ht_release(&h);
    return has_dup;
}

int *arrayNoDupWithRange(int size, int lo, int hi)
{
    if (hi - lo < size) {
        printf("hi - lo = %d must greater or equal than size=%d\n", hi - lo, size);
        return NULL;
    }
    int *arr = (int *)malloc(sizeof(int) * (hi - lo));
    for (int i = lo; i < hi; i++)
        arr[i - lo] = i; 
    shuffle(arr, hi - lo);
    int *res = (int *)malloc(sizeof(int) * size);
    memcpy(res, arr, sizeof(int) * size);
    free(arr);
    return res;
}

int *arrayNoDup(int size)
{
    int *arr = NULL;
    while (1) {
        arr = arrayWithRange(size, -size, size);
        if (!arrayHasDup(arr, size))
            break;
        free(arr);
    }
    return arr;
}

void shuffle(int *arr, int size)
{
    if (!arr || size <= 0)
        return;

    for (int i = 0; i < size; i++) {
        int r = i + randWithRange(0, size - i);
        swap(arr + i, arr + r);
    }
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
    ht *h = ht_create();

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

void matrix_print_(int *A, int Ar, int Ac)
{
    for (int i = 0; i < Ar; i++) {
        for (int j = 0; j < Ac; j++)
            printf("%-3d", A[i * Ac + j]);
        printf("\n");
    }
    printf("\n");

}
void matrix_clr_(int *A, int Ar, int Ac)
{
    memset(A, 0, sizeof(int) * (Ar * Ac));
}

void matrix_mul_(int *A, int Ar, int Ac, int *B, int Br, int Bc, int *C, int Cr, int Cc)
{
    matrix_clr_(C, Cr, Cc);
    if (Cr != Ar || Cc != Bc)
        return;

    for (int i = 0; i < Ar; i++)
        for (int j = 0; j < Bc; j++)
            for (int k = 0; k < Ac; k++)
                C[i * Cc + j] += A[i * Ac + k] * B[k * Bc + j];

}
int *matrix_gen_(int r, int c)
{
    int *arr = (int *)malloc(sizeof(int) * (r * c));
    if (!arr) exit(1);
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            arr[i * c + j] = randWithRange(0, 100);
    return arr;
}

void matrix_print(long *A, int Ar, int Ac)
{
    for (int i = 0; i < Ar; i++) {
        for (int j = 0; j < Ac; j++)
            printf("%-3ld", A[i * Ac + j]);
        printf("\n");
    }
    printf("\n");
}

void matrix_clr(long *A, int Ar, int Ac)
{
    memset(A, 0, sizeof(long) * (Ar * Ac));
}

void matrix_mul(long *A, int Ar, int Ac, long *B, int Br, int Bc, long *C, int Cr, int Cc)
{
    matrix_clr(C, Cr, Cc);
    if (Cr != Ar || Cc != Bc)
        return;

    for (int i = 0; i < Ar; i++)
        for (int j = 0; j < Bc; j++)
            for (int k = 0; k < Ac; k++)
                C[i * Cc + j] += A[i * Ac + k] * B[k * Bc + j];
}

long *matrix_gen(int r, int c)
{
    long *arr = (long *)malloc(sizeof(long) * (r * c));
    if (!arr) exit(1);
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            arr[i * c + j] = randWithRange(0, 10);
    return arr;
}

/*
 * int main(int argc, char *argv[])
 * {
 *     bst_test();
 * }
 */
