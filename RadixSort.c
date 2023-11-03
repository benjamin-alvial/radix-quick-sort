#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "BucketSort.c"

unsigned long long* RadixSort(unsigned long long* aOrdenar, int u, int k, int TamañoArray){
    //long long Mask = 0; // ej k= 4
    //Mask = ~Mask; // 1111111111111111111111111111111
    //printf("Mask:%d\n",Mask);
    //Mask << k; //11111111111111111111111110000 (k 0's)
    //printf("Mask:%d\n",Mask);
    //Mask = ~Mask; // 0000000000000000000000001111 (k 1's)
    //int TamañoArray = sizeof(aOrdenar)/sizeof(int); // Tamaño array puede que sea necesario declararlo desde antes
    unsigned long long Mask = (1ULL << k) - 1;
    ParPunteroYBits* ArrayOrdenador = (ParPunteroYBits*)malloc(sizeof(ParPunteroYBits*)*TamañoArray);
    unsigned long long* ArrayOrdenador2 = malloc(sizeof(unsigned long long)*TamañoArray);
    unsigned long long* ArrayOrdenador3 = malloc(sizeof(unsigned long long)*TamañoArray);
    int BitsPorRecorrer = sizeof(unsigned long long)*8;
    int BitsRecorridos = 0;
    while(BitsPorRecorrer > k){
        for(int i = 0; i < TamañoArray; i++){ // Me preocupa si se guarda bien
            //ParPunteroYBits* j;
            unsigned long long bit = aOrdenar[i]&Mask;
            bit = bit >> BitsRecorridos;
            ParPunteroYBits PPYB= {i,bit}; ///10&01 ---> 00
            //j = &PPYB;
            printf("------------------i:%d///aOrdenar:%d///bits:%d/// MASK:%d  -------------------\n",i,aOrdenar[i],aOrdenar[i]&Mask,Mask);
            //j -> ptr = i;
            //j -> bits = aOrdenar[i]&Mask;
            ArrayOrdenador[i] = PPYB;
        }

        ArrayOrdenador2 = BucketSort(ArrayOrdenador,k, TamañoArray); //  
        for(int a = 0; a < TamañoArray;a++){
            printf("ArrayOrdenador2[%d]: %d\n",a,ArrayOrdenador2[a]);
        }
        printf("------------------PUNTO DE CONTROL FUERA DEL BUCKET SORT : %d-------------------\n", BitsPorRecorrer);
        for(int ptr = 0 ;ptr < TamañoArray ;ptr++ ){
            ArrayOrdenador3[ptr] = aOrdenar[ArrayOrdenador2[ptr]]; // ArrayOrdenador2 = {5 ,8 ,9] --> ArrayOrdenador3 = {aOrdenar[5], aOrdenar[8], aOrdenar[9]}
        }
        for(int ptr = 0; ptr< TamañoArray; ptr++){
            aOrdenar[ptr] = ArrayOrdenador3[ptr];
        }
        for(int a = 0; a <TamañoArray;a++){
          printf("aOrdenar[%d] = %d\n",a,aOrdenar[a]);
        }
        // Mask:  00000000000000000000000000000 1111
        Mask = Mask << k; // 0000000000000000000000000 1111 0000
        printf("--------------------MASK: %d-----------------------\n", Mask);
        BitsRecorridos+=k;
        BitsPorRecorrer-= k;
        printf("------------------Bits por recorrer: %d--------------------\n",BitsPorRecorrer);
        free(ArrayOrdenador2);
        free(ArrayOrdenador3);
    }
    ArrayOrdenador2 = malloc(sizeof(unsigned long long)*TamañoArray);
    ArrayOrdenador3 = malloc(sizeof(unsigned long long)*TamañoArray);
    printf("------------------PUNTO DE CONTROL 2--------------------\n");
    Mask = 0;
    Mask = ~Mask; // 11111111111111111111111111111
    Mask >> BitsRecorridos; // Si faltaron 3 bits por ejemplo 
    Mask << BitsRecorridos; // 111 00000000000000000000000000
    for(int i = 0; i < TamañoArray; i++){ // Me preocupa si se guarda bien
        ParPunteroYBits j;
        j.ptr = i;
        j.bits = aOrdenar[i]&Mask;
        ArrayOrdenador[i] = j;
    }
    ArrayOrdenador2 = BucketSort(ArrayOrdenador,BitsPorRecorrer,TamañoArray);
    for(int j = 0 ;j < TamañoArray ;j++ ){
        ArrayOrdenador3[j] = aOrdenar[ArrayOrdenador2[j]];
    }
    free(ArrayOrdenador3);
    free(ArrayOrdenador2);
    free(ArrayOrdenador);
    return ArrayOrdenador3; 



}