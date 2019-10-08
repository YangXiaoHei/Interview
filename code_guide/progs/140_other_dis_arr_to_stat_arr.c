#include "ds.h"

void path_to_dis(int *arr, int size)
{
    int cap = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == i) {
            cap = i;
        } else if (arr[i] > -1) {
            int cur = arr[i];
            arr[i] = -1;
            int pre = i;
            while (cur != arr[cur]) {
                if (arr[cur] <= -1)
                    break;

                int next = arr[cur];
                arr[cur] = pre;
                pre = cur;
                cur = next;
            }

            int val = cur == arr[cur] ? 0 : arr[cur];
            while (arr[pre] != -1) {
                int lastpre = arr[pre];
                arr[pre] = --val;
                pre = lastpre;
            }
            arr[pre] = --val;
        }
    }
    arr[cap] = 0;
}

void dis_to_stat(int *arr, int size)
{
    int index = 0;
    for (int i = 0; i < size; i++) {
        index = arr[i];
        if (index >= 0)
            continue;

        arr[i] = 0;
        while (1) {
            index = -index;
            if (arr[index] > -1) {
                arr[index]++;
                break;
            } 
            int next = arr[index];
            arr[index] = 1;
            index = next;
        }
    }
    arr[0] = 1;
}

void path_to_stat(int *arr, int size)
{
    if (!arr || size <= 0)
        return;

    path_to_dis(arr, size);
    dis_to_stat(arr, size);
}

int main()
{
    setbuf(stdout, NULL);
    int arr[] = { 9, 1, 4, 9, 0, 4, 8, 9, 0, 1 };
    int size = sizeof(arr) / sizeof(arr[0]);
    path_to_stat(arr, size);
    printArray(arr, size);    
}
