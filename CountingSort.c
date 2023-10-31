#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int CountingSort(int* aOrdenar, int u) {
    int TamañoArray = sizeof(aOrdenar)/sizeof(int);
    int* ArrayContador = malloc(sizeof(int)*u);     
    int* NuevoArray = malloc(sizeof(int)*TamañoArray);
    for(int i = 0; i < u; i++){
        ArrayContador[i] = 0;
    }
    for(int j = 0; j < TamañoArray;j++){
        ArrayContador[aOrdenar[j]]++;
    }
    int posicion = 0;
    for(int k = 0; k < u; k++){
        while(ArrayContador[k]!= 0){
            NuevoArray[posicion] = k;
            ArrayContador[k]--;
            posicion++;
        }
    }
    return NuevoArray;





}