/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre, Carmen Gómez, María Pozo
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */


#include "sorting.h"
#include "swap.h"

/***************************************************/
/* Function: SelectSort    Date:04/10/2024         */
/* Your comment                                    */
/***************************************************/
int BubbleSort(int* array, int ip, int iu)
{
  int i, tae = 0;

  for (i = iu; i > ip; i--) {
    int j;
    for (j = ip; j < i; j++) {
      tae++;
      if (array[j] > array[j + 1])
        swap(&array[j], &array[j + 1]);
    }
  }
  return tae;
}

int BubbleSortFlag(int* array, int ip, int iu)
{
  int i, tae = 0, flag=0;

  for (i = iu; i > ip; i--) {
    int j;
    for (j = ip; j < i; j++) {
      tae++;
      if (array[j] > array[j + 1]){
        swap(&array[j], &array[j + 1]);
        flag=1;
      }
    }

    if(flag==0){
      break;
    }
  }
  return tae;
}



