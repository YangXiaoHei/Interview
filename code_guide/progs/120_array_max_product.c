#include "ds.h"

double max2(double a, double b) { return a > b ? a : b; }
double min2(double a, double b) { return a < b ? a : b; }
double max3(double a, double b, double c) { return max2(max2(a, b), c); }
double min3(double a, double b, double c) { return min2(min2(a, b), c); }
double max_product(double *arr, int size)
{
    if (!arr || size <= 0)
        return 0.0;
    
    double min = 1.0, max = 1.0;
    double a, b, c;
    double res = 0;
    for (int i = 0; i < size; i++) {
        a = min * arr[i];
        b = max * arr[i];
        c = arr[i];
        min = min3(a, b, c);
        max = max3(a, b, c); 
        res = max2(max, res);
    }
    return res;
}

int main()
{
    double arr[] = { -2.5, 4, 0, 3, 0.5, 8, -1 };
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("%.3f\n", max_product(arr, size)); 
}
