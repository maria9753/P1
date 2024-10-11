/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso, Carmen Gómez, María Pozo
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include <time.h>
#include "times.h"
#include "sorting.h"

/***************************************************/
/* Function: average_sorting_time Date: 11/10/2024 */
/*  Authors: Carmen Gómez, María Pozo              */
/*                                                 */
/* Function that generates the average sorting     */
/* time of the algorithm introduced                */
/*                                                 */
/* Input:                                          */
/* pfunc_sort metodo: Which sorting algorithm      */
/* int n_perms: Number of permutations generated   */
/* int N: Number of elements in each permutation   */
/* PTIME_AA ptime: Structure where th information  */
/* is going to be stored                           */
/* Output:                                         */
/* short: Average time that took the algorithm to  */
/* sort each permutation                           */
/* -1 en case of error                             */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, int n_perms, int N, PTIME_AA ptime)
{
  /* generamos las permutaciones, tantas como indique n_perms y N*/
  clock_t start, end;
  int i, num_ob=0, total_ob=0, max_ob=0, min_ob=N*(N-1)/2;
  double time_in_seconds;
  int **perms = generate_permutations(n_perms, N);
  if(perms==NULL){
    return ERR;
  }

  /*inicia el reloj*/
  start= clock();
  /* ordernar cada permutacion con la funcion que se pase por method*/
  for(i=0; i<N; i++){
    num_ob =metodo(perms[i], 0, N-1);

    total_ob += num_ob;

    if(num_ob<min_ob)
      min_ob= num_ob;

    if(num_ob>max_ob)
      max_ob=num_ob;
  }
  /*termina el reloj*/
  end= clock();
  /*paso a segundos*/
  time_in_seconds = (double)((end - start)/CLOCKS_PER_SEC)/n_perms;

  /*estructura de AA_TIME*/
  ptime->average_ob= num_ob;
  ptime->max_ob= max_ob;
  ptime->min_ob= min_ob;
  ptime->N= N;
  ptime->n_elems= n_perms;
  ptime->time= time_in_seconds;

  for(i=0; i<n_perms; i++){
    free(perms[i]);
  }
  free(perms);

  return 0;
}

/***************************************************/
/* Function: generate_sorting_times Date:11/10/2024*/
/*                                                 */
/* This function saves to a file the average times,*/
/* the average, minimum and maximum number of      */
/* times that the OB has been executed by the      */
/* selected sorting algoritm                       */
/*                                                 */
/* pfunc_sort method: the sorting algoritm         */
/* char* file:the file to store the data           */
/* int num_min: minimum size of the range          */
/* int num_max: maximum size of the range          */
/* int incr: increment for the range               */
/* int n_perms: number of permutations generated   */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, int num_min, int num_max, int incr, int n_perms)
{
  return 0;
}

/***************************************************/
/* Function: save_time_table Date: 11/10/2024      */
/*                                                 */
/* This function saves to a file a table that      */
/* contains five columns: size(N), execution       */
/* time(time), average Ob, maximum OB and minimum  */
/* OB                                              */
/*                                                 */
/* char* file: Name of the file where the data will*/
/* be saved                                        */
/* PTIME_AA ptime: structure that holds the data to*/ 
/* be saved                                        */
/* int n_times: number of elements stored          */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  return 0;
}


