#include "ds.h"

void print_process(int level, int times, int down)
{
    if (level > times)
        return;

    print_process(level + 1, times, 1);
    printf("%s", down ? "down " : "up ");
    print_process(level + 1, times, 0);
}

void print_fold(int times)
{
    if (times < 1)
        return;
    print_process(1, times, 1);
    printf("\n");
}

int main()
{
    print_fold(3);    
}
