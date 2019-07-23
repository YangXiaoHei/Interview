#ifndef _DS_TOOL_H_
#define _DS_TOOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

#ifdef BENCHMARK
#error "what a fuck!"
#endif

#define BENCHMARK(...)\
do {\
    long __beg = getCurTime();\
    __VA_ARGS__\
    long __end = getCurTime();\
    long __diff = __end - __beg;\
    if (__diff < 1000)\
        printf("total cost %ld us\n", __diff);\
    else if (__diff < 1000 * 1000)\
        printf("total cost %.3f ms\n", __diff / 1000.0);\
    else\
        printf("total cost %.3f s\n", __diff * 1.0 / (1000 * 1000));\
} while (0)\

typedef struct treenode {
    long val;
    int size;
    int height;
    struct treenode *parent;
    struct treenode *left;
    struct treenode *right;
} treenode;
treenode *treenode_create(long val);
void in_traverse(treenode *root);
void pre_traverse(treenode *root);
void post_traverse(treenode *root);
void in_traverse_funptr(treenode *root, void(*trav)(long));
void pre_traverse_funptr(treenode *root, void(*trav)(long));
void post_traverse_funptr(treenode *root, void(*trav)(long));
void in_print(treenode *root);
void pre_print(treenode *root);
void post_print(treenode *root);
int tree_size(treenode *root);
int tree_height(treenode *root);
void tree_draw(treenode *root);
void tree_release(treenode **root);
treenode* tree_clone(treenode *root);

treenode* bst_create(int size);
treenode* bst_create_with_arr(int *arr, int size);
treenode* cbt_create(int size);
treenode* cbt_create_with_arr(int *arr, int size);
void bst_insert(treenode **root, long val);
void bst_remove(treenode **root, long val);
int get_num_width(int num);
int get_width_num(int w);

typedef struct htnode {
    long key;
    long val;
    struct htnode *prev;
    struct htnode *next;
} htnode;
htnode* htnode_create(long key, long val);

typedef struct ht {
    int size;
    int bucket;
    htnode **slot;
    long (*hash)(long);
} ht;

ht *ht_create(long (*hash)(long));
void ht_insert(ht *h, long key, long val);
long ht_get(ht *h, long key);
int ht_contain(ht *h, long key);
void ht_remove(ht *h, long key);
int ht_empty(ht *h);
void ht_print(ht *h);
void ht_print_funptr(ht *h, void (*print)(long, long));
void ht_release(ht **h);

/*********** deque ****************/
typedef struct deque_node {
    long val;
    struct deque_node *next;
    struct deque_node *prev;
} deque_node;
deque_node *deque_node_create(long val);
typedef struct deque {
    deque_node *header;
    deque_node *tailer;
    int size;
} deque;
deque *deque_create(void);
void deque_push_back(deque *d, long val);
void deque_push_front(deque *d, long val);
long deque_pop_back(deque *d);
long deque_pop_front(deque *d);
long deque_front(deque *d);
long deque_back(deque *d);
int deque_empty(deque *d);
void deque_print_front(deque *d);
void deque_print_back(deque *d);
void deque_print_front_funptr(deque *d, void(*fun)(long));
void deque_print_back_funptr(deque *d, void(*fun)(long));
void deque_release(deque **d);
/**********************************/

/*********** queue ****************/
typedef struct queue {
    int size;
    deque_node *header;
    deque_node *tailer;
} queue;

queue *queue_create(void);
int queue_empty(queue *q);
void queue_enqueue(queue *q, long val);
long queue_dequeue(queue *q);
void queue_print(queue *q);
void queue_release(queue **q);
/*********************************/

/*********** stack ****************/
typedef struct stknode {
    long val;
    struct stknode *next;
} stknode;
typedef struct stack {
    long size;
    stknode *top;
} stack;

stknode *stknode_create(long val);
stack *stack_create(void);
void stack_push(stack *s, long val);
int stack_empty(stack *s);
void stack_clear(stack *s);
void stack_copy(stack *dst, stack *src);
long stack_pop_bottom(stack *s);
int stack_size(stack *s);
long stack_pop(stack *s);
long stack_peek(stack *s);
void stack_print(stack *s);
void stack_print_r(stack *s);
void stack_print_s(stack *s);
void stack_print_funptr(stack *s, void(*printfun)(long));
void stack_release(stack **s);
/**********************************/

/**********************************/
typedef struct lnode {
    long val;
    struct lnode *next;
} lnode;

lnode *lnode_create(long val);
void list_insert(lnode **head, long val);
lnode *list_create(int size);
lnode *list_circle_create(int size);
lnode *list_loop_create(int size);
lnode *list_create_with_arr(int *arr, int size);
void list_print(lnode *head);
void list_print_with_size(lnode *head, int size);
void list_release(lnode **head);
/**********************************/

/**********************************/
typedef struct dlnode {
    long val;
    struct dlnode *prev;
    struct dlnode *next;
} dlnode;

dlnode *dlnode_create(long val);
void dlist_insert(dlnode **head, long val);
dlnode *dlist_create(int size);
dlnode *dlist_create_with_arr(int *arr, int size);
void dlist_print_front(dlnode *head);
void dlist_print_back(dlnode *head);
void dlist_release(dlnode **head);
/**********************************/



void sort(int *arr, int size);
int is_sorted(int *arr, int size);
void swap(int *a, int *b);
long getCurTime(void);
void parseArray(int *arr, int *len, char *str);
int randWithRange(int lo, int hi);
void printArray(int *array, int size);
int *copyArray(int *arr, int size);
int *array(int size);
int *arrayWithRange(int size, int lo, int hi);
int *arrayWithSize(int size);
int *arrayNoDup(int size);
int *arrayNoDupWithRange(int size, int lo, int hi);
int arrayHasDup(int *arr, int size);
void shuffle(int *arr, int size);

void matrix_print(long *A, int Ar, int Ac);
void matrix_clr(long *A, int Ar, int Ac);
void matrix_mul(long *A, int Ar, int Ac, long *B, int Br, int Bc, long *C, int Cr, int Cc);
long *matrix_gen(int r, int c);

#endif
