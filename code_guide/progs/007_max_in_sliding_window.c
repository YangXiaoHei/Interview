#include "ds.h"

deque *max_in_sliding_window(int *win, int size, int winsize)
{
    if (!win || size <= 0 || winsize <= 0)
        return NULL;

    deque *index = deque_create();
    for (int i = 0; i < winsize; i++) {
        while (!deque_empty(index) && win[i] > win[deque_back(index)])
            deque_pop_back(index);
        deque_push_back(index, i);
    }
    
    deque *max = deque_create();
    deque_push_back(max, win[deque_front(index)]);
    for (int i = winsize; i < size; i++) {
        while (!deque_empty(index) && win[i] > win[deque_back(index)])
           deque_pop_back(index);

        if (!deque_empty(index) && i - deque_front(index) >= winsize)
            deque_pop_front(index);

        deque_push_back(index, i);
        deque_push_back(max, win[deque_front(index)]);
    }
    deque_release(&index);
    return max;
}

int main(int argc, char *argv[])
{
    int size = randWithRange(5, 15);
    int *win = arrayWithRange(size, 1, 30);
    printArray(win, size);

    deque *d = max_in_sliding_window(win, size, 3);
    deque_print_front(d);
}
