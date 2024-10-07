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
  int **perms = generate_permutations(n_perms, N);
  if(perms==NULL){
    return ERR;
  }

  /*inicia el reloj*/
  int start= clock();
  /* ordernar cada permutacion con la funcion que se pase por method*/
  int i, num_ob, max_ob, min_ob;
  for(i=0, num_ob=0; i<N; i++){
    metodo(perms[i], 0, N-1);
    num_ob++;
  }

  /*termina el reloj*/
  int end= clock();
  /*paso a segundos*/
  short time_in_seconds = (short)(end - start) / CLOCKS_PER_SEC;

  /*estructura de AA_TIME*/
  ptime->average_ob;
  ptime->max_ob;
  ptime->min_ob;
  ptime->N= N;
  ptime->n_elems= n_perms;
  ptime->time= time_in_seconds;

}

/***************************************************/
/* Function: generate_sorting_times Date:11/10/2024*/
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, int num_min, int num_max, int incr, int n_perms)
{
  /* Your code */
}

/***************************************************/
/* Function: save_time_table Date: 11/10/2024      */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  /* your code */
}


