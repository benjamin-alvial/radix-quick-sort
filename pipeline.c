#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "quicksort.c"
#include "radixsort.c"

// Values for universe u
// follow powers of 2 from U_POW_INITIAL to U_POW_FINAL
//#define U_POW_INITIAL 1
//#define U_POW_FINAL 64
#define U_POW_INITIAL 10
#define U_POW_FINAL 60

// Amount of times the sort will be done to calculate
// the average performance
//#define NUMBER_REPS 100
#define NUMBER_REPS 1

// Number of elements in the arrays
//#define ARRAY_SIZE 100000000
#define ARRAY_SIZE 10000000

int main() {

    // This file will be used to plot the performance data
    FILE *results_file = fopen("performance_results.txt", "w");

    // Array for the values of u (powers of 2)
    int u_values_size = U_POW_FINAL-U_POW_INITIAL+1;
    unsigned long long u_values[u_values_size];
    for(int i=0; i<u_values_size; i++) {
        u_values[i] = pow(2, i+U_POW_INITIAL);
        printf("Power of 2 created: 2^%d= %llu\n", i+U_POW_INITIAL, u_values[i]);
    }

    double cpu_time_used_rs, cpu_time_used_qs;

    // For u in [2^U_POW_INITIAL, ..., 2^U_POW_FINAL]
    for(int i=0; i<u_values_size; i++) {
        unsigned long long u = u_values[i];

        int quick_rep = 0; // Do quicksort only NUMBER_REPS for each value of u

        // For k in [1, 2, 3, ..., log2(u)]
        // The index i+U_POW_INITIAL is exactly the value of log2(u)
        // since it's the exponent of the 2 in this iteration
        for(int k=1; k<i+U_POW_INITIAL+1; k++) {

            // Counter arrays in radix's bucket sorts can't be too big.
            // k=30 would mean a counter array for universe approx. [1..2^30]
            if(k>26) {
                continue; 
            }

            printf("--------------------------------------------\n");
            printf("Sorting %d elements for u=2^%d=%llu, k=%d for %d repetitions...\n", ARRAY_SIZE, i+U_POW_INITIAL, u, k, NUMBER_REPS);
            printf("--------------------------------------------\n");

            for(int rep=1; rep<NUMBER_REPS+1; rep++) {

                printf("Repetition number %d...\n", rep);

                printf("- Creating array...\n");
                unsigned long long *array = (unsigned long long *)malloc(ARRAY_SIZE * sizeof(unsigned long long));
                for (int j = 0; j < ARRAY_SIZE; ++j) {
                    // Generate an array of random numbers between 1 and u
                    // Multiplication of two values from a uniform distribution may not follor another uniform distribution, 
                    // but this works for this project.
                    unsigned long long rand1 = ((unsigned long long)rand() % u) + 1;
                    unsigned long long rand2 = ((unsigned long long)rand() % u) + 1;
                    array[j] = rand1 * rand2;
                }

                printf("- Sorting with radix sort...\n");
                clock_t start_time_rs, end_time_rs;
                start_time_rs = clock();
                radixsort(array,k,ARRAY_SIZE);
                end_time_rs = clock();
                cpu_time_used_rs = ((double) (end_time_rs - start_time_rs)) / CLOCKS_PER_SEC;

                if(quick_rep < NUMBER_REPS) {
                    printf("- Sorting with quicksort...\n");
                    clock_t start_time_qs, end_time_qs;
                    start_time_qs = clock();
                    quicksort(array, 0, ARRAY_SIZE-1);
                    end_time_qs = clock();
                    cpu_time_used_qs = ((double) (end_time_qs - start_time_qs)) / CLOCKS_PER_SEC;
                    quick_rep++; 
                }
            
                fprintf(results_file, "%llu, %d, %d, %lf, %lf\n", u, k, rep, cpu_time_used_rs, cpu_time_used_qs);
        
                free(array);
            }

        }

    }

    fclose(results_file);
    return 0;

}