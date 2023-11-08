#include "quicksort.h"
#include <stdlib.h>

void swap(unsigned long long *a, unsigned long long *b)
{
    unsigned long long temp = *a;
    *a = *b;
    *b = temp;
}

int randomPivot(int low, int high)
{
    return low + rand() / (RAND_MAX / (high - low + 1) + 1);
}

void quicksort(unsigned long long arr[], int low, int high)
{
    if (high <= low)
        return;

    int pivotIndex = randomPivot(low, high);
    swap(&arr[low], &arr[pivotIndex]);
    unsigned long long v = arr[low];

    int lt = low, gt = high;
    int i = low;

    while (i <= gt)
    {
        if (arr[i] < v)
            swap(&arr[lt++], &arr[i++]);
        else if (arr[i] > v)
            swap(&arr[i], &arr[gt--]);
        else
            i++;
    }

    quicksort(arr, low, lt - 1);
    quicksort(arr, gt + 1, high);
}
