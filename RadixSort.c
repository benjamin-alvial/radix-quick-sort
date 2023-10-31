#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "CountingSort.c"
#include "BucketSort.c"

typedef struct ParPunteroYBits {
    int ptr;
    int bits;
} ParPunteroYBits;

int RadixSort(int* aOrdenar, int u, int k){
    int Mask = 0; // ej k= 4
    Mask = ~Mask; // 1111111111111111111111111111111
    Mask << k; //11111111111111111111111110000 (k 0's)
    Mask = ~Mask; // 0000000000000000000000001111 (k 1's)
    int TamañoArray = sizeof(aOrdenar)/sizeof(int);
    ParPunteroYBits** ArrayOrdenador = (int**)malloc(sizeof(ParPunteroYBits*)*TamañoArray);
    int* ArrayOrdenador2 = malloc(sizeof(aOrdenar)*TamañoArray);
    int BitsPorRecorrer = sizeof(int)*8;
    int BitsRecorridos = k;
    while(BitsPorRecorrer > k){
        for(int i = 0; i < TamañoArray; i++){ // Me preocupa si se guarda bien
            ParPunteroYBits* j;
            j -> ptr = i;
            j -> bits = aOrdenar[i]&&Mask;
            ArrayOrdenador[i] = j;
        }
        ArrayOrdenador = BucketSort(ArrayOrdenador,u);
        for(int j = 0 ;j < TamañoArray ;j++ ){
            ArrayOrdenador2[j] = aOrdenar[ArrayOrdenador[j]->ptr];
        } 
        // Mask:  00000000000000000000000000000 1111
        Mask << k; // 0000000000000000000000000 1111 0000
        BitsRecorridos+=k;
        BitsPorRecorrer-= k;
    }
    //Mask = -2147483648;
    



}