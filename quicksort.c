#include "quicksort.h"
#include <stdlib.h>

void swap(unsigned long long *a, unsigned long long *b)
{
    unsigned long long t = *a;
    *a = *b;
    *b = t;
}

int partition(unsigned long long arr[], int low, int high)
{
    int pivotIndex = low + rand() % (high - low + 1);
    unsigned long long pivot = arr[pivotIndex];
    swap(&arr[pivotIndex], &arr[high]);
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quicksort(unsigned long long arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}
