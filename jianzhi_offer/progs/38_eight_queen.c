#include <stdio.h>
#include "tool.h"

int count = 0;

void draw_queen(int *a, int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (a[i] == j)
                printf("%-3c", 'O');
            else
                printf("%-3c", '.');
        }
        printf("\n");
    }
    printf("--------------------------\n");
}

void check_condition(int *a, int size, int idx)
{
    if (idx == size) {
        for (int i = 0; i < size; i++) 
            for (int j = i + 1; j < size; j++)  
                if (i - j == a[i] - a[j] ||
                    j - i == a[i] - a[j])
                    return;
        count++;
        draw_queen(a, size);
        return;
    }
    for (int i = idx; i < size; i++) {
        swap(a + idx, a + i);
        check_condition(a, size, idx + 1);
        swap(a + idx, a + i);
    }
}

void eight_queen(void)
{
    int a[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    check_condition(a, 8, 0);
}

int main(int argc, char *argv[])
{
   eight_queen(); 
   printf("%-3d\n", count);
}
