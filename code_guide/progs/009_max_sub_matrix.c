#include "ds.h"

int *gen_01_matrix(int row, int col)
{
    if (row <= 0 || col <= 0)
        return NULL;
    
    int *arr = malloc(sizeof(int) * row * col);
    for (int i = 0; i < row * col; i++) 
        arr[i] = randWithRange(0, 1000) < 800;
    return arr;
}

void print_matrix(int *arr, int row, int col)
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) 
            printf("%-3d", arr[i * col + j]);
        printf("\n");
    }
}

int max_sub_matrix(int *arr, int row, int col)
{
    if (!arr || row <= 0 || col <= 0)
        return 0;

    int *height = malloc(sizeof(int) * col);
    memset(height, 0, sizeof(int) * col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            height[j]++;
            if (arr[i * col + j] == 0)
                height[j] = 0;
        }
    }

    stack *s = stack_create();
    int index = 0;
    int max = 0;
    int tmp = 0;
    int push_height = 0;
    stack_push(s, index++);
    while (!stack_empty(s)) {
        push_height = index >= col ? 0 : height[index];        
        while (!stack_empty(s) && push_height <= height[stack_peek(s)]) {
            int pop_height = height[stack_pop(s)];
            int k = stack_empty(s) ? -1 : stack_peek(s);
            tmp = (index - k - 1) * pop_height;
            if (tmp > max)
                max = tmp;
        }

        if (index < col)
            stack_push(s, index);
        index++;
    }
    stack_release(&s);
    return max;
}

int main(int argc, char *argv[])
{
    int row = 5;
    int col = 6;
    int *arr = gen_01_matrix(row, col);
    print_matrix(arr, row, col);
    printf("%d\n", max_sub_matrix(arr, row, col));
}
