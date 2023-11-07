#include "quicksort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fillArrayWithRandom(unsigned long long *arr, int n, int bits)
{
    if (bits < 1 || bits > 64)
    {
        fprintf(stderr, "Bits parameter must be between 1 and 64\n");
        return;
    }

    unsigned long long max_val = (bits >= 64) ? ~0ULL : (1ULL << bits) - 1;

    for (int i = 0; i < n; i++)
    {
        unsigned long long rand_val = 0ULL;
        for (int j = 0; j < bits; j += 15)
        {
            rand_val = (rand_val << 15) | (rand() & 0x7FFF);
        }
        arr[i] = (rand_val & max_val) + 1ULL;
    }
}

int main()
{
    int n = 100000000;
    int u = 64;

    for (int i = 1; i <= u; i++)
    {
        // printf("BITS: %d\n", i);
        unsigned long long *arr = malloc(n * sizeof(unsigned long long));
        if (arr == NULL)
        {
            fprintf(stderr, "Failed to allocate memory\n");
            return 1;
        }

        // printf("Creating random array...\n");

        clock_t start = clock();

        srand((unsigned)time(NULL));

        fillArrayWithRandom(arr, n, i);

        clock_t end = clock();

        double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

        // printf("TIME OF CREATION for u=%d:  %.3f seconds.\n", i, elapsed_time);

        // printf("Sorting array...\n");
        clock_t start2 = clock();
        quicksort(arr, 0, n - 1);
        clock_t end2 = clock();

        double elapsed_time2 = (double)(end2 - start2) / CLOCKS_PER_SEC;

        printf("TIME OF SORTING for u=:%d  %.3f seconds.\n", i, elapsed_time2);

        for (int i = 0; i < n - 1; i++)
        {
            if (!(arr[i] <= arr[i + 1]))
            {
                printf("ERROR\n");
                break;
            }
        }

        free(arr);
    }
    return 0;
}
