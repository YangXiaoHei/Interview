#include "ds.h"

int main(int argc, char *argv[])
{
    int size = 15;
    int *arr = arrayWithRange(size, 0, size / 3);
    printArray(arr, size);
}
