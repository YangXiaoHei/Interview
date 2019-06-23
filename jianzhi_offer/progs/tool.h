#ifndef _ARRAY_TOOL_H_
#define _ARRAY_TOOL_H_

void tool_sort_core(int *arr, int size, int lo, int hi);
void tool_sort(int *arr, int size);
int tool_is_sorted(int *arr, int size);
long getCurTime(void);
void swap(int *a, int *b);
void parseArray(int *arr, int *len, char *str);
int *array(int size);
int *copyArray(int *arr, int size);
int *arrayWithSize(int size);
int *arrayWithRange(int size, int lo, int hi);
void printArray(int *array, int size);
int randWithRange(int lo, int hi);

#endif
