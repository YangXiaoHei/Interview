#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void shift(int *input, int len, int dist)
{
    if (!input || len <= 0 || dist < 0 || dist % len == 0)
        return;
    dist %= len;
    int *tmp = malloc(sizeof(int) * dist);
    if (!tmp) return;
    memcpy(tmp, input + len - dist, sizeof(int) * dist);
    memcpy(input + dist, input, sizeof(int) * (len - dist));
    memcpy(input, tmp, sizeof(int) * dist);
    free(tmp);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage : %s <shift>\n", argv[0]);
        exit(1);
    }

   int a[7] = {1, 2, 3, 4, 5, 6, 7};
   shift(a, 7, atoi(argv[1]));

   for (int i = 0; i < 7; i++) {
       printf("%2d", a[i]); 
   }
   printf("\n");
}
