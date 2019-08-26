#include "ds.h"

char buf1[100], buf2[100];
char buf3[1000];

int cmp(const char *str1, const char *str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    snprintf(buf1, 100, "%s%s", str1, str2);
    snprintf(buf2, 100, "%s%s", str2, str1);
    return strcmp(buf1, buf2);
}

void shell(const char *arr[], int size)
{
    int h = 1;
    while (h < size / 3)
        h = 3 * h + 1;

    while (h >= 1) {
        for (int i = h; i < size; i++) {
            const char *t = arr[i];
            int j;
            for (j = i - h; j >= 0 && cmp(t, arr[j]) < 0; j -= h)
                arr[j + h] = arr[j];
            arr[j + h] = t;
        }
        h /= 3;
    }
}

char *expression(const char *arr[], int size)
{
    int len = 0;
    for (int i = 0; i < size; i++)
        len += snprintf(buf3 + len, 1000 - len, "%s", arr[i]);
    return buf3;
}

int main(int argc, char *argv[])
{
    const char *arr[] = { "bb", "ab", "bd" };
    int size = sizeof(arr) / sizeof(arr[0]);
    shell(arr, size);
    printf("%s\n", expression(arr, size));
}
