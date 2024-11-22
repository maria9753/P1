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


/***************************************************/
/* Function: MergeSort       Date: 16/11/2024      */
/*                                                 */
/* This function sorts a table of numbers using    */
/* the merge technique, which consists on dividing */
/* the table until they are only numbers, and then */
/* use merge to join them all ordered              */
/*                                                 */
/* Input:                                          */
/* int *tabla: The permutation that will be sorted */
/* int ip: the index of the lowest element         */ 
/* int iu: the index of the highest element        */ 
/* Output:                                         */
/* int: the execution time of the algorithm        */
/***************************************************/
int mergesort(int* tabla, int ip, int iu){
  int imedio, tae1=0, tae2=0, tae3=0;

  if(ip > iu)
    return ERR;
  else if(ip == iu)
    return OK;

  else{
    if((ip+iu)%2==0)
      imedio= (ip+iu)/2;

    else
      imedio= (ip+iu-1)/2;

    tae1= mergesort(tabla, ip, imedio);
    tae2= mergesort(tabla, imedio + 1, iu);
    tae3= merge(tabla, ip, iu, imedio);
  
    if(tae1==ERR || tae2==ERR || tae3==ERR){
      return ERR;
    }
    }

    return tae1 + tae2 + tae3;
}

/***************************************************/
/* Function: Merge           Date: 16/11/2024      */
/*                                                 */
/* This function joins tables of numbers but       */
/* sorting them until the last one is the original */
/* table sorted                                    */
/*                                                 */
/* Input:                                          */
/* int *tabla: The permutation that will be sorted */
/* int ip: the index of the lowest element         */ 
/* int iu: the index of the highest element        */ 
/* int imedio: the index of the medium element     */ 
/* Output:                                         */
/* int: the execution time of the algorithm        */
/***************************************************/
int merge(int* tabla, int ip, int iu, int imedio){

  int *tabla_aux= (int*)malloc((iu - ip + 1)*sizeof(tabla_aux[0]));
  int i=ip, j=imedio+1, k=ip, tae=0;

  if(tabla_aux==NULL){
    return ERR;
  }

  while(i <= imedio && j <= iu){
    tae++;
    if(tabla[i]<tabla[j]){
      tabla_aux[k - ip]=tabla[i];
      i++;
    }
      
    else{
      tabla_aux[k - ip]=tabla[j];
      j++;
    }

    k++;
  }  

  if(i>imedio){
    while(j<=iu){
      tabla_aux[k - ip]=tabla[j];
      j++;
      k++;
    }
  }

  else if(j>iu){
    while(i<=imedio){
      tabla_aux[k - ip]=tabla[i];
      i++;
      k++;
    }
  }

  for (k = 0; k <= iu - ip; k++) {
    tabla[ip + k] = tabla_aux[k];
  }

  free(tabla_aux);
  return tae;
}

/***************************************************/
/* Function: HeapSort        Date: 16/11/2024      */
/*                                                 */
/* This function sorts a table of numbers using    */
/* a heap, whcih is created first, and then sorted */
/*                                                 */
/* Input:                                          */
/* int *tabla: The permutation that will be sorted */
/* int ip: the index of the lowest element         */ 
/* int iu: the index of the highest element        */ 
/* Output:                                         */
/* int: the execution time of the algorithm        */
/***************************************************/
int heapsort(int *tabla, int ip, int iu) {
  int tae1 = CrearHeap(tabla, iu - ip + 1);
  int tae2 = OrdenarHeap(tabla, iu - ip + 1);
  
  if (tae1 == ERR || tae2 == ERR) {
    return ERR;
  }
  
  return tae1 + tae2;
}

/***************************************************/
/* Function: CrearHeap        Date: 16/11/2024     */
/*                                                 */
/* This function creates the heap                  */
/*                                                 */
/* Input:                                          */
/* int *tabla: The permutation that will be sorted */
/* int n: the amount of elements of the table      */ 
/* Output:                                         */
/* int: the execution time of the algorithm        */
/***************************************************/
int CrearHeap(int* tabla, int n) {
  int i = 0, tae = 0, result=0;

  if (n == 1)
    return 0;

  for (i = n / 2 -1 ; i >= 0; i--) {
    result = Heapify(tabla, n, i);
    if (result == ERR) {
      return ERR;
    }
    tae += result;
  }
  
  return tae;
}

/***************************************************/
/* Function: OrdenarHeap        Date: 16/11/2024   */
/*                                                 */
/* This function sorts the heap                    */
/*                                                 */
/* Input:                                          */
/* int *tabla: The permutation that will be sorted */
/* int n: the amount of elements of the table      */ 
/* Output:                                         */
/* int: the execution time of the algorithm        */
/***************************************************/
int OrdenarHeap(int* tabla, int n) {
  int i = 0, tae = 0, result = 0;
  
  for (i = n - 1; i > 0; i--) {
    swap(&tabla[0], &tabla[i]);
    result = Heapify(tabla, i, 0);
    if (result == ERR) {
      return ERR;
    }
    tae += result;
  }

  return tae;
}

/***************************************************/
/* Function: Heapify          Date: 16/11/2024     */
/*                                                 */
/* This function ensures that the table keeps      */
/* being a max heap in each iteration              */
/*                                                 */
/* Input:                                          */
/* int *tabla: The permutation that will be sorted */
/* int n: the amount of elements of the table      */ 
/* int i: the position of the cahged element       */
/* Output:                                         */
/* int: the execution time of the algorithm        */
/***************************************************/
int Heapify(int *tabla, int n, int i) {
  int ind = 0, tae = 0;
  
  while (2 * i + 1 < n) {
    ind = max(tabla, n, i, 2 * i + 1, 2 * i + 2, &tae);
    if (ind != i) {
      swap(&tabla[i], &tabla[ind]);
      i = ind;
    } else {
      break;
    }
  }

  return tae;
}

/***************************************************/
/* Function: max              Date: 16/11/2024     */
/*                                                 */
/* This function selects which child is not        */
/* satisfying the max heap condition               */
/*                                                 */
/* Input:                                          */
/* int *tabla: The permutation that will be sorted */
/* int n: the amount of elements of the table      */ 
/* int i1: the father node                         */
/* int i2: the left son of the node                */
/* int i3: the rigth son of the node               */ 
/* int tae: the time of execution of the algorithm */
/* Output:                                         */
/* int: the index that has to be moved             */
/***************************************************/
int max (int *tabla, int n, int i1, int i2, int i3, int *tae) {
  int ind_max=i1;
  
  if (i2 < n) {
    (*tae)++;
    if (tabla[i2] > tabla[ind_max]) {
      ind_max = i2;
    }
  }

  if (i3 < n) {
    (*tae)++;
    if (tabla[i3] > tabla[ind_max]) {
      ind_max = i3;
    }
  }

  return ind_max;
}
  