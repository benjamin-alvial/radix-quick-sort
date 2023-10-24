#include "quicksort.c"
#include "radix-sort.c"
#include <time.h>

// Values for universe u
// follow powers of 2 from U_POW_INITIAL to U_POW_FINAL
#define U_POW_INITIAL 1
#define U_POW_FINAL 64

// Amount of times the sort will be done to calculate
// the average performance
#define NUMBER_REPS 100

// Number of elements in the arrays
#define ARRAY_SIZE 100000000


int main() {

    // This file will be used to plot the performance data
    FILE *results_file = fopen("performance_results.txt", "w");

    // Array for the values of u (powers of 2)
    int u_values_size = U_POW_FINAL-U_POW_INITIAL+1;
    unsigned long long u_values[u_values_size];
    for(int i=0; i<u_values_size; i++) {
        u_values[i] = pow(2, i+U_POW_INITIAL);
    }

    // For u in [2^U_POW_INITIAL, ..., 2^U_POW_FINAL]
    for(int i=0; i<u_values_size; i++) {
        int u = u_values[i];

        // For k in [1, ..., log2(u)]
        // The index i+U_POW_INITIAL is exactly the value of log2(u)
        // since it's the exponent of the 2 in this iteration
        for(int k=1; k<i+U_POW_INITIAL+1; k++) {

            for(int rep=1; rep<NUMBER_REPS+1; rep++) {

                unsigned long long array[ARRAY_SIZE];

                for (int j = 0; j < ARRAY_SIZE; ++j) {
                    // Generate an array of random numbers between 1 and u
                    array[i] = ((unsigned long long)rand() % u) + 1;
                }

                clock_t start_time_rs, end_time_rs;
                start_time_rs = clock();
                radix_sort(array, n, k);
                end_time_rs = clock();
                double cpu_time_used_rs = ((double) (end_time_rs - start_time_rs)) / CLOCKS_PER_SEC;

                clock_t start_time_qs, end_time_qs;
                start_time_qs = clock();
                quicksort(array, n);
                end_time_qs = clock();
                double cpu_time_used_qs = ((double) (end_time_qs - start_time_qs)) / CLOCKS_PER_SEC;

                fprintf(results_file, "%d, %lf, %lf, %lf, %d, %d, %d\n", u, k, rep, cpu_time_used_rs, cpu_time_used_qs);
                
            }

        }

    }

    fclose(results_file);
    return 0;

}