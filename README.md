# radix-quick-sort
Se implementan dos métodos para ordenar arreglos de enteros: radix sort y quicksort. Se crean y ordenan arreglos de tamaño fijo y sobre distintos universos para ver la variación de los tiempos de ordenamiento en función del tamaño del universo. Además, se estudia el número de bits óptimo para utilizar en el algoritmo de radix sort.

## Pipeline
En `pipeline.c` está el flujo general de la generación de arreglos y el ordenamiento de ellos. En él, se deben especificar los parámetros del problema.

- `U_POW_INITIAL` es la primera potencia de 2 de universo a probar.
- `U_POW_FINAL` es la última potencia de 2 de universo a probar.
- `NUMBER_REPS` es la cantidad de repeticiones para realizar un ordenamiento sobre un mismo arreglo.
- `ARRAY_SIZE` es el tamaño fijo de los arreglos a ordenar.

Se debe compilar y ejecutar `pipeline.c` con gcc, con la opción `-lm` para calcular potencias:

```
$ gcc -o pipeline pipeline.c -lm
$ ./pipeline
```

Al compilar y ejecutarse, se itera sobre las potencias de 2 dadas y para cada una de ellas:
- Se crea un arreglo de enteros aleatorios en el universo.
- Se itera sobre los valores de k y para cada uno de estos se realiza la cantidad especificada de repeticiones de radix sort y quicksort sobre el arreglo.
- Se escribe en un archivo de texto la tupla que contiene al tamaño del universo, al número de bits k, el número de la repetición, el tiempo de ordenamiento de radix sort y el tiempo de ordenamiento de quicksort.

Los resultados quedan finalmente en `performance_results.txt`.

## Radix sort
En `radixsort.c` está la implementación del ordenamiento radix sort.

## Quicksort
En `quicksort.c` está la implementación del ordenamiento quicksort.

## Resultados
En `plot_results.py` está la implementación para encontrar los gráficos de número de bits k óptimo para valores del universo en radix sort y la comparación entre los métodos de ordenamiento en función del tamaño del universo u.