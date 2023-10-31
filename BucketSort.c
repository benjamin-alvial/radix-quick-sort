#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "CountingSort.c"

int BucketSort(int* aOrdenar, int u ){ // Se asume U = [1,u]
    int* ArrayContador = malloc(sizeof(int)*(u+1));
    int TamañoArray = sizeof(aOrdenar)/sizeof(int);
    int* NuevoArray = malloc(sizeof(int)*TamañoArray);
    ArrayContador[0] = 1;
    for(int i = 0; i < u+1; i++){
        ArrayContador[i] = 0;
    }
    for(int j = 0; j < TamañoArray;j++){
        ArrayContador[aOrdenar[j]+1]++;
    }
    for(int k = 1; k < u+1; k++){
        ArrayContador[k] = ArrayContador[k]+ArrayContador[k-1];
    }
    int Actual = 1;
    for(int L = 0; L < u+1; L++){
        while(Actual < ArrayContador[L]){
            NuevoArray[Actual-1] = L;
            Actual++;
        }
    }
    return NuevoArray;   
    

    
}