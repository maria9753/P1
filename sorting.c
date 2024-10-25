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
/* Function: BubbleSort      Date: 11/10/2024      */
/*                                                 */
/* This function sorts a table of numbers using    */
/* the bubble technique                            */
/*                                                 */
/* Input:                                          */
/* int *array: The permutation that will be sorted */
/* int ip: the index of the lowest element         */ 
/* int iu: the index of the highest element        */ 
/* Output:                                         */
/* int: the execution time of the algorithm        */
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

/***************************************************/
/* Function: BubbleSortFlag  Date: 18/10/2024      */
/*                                                 */
/* This function sorts a table of numbers using    */
/* the bubble technique, but adding a flag to that */
/* is activated if the table is already sorted,    */
/* returns the algorithms tae                      */
/*                                                 */
/* Input:                                          */
/* int *array: The permutation that will be sorted */
/* int ip: the index of the lowest element         */ 
/* int iu: the index of the highest element        */ 
/* Output:                                         */
/* int: the execution time of the algorithm        */
/***************************************************/
int BubbleSortFlag(int* array, int ip, int iu)
{
  int i, tae = 0;

  for (i = iu; i > ip; i--) {
    int j, flag=0;
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


int mergesort(int* tabla, int ip, int iu){
  int imedio;

  if(ip>iu)
    return ERR;

  else if(ip==iu)
    return OK;

  else{
    if((ip+iu)%2==0)
      imedio= (ip+iu)/2;

    else
      imedio= (ip+iu-1)/2;

    mergesort(tabla, ip, imedio);
    mergesort(tabla, imedio+1, iu);

    return merge(tabla, ip, iu, imedio);
    }
}
int merge(int* tabla, int ip, int iu, int imedio){

  int *tabla_aux= (int*)malloc((iu-ip+1)*sizeof(tabla_aux[0]));

  if(tabla_aux==NULL){
    return ERR;
  }

  int i=ip, j=imedio+1, k=ip;

  while(i<=imedio && j<=iu){
    if(tabla[i]<tabla[j])
      i++;
    else
      k++;
  }  

  if(i>imedio){
    while(j<=iu){
      tabla_aux[k]=tabla[j];
      j++;
      k++;
    }
  }

  else if(j>iu){
    while(i<=imedio){
      tabla_aux[k]=tabla[i];
      i++;
      k++;
    }
  }

  if(copy(tabla_aux, tabla, ip, iu)==ERR){
    return ERR;
  }

  free(tabla_aux);
  return OK;
}

int copy(int *tabla_aux, int *tabla, int ip, int iu){
  int i;
  for(i=0; i<iu; i++){
    tabla[ip+i]=tabla_aux[i];
  }

  return OK;
}

