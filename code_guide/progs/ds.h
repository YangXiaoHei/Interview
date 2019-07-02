#ifndef _DS_TOOL_H_
#define _DS_TOOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

/*********** stack ****************/
typedef struct stknode {
    int val;
    struct stknode *next;
} stknode;
stknode *stknode_create(int val);
typedef struct stack {
    int size;
    stknode *top;
} stack;
stack *stack_create(void);
void stack_push(stack *s, int val);
int stack_empty(stack *s);
int stack_pop(stack *s);
int stack_peek(stack *s);
void stack_print(stack *s);
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
