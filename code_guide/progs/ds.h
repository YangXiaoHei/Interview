#ifndef _DS_TOOL_H_
#define _DS_TOOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>

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
    long (*hash)(struct ht *, void *);
} ht;

ht *ht_create(long (*hash)(ht *, void *));
void ht_insert(ht *h, long key, long val);
long ht_get(ht *h, long key);
void ht_remove(ht *h, long key);
int ht_empty(ht *h);
void ht_print(ht *h);

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
long stack_pop(stack *s);
long stack_peek(stack *s);
void stack_print(stack *s);
void stack_release(stack **s);
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


#endif
