#include "ds.h"

lnode *get_loop_entry(lnode *list, int *nloop)
{
    if (!list)
        return NULL;

    /* 判断是否有环 */
    lnode *fast = list, *slow = list;
    while (1) {
        if (!(fast = fast->next))
            break;
        if (!(fast = fast->next))
            break;
        slow = slow->next;
        if (slow == fast)
            break;
    }

    if (!fast)
        return NULL;

    /* 计算环中有多少节点 */
    int n = 1;
    while (slow->next != fast)
        slow = slow->next, n++;
    if (nloop)
        *nloop = n;

    /* 转换问题为倒数第 k 个节点 */
    slow = list, fast = list;
    while (n--)
        fast = fast->next;

    while (slow != fast)
        fast = fast->next, slow = slow->next;

    return fast;
}

lnode *get_kth_node(lnode *list, int k)
{
    if (!list || k < 0)
        return NULL;

    while (list && k > 0)
        list = list->next, k--;
    return list;
}

void two_loop_intersect_common_entry(lnode **list1, lnode **list2)
{
    lnode *loop = list_loop_create(10);
    lnode *list = list_create(6);
    lnode *entry = get_loop_entry(loop, NULL);

    lnode *last = list;
    while (last->next)
        last = last->next;

    int n = 1;
    for (lnode *cur = loop; cur != entry; cur = cur->next)
        n++;

    int r = randWithRange(0, n);
    lnode *inter = get_kth_node(loop, r);
    printf("entry is %-3ld inter is %-3ld\n", entry->val, inter->val);

    last->next = inter;
    *list1 = loop;
    *list2 = list;
}

void two_loop_intersect_diff_entry(lnode **list1, lnode **list2)
{
    int nloop = 0;
    lnode *loop = NULL;
    lnode *entry = NULL;
    while (1) {
        loop = list_loop_create(10);
        entry = get_loop_entry(loop, &nloop);
        if (nloop > 1)
            break;
    }
    lnode *list = list_create(6);

    lnode *last = list;
    while (last->next)
        last = last->next;

    int n = 1;
    for (lnode *cur = loop; cur != entry; cur = cur->next)
        n++;

    int r = 0;
    lnode *another_entry = NULL;
    while (1) {
        r = randWithRange(0, nloop);
        another_entry = get_kth_node(entry, r);
        if (another_entry != entry)
            break;
    }

    last->next = another_entry;
    printf("entry1 = %-3ld entry2 = %-3ld\n", entry->val, another_entry->val);
    *list1 = loop;
    *list2 = list;
}

void two_loop_non_intersect(lnode **list1, lnode **list2)
{
    *list1 = list_loop_create(10);
    *list2 = list_loop_create(8);
}

int two_loop_list_intersect(lnode *list1, lnode *list2)
{
    if (!list1 || !list2)
        return 0;

    int intersect = 0;
    lnode *entry1 = get_loop_entry(list1, NULL);
    lnode *entry2 = get_loop_entry(list2, NULL);
    /* 必须是求两个有环链表的交点，连他妈环都没有算怎么回事 */
    if (!(entry1 && entry2))
        return 0;

    if (entry1 == entry2) {
        int n1 = 1;
        lnode *cur1 = NULL;
        for (cur1 = list1; cur1 != entry1; cur1 = cur1->next)
            n1++;

        int n2 = 1;
        lnode *cur2 = NULL;
        for (cur2 = list2; cur2 != entry2; cur2 = cur2->next)
            n2++;

        if (cur1 != cur2)
            return 0;

        int diff = n1 - n2;
        diff = diff < 0 ? -diff : diff;
        lnode *longer = n1 > n2 ? list1 : list2;
        lnode *shorter = longer == list1 ? list2 : list1;
        while (diff--)
            longer = longer->next;

        while (1) {
            if (longer == shorter) {
                intersect = 1;
                break;
            }
            longer = longer->next;
            shorter = shorter->next;
        }
        printf("common entry, intersect node %-3ld\n", longer->val);
    } else {
        lnode *cur1 = entry1;
        do {
            cur1 = cur1->next;
            if (cur1 == entry2) {
                intersect = 1;
                break;
            }
        } while (cur1 != entry1);

        if (intersect)
            printf("diff entry, intersect node %-3ld\n", entry2->val);
    }
    return intersect;
}

int main(int argc, char *argv[])
{
    lnode *list1, *list2;
    int r = randWithRange(0, 3);
    if (r == 0) 
        two_loop_intersect_diff_entry(&list1, &list2);
    else if (r == 1)
        two_loop_intersect_common_entry(&list1, &list2);
    else
        two_loop_non_intersect(&list1, &list2);

    list_print_with_size(list1, 20);
    list_print_with_size(list2, 20);

    two_loop_list_intersect(list1, list2);
}
