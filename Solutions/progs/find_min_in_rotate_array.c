#include <stdio.h>

int normnumsl_find(int *nums, int numssSize)
{
    int min = nums[0];
    for (int i = 1; i < numssSize; i++)
        if (nums[i] < min)
            min = nums[i];
    return min;
}

int find_min(int *nums, int numsSize)
{
    if (!nums || numsSize <= 0)
        return -1;

    if (numsSize == 1)
        return nums[0];

    int lo = 0, hi = numsSize - 1, mid = (lo + hi) >> 1;

    if (nums[lo] == nums[hi] && nums[mid] == nums[hi])
        return normnumsl_find(nums, numsSize);

    if (nums[mid] > nums[lo] && nums[mid] < nums[hi])
        return nums[0];

    if (nums[mid] > nums[lo] && nums[mid] == nums[hi])
        return nums[0];

    if (nums[mid] == nums[lo] && nums[mid] < nums[hi])
        return nums[0];

    while (hi - lo > 1) {
        mid = (lo + hi) >> 1;
        if (nums[mid] >= nums[lo] && nums[mid] > nums[hi])
            lo = mid;
        else
            hi = mid;
    }
    return nums[hi];
}

int main(int argc, char *argv[])
{
    /* int a[] = {4, 4, 5, 6, 1, 2, 3, 4}; */
    int a[] = {4, 4, 5, 6, 1, 2, 3, 4};
    int size = sizeof(a) / sizeof(a[0]);
    printf("%d\n", find_min(a, size));
}
