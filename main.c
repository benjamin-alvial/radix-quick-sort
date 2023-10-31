#include "quicksort.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 1000000; // Adjust the array size according to your system's memory capacity
    unsigned long long *arr = malloc(n * sizeof(unsigned long long));
    if (arr == NULL)
    {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        arr[i] = (((unsigned long long)rand() << 32 | rand()) % (1ULL << 63)) + 1;
    }

    quicksort(arr, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        printf("%llu ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}
