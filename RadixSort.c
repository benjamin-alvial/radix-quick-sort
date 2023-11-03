#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "BucketSort.c"

unsigned long long* RadixSort(unsigned long long* aOrdenar, int u, int k, int TamañoArray){
    unsigned long long Mask = 0; // ej k= 4
    Mask = ~Mask; // 1111111111111111111111111111111
    Mask << k; //11111111111111111111111110000 (k 0's)
    Mask = ~Mask; // 0000000000000000000000001111 (k 1's)
    //int TamañoArray = sizeof(aOrdenar)/sizeof(int); // Tamaño array puede que sea necesario declararlo desde antes
    ParPunteroYBits** ArrayOrdenador = (ParPunteroYBits**)malloc(sizeof(ParPunteroYBits*)*TamañoArray);
    unsigned long long* ArrayOrdenador2 = malloc(sizeof(int)*TamañoArray);
    unsigned long long* ArrayOrdenador3 = malloc(sizeof(unsigned long long)*TamañoArray);
    int BitsPorRecorrer = sizeof(int)*8;
    int BitsRecorridos = k;
    printf("------------------PUNTO DE CONTROL 1--------------------\n");
    while(BitsPorRecorrer > k){
        for(int i = 0; i < TamañoArray; i++){ // Me preocupa si se guarda bien
            ParPunteroYBits* j;
            j -> ptr = i;
            j -> bits = aOrdenar[i]&&Mask;
            ArrayOrdenador[i] = j;
        }
        ArrayOrdenador2 = BucketSort(ArrayOrdenador,k, TamañoArray);
        for(int j = 0 ;j < TamañoArray ;j++ ){
            ArrayOrdenador3[j] = aOrdenar[ArrayOrdenador2[j]];
        } 
        // Mask:  00000000000000000000000000000 1111
        Mask << k; // 0000000000000000000000000 1111 0000
        BitsRecorridos+=k;
        BitsPorRecorrer-= k;
    }
    Mask = 0;
    Mask = ~Mask; // 11111111111111111111111111111
    Mask >> BitsRecorridos; // Si faltaron 3 bits por ejemplo 
    Mask << BitsRecorridos; // 111 00000000000000000000000000
    for(int i = 0; i < TamañoArray; i++){ // Me preocupa si se guarda bien
        ParPunteroYBits* j;
        j -> ptr = i;
        j -> bits = aOrdenar[i]&&Mask;
        ArrayOrdenador[i] = j;
    }
    ArrayOrdenador2 = BucketSort(ArrayOrdenador,BitsPorRecorrer,TamañoArray);
    for(int j = 0 ;j < TamañoArray ;j++ ){
        ArrayOrdenador3[j] = aOrdenar[ArrayOrdenador2[j]];
    }
    return ArrayOrdenador3; 



}