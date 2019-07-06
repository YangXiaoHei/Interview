#include "ds.h"

int count_sub_arr(int *arr, int size, int num)
{
    deque *qmax = deque_create();
    deque *qmin = deque_create();

    int i = 0, j = 0;
    int res = 0;

    while (i < size) {
        while (j < size) {

            while (!deque_empty(qmax) && arr[deque_back(qmax)] <= arr[j])
                deque_pop_back(qmax);
            deque_push_back(qmax, j);

            while (!deque_empty(qmin) && arr[deque_back(qmin)] >= arr[j])
                deque_pop_back(qmin);
            deque_push_back(qmin, j);

            if (arr[deque_front(qmax)] - arr[deque_front(qmin)] > num)
                break;

            j++;
        }

        if (deque_front(qmax) == i)
            deque_pop_front(qmax);

        if (deque_front(qmin) == i)
            deque_pop_front(qmin);

        res += j - i;
        i++;
    }
    deque_release(&qmin);
    deque_release(&qmax);
    return res;
}

int main(int argc, char *argv[])
{
    int num = randWithRange(1, 10);
    int size = 8;
    int *arr = arrayWithRange(size, 1, 10);
    printArray(arr, size);
    printf("num = %d, result = %d\n", num, count_sub_arr(arr, size, num));
}
