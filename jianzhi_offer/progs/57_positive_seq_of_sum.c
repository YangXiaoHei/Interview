#include <stdio.h>
#include "tool.h"

void positive_seq_of_sum_s(int sum)
{
    if (sum <= 2)
        return;

    int i = 1, j = 2;
    int tmpsum = i + j;
    while (j <= (1 + sum) / 2) {
        if (tmpsum == sum) {
            for (int k = i; k <= j; k++)
                printf("%-3d", k);
            printf("\n");
            tmpsum += ++j;
            tmpsum -= i++;
        } else if (tmpsum < sum) 
            tmpsum += ++j;
          else 
            tmpsum -= i++;
    }
}

int main(int argc, char *argv[])
{
    int r = randWithRange(10, 100);
    printf("r = %d\n", r);
    positive_seq_of_sum_s(r);
}
