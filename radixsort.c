#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

// Does a bucket sort with satellite information.

// Sorts with bucket sort a given array_to_sort
// and in the same order sorts the given array_satellite. 
// Both arrays must be have size size.
// The universe for the elements in array_to_sort is [1..u]

// In the context of this project,
// array_satellite would correspond to [17,5,9,7,8]
// array_to_sort would correspond to [1,1,1,1,0]
// if we consider the iteration for the least significant bit.
// Strictly speaking, array_to_sort is [2,2,2,2,1] so that universe is well-defined.

void bucketSortWithSatellite(
    unsigned long long array_to_sort[], 
    unsigned long long array_satellite[],
    int size, 
    unsigned long long u) {

    // Temporal arrays to write the results.
    unsigned long long *result_array = (unsigned long long *)malloc(size * sizeof(unsigned long long));
    unsigned long long *result_satellite = (unsigned long long *)malloc(size * sizeof(unsigned long long));
    // Create counter array.
    int *C = (int *)malloc((u+1) * sizeof(int));
    
    /*
    printf("\n-- array to be sorted --\n");
    for(int a = 0; a < size;a++){
        printf("%llu ",array_to_sort[a]);
    }
    */
    
    /*
    printf("\n-- satellite array to be sorted --\n");
    for(int a = 0; a < size;a++){
        printf("%llu ",array_satellite[a]);
    }
    */

    for(unsigned long long j=0; j<u+1; j++) {
        C[j] = 0;
    }

    /*
    printf("\n-- counter array --\n");
    for(int a = 0; a < u+1;a++){
        printf("%d ",C[a]);
    }
    */

    // Increase counter of each A[i] that is found in A.
    for (int i = 0; i < size; i++) {
        C[array_to_sort[i]]++;
    }

    /*
    //printf("\n-- increased counter array --\n");
    for(int a = 0; a < u+1;a++){
        printf("%d ",C[a]);
    }
    */

    // Find positions of where to insert copies.
    for (unsigned long long j = 1; j < u + 1; j++) {
        C[j] = C[j] + C[j - 1];
    }

    /*
    //printf("\n-- counter array changed --\n");
    for(int a = 0; a < u+1;a++){
        printf("%d ",C[a]);
    }
    */

    // Save results in temporal arrays.
    for(int i=0; i<size; i++) {
        result_array[C[array_to_sort[i]-1]] = array_to_sort[i];
        result_satellite[C[array_to_sort[i]-1]] = array_satellite[i];
        C[array_to_sort[i]-1]++;
    }

    // Modify original arrays so they can be used in next iteration.
    for(int a = 0; a < size;a++){
        array_to_sort[a] = result_array[a];
        array_satellite[a] = result_satellite[a];
    }

    // Free temporal arrays.
    free(result_array);
    free(result_satellite);
    free(C);
}

// Does a radix sort as a series of bucket sorts by bits,
// from right to left (least to most significant).
// Each bucket sort considers k bits.

void radixsort(unsigned long long array_original[], int k, int size) {

    // The satellite information is simply the numbers that want to be sorted. A copy is then made.
    unsigned long long *array_satellite = (unsigned long long *)malloc(size * sizeof(unsigned long long));
    memcpy(array_satellite, array_original, size*sizeof(unsigned long long));

    // The sorting will be done with respect to k bits in the real numbers. These must be calculated.
    unsigned long long *array_to_sort = (unsigned long long *)malloc(size * sizeof(unsigned long long));
    unsigned long long Mask = (1ULL << k) - 1;

    int BitsPorRecorrer = sizeof(unsigned long long)*8; // Cantidad de bits en un unsigned long long
    int BitsRecorridos = 0;

    while(BitsPorRecorrer >= k){ // >=?

        // Extraer los k bits a ordenar.
        //printf("Mask is: %llu\n", Mask);
        for(int a = 0; a < size; a++){
            unsigned long long bits = array_satellite[a]&Mask; // Bits are extracted.
            bits = bits >> BitsRecorridos; // Bits in the middle of the number are moved to the beginning.
            array_to_sort[a] = bits + 1; // Adjust with +1 so universe is well-defined. 0->1, 1->2.
        }

        bucketSortWithSatellite(array_to_sort, array_satellite, size, pow(2,k));

        Mask = Mask << k;
        BitsRecorridos += k;
        BitsPorRecorrer -= k;
     
    }

    // The number of bits per iteration k may not divide the total number of bits.
    // If there are bits that weren't analyzed yet, do one last bucket sort.
    if(BitsPorRecorrer>0) {
        for(int a = 0; a < size; a++){
            unsigned long long bits = array_satellite[a] >> (sizeof(unsigned long long)*8 - BitsPorRecorrer);
            bits = bits >> BitsRecorridos;
            array_to_sort[a] = bits + 1;
        }
        bucketSortWithSatellite(array_to_sort, array_satellite, size, pow(2,BitsPorRecorrer));
    }

    free(array_satellite);
    free(array_to_sort);
}