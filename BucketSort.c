#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct ParPunteroYBits {
    int ptr;
    unsigned long long bits;
}ParPunteroYBits;
typedef struct LinkedList {
    int ptr;
    LinkedList* next;
}LinkedList;


// Este BucketSort será utilizado para ordenar arrays de ParPunteroYBits los cuales tienen k bits guardados
int* BucketSort( ParPunteroYBits** aOrdenar, int k, int TamañoArray ){ // u Ahora es el numero de bits que tiene el  campo bits del arreglo aOrdenar
    int NumMaximo = 0;
    for(int a = k-1; a >-1; a--){ // La idea es que NumMaximo guarde 2^k + 2^(k-1) + ... + 2^1 + 2^0
        NumMaximo+= pow(2,a);      // Ej : k = 4 bits -> 2^3 + 2^2 + 2^1 + 2^0 = 8+4+2+1 = 15
    }

    // Creamos un array de Ej 15+1 Listas Enlazadas que guardarán los punteros
    LinkedList** ArrayContador = (LinkedList**)malloc((NumMaximo+1)*sizeof(LinkedList));
    for(int i = 0; i < NumMaximo+1;i++){
        LinkedList* j;
        j->ptr = -1;
        j->next = NULL;
        ArrayContador[i] = j;
    }

    // Tamaño array aOrdenar
    //int TamañoArray = sizeof(aOrdenar)/sizeof(ParPunteroYBits);

    // Recorremos aOrdenar y ponemos los ptr que almacenan sus elementos en su LinkedList correspondiente
    for(int k = 0; k < TamañoArray;k++){
        LinkedList* Objetivo = ArrayContador[aOrdenar[k]->bits+1];
        while(Objetivo->next != NULL){
            Objetivo = Objetivo->next;
        }
        LinkedList* l;
        l->ptr = aOrdenar[k]->ptr;
        l->next = NULL;
        Objetivo->next = l;
    }

    // Creamos un nuevo array para almacenar los elementos ordenados
    int* NuevoArray = malloc(sizeof(int)*TamañoArray);
    int posActual = 0;
    // Recorremos el ArrayContador llevandonos los punteros que almacena en las LinkedList de forma ordenada
    for(int k = 0; k < NumMaximo+1;k++){
        LinkedList* Actual = ArrayContador[k];
        while(Actual != NULL){
            if(Actual->ptr != -1){
                NuevoArray[posActual] = Actual->ptr;
                posActual++;
            }
            Actual = Actual->next;
        }
    }
    return NuevoArray;
}

// IMPORTANTE
// NO ESTOY SEGURO SI LA FORMA DE UTILIZACION DEL SIZEOF FUNCIONA, PUES LEÍ QUE NO FUNCIONA PARA ESTRUCTURAS CREADAS POR LO TANTO
// HABRÍA QUE TENER COMO PARAMETRO FIJO EL TAMAÑO DEL ARRAY QUE SON 100 M GUARDADO EN ALGÚN LADO DE SER ASÍ