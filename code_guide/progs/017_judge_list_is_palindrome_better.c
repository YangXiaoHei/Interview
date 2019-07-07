#include "ds.h"

lnode *gen_palindrome(int size)
{
    int left = ceil(size / 2.0);
    int right = size - left;
    int *arr = arrayWithRange(left, 1, 10);
    int *copy = copyArray(arr, right);
    int i = 0, j = right - 1;
    while (i < j) {
        swap(copy + i, copy + j);
        i++; j--;
    }
    int *total = malloc(sizeof(int) * size);
    memcpy(total, arr, sizeof(int) * left);
    memcpy(total + left, copy, sizeof(int) * right);
    free(arr);
    free(copy);

    lnode *list = list_create_with_arr(total, size);
    free(total);
    return list;
}

int is_list_palindrome(lnode *list)
{
    if (!list)
        return 0;

    if (!list->next)
        return 1;

    /* 找到中间节点 */
    lnode *mid = list, *fast = list;
    while (fast->next && fast->next->next)
        mid = mid->next, fast = fast->next->next;

    /* 反转后半部分 */
    lnode *prev = NULL, *head = mid, *next = NULL;
    while (head) {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }

    /* 前半部分后半部分对比 */
    lnode *last = prev;
    int result = 1;
    while (list && last) {
        if (list->val != last->val) {
            result = 0;
            break;
        }
        list = list->next;
        last = last->next;
    }

    /* 恢复被反转的后半部分 */
    prev = NULL, head = prev, next = NULL;
    while (head) {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return result;
}

int main(int argc, char *argv[])
{
    int size = randWithRange(1, 10);
    lnode *list = NULL;
    if (randWithRange(0, 2))
        list = gen_palindrome(size);
    else
        list = list_create(size);
    list_print(list);
    printf("is palindrome : %d\n", is_list_palindrome(list));
}
