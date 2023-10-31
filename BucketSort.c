#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct ParPunteroYBits {
    int ptr;
    unsigned long long bits;
} ParPunteroYBits;

ParPunteroYBits** BucketSort( ParPunteroYBits** aOrdenar, int u ){ // Se asume U = [1,u]
    int* ArrayContador = malloc(sizeof(int)*(u+1)); // Array que almacena el contador de cada elemento de u
    int TamañoArray = sizeof(aOrdenar)/sizeof(ParPunteroYBits);
    ParPunteroYBits** NuevoArray = malloc(sizeof(ParPunteroYBits)*TamañoArray);
    ArrayContador[0] = 1;
    for(int i = 0; i < u+1; i++){
        ArrayContador[i] = 0;
    }
    for(int j = 0; j < TamañoArray;j++){
        ArrayContador[aOrdenar[j]->bits+1]++;
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