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
    int Mask = 0;
    int Mask2 = 0; 
    int TamañoArray = sizeof(aOrdenar)/sizeof(int);
    ParPunteroYBits** ArrayOrdenador = (int**)malloc(sizeof(ParPunteroYBits*)*TamañoArray);
    int* ArrayOrdenador2 = malloc(sizeof(aOrdenar)*TamañoArray);
    int NumIteraciones = sizeof(int)*8;
    int BitsRecorridos = k;
    Mask << k;
    while(NumIteraciones > k){ 
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
        Mask = ~Mask;
        BitsRecorridos+=k;
        Mask2 << BitsRecorridos;
        Mask = Mask&&Mask2;
        NumIteraciones-= k;
    }



}