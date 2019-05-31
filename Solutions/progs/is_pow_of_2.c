#include <stdio.h>

int ispow2(int x)
{
    return !(x & (x - 1));
}

int main(int argc, char *argv[])
{
    printf("%d\n", ispow2(1024));
}
