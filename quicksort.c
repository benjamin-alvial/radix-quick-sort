#include <stdlib.h>

// Función para swapear dos valores
void swap(unsigned long long *a, unsigned long long *b)
{
    unsigned long long t = *a;
    *a = *b;
    *b = t;
}

// Función para elegir un pivot aleatorio y reordenar el array para que
// los elementos menores al pivot queden a su izquierda y los mayores a su derecha
int partition(unsigned long long arr[], int low, int high)
{

    int random_index = low + rand() % (high - low + 1);
    swap(&arr[random_index], &arr[high]);

    unsigned long long pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        // Si el elemento actual es menor o igual al pivote
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Función principal
void quicksort(unsigned long long arr[], int low, int high)
{
    if (low < high)
    {

        int partitioning_index = partition(arr, low, high);

        // Implementar quicksort para el arreglo de la izquierda y de la derecha
        quicksort(arr, low, partitioning_index - 1);
        quicksort(arr, partitioning_index + 1, high);
    }
}
