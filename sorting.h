/**
 *
 * Descripcion: Header file for sorting functions 
 *
 * Fichero: sorting.h
 * Autor: Carlos Aguirre, Carmen Gómez, María Pozo
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#ifndef SORTING_H
#define SORTING_H

#include "permutations.h"

/* constants */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

/* type definitions */
typedef int (* pfunc_sort)(int*, int, int);

/* Functions */

int BubbleSort(int* array, int ip, int iu);
int BubbleSortFlag(int* array, int ip, int iu);

int mergesort(int* tabla, int ip, int iu);
int merge(int* tabla, int ip, int iu, int imedio);
int copy(int *tabla_aux, int *tabla, int ip, int iu);

#endif
