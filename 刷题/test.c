#include <stdio.h>
#include "array_tool.h"

int main(int argc, char *argv[])
{
    int n = 5;
    printf("n = %d\n", n);
    printArray(arrayWithRange(n + 1, 1, n + 1), n + 1);
}
