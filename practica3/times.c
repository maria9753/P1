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
#include <stdio.h>
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
  int i, num_ob=0, max_ob=0, min_ob = (N / 2) * (N - 1);
  double time_in_seconds, total_ob=0;
  int **perms = generate_permutations(n_perms, N);
  if(perms==NULL){
    return ERR;
  }

  /*inicia el reloj*/
  start= clock();

  /* ordernar cada permutacion con la funcion que se pase por method*/
  for(i=0; i<n_perms; i++){
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
  ptime->average_ob= total_ob/n_perms;
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
/* Input:                                          */
/* pfunc_sort method: the sorting algoritm         */
/* char* file:the file to store the data           */
/* int num_min: minimum size of the range          */
/* int num_max: maximum size of the range          */
/* int incr: increment for the range               */
/* Output:                                         */
/* short: 0 if the function was succesfull and     */
/* ERR en case of error                            */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, int num_min, int num_max, int incr, int n_perms)
{
  int tamano, i;
  int n_times= (num_max - num_min)/incr +1;

  PTIME_AA ptimes= (PTIME_AA)malloc(n_times*sizeof(ptimes[0]));

  for(tamano=num_min, i=0; tamano<=num_max ;tamano+=incr, i++){
    if(average_sorting_time(method, n_perms, tamano, &ptimes[i])==ERR){
      free(ptimes);
      return ERR;
    }
  }
  
  if(save_time_table(file, ptimes, n_times)==ERR){
    free(ptimes);
    return ERR;
  }

  free(ptimes);

  return OK;
}

/***************************************************/
/* Function: save_time_table Date: 11/10/2024      */
/*                                                 */
/* This function saves to a file a table that      */
/* contains five columns: size(N), execution       */
/* time(time), average Ob, maximum OB and minimum  */
/* OB                                              */
/*                                                 */
/* Input:                                          */
/* char* file: Name of the file where the data will*/
/* be saved                                        */
/* PTIME_AA ptime: structure that holds the data to*/ 
/* be saved                                        */
/* int n_times: number of elements stored          */
/* Output:                                         */
/* short: 0 if the function was succesfull and     */
/* ERR en case of error                            */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  FILE *f;
  int i;

  f= fopen(file, "w");
  if(f==NULL){
    return ERR;
  }

  for(i=0; i<n_times; i++)
    fprintf(f, "%d %f %.4f %d %d\n", ptime[i].N, ptime[i].time, ptime[i].average_ob, ptime[i].max_ob, ptime[i].min_ob);
  
  fclose(f);
  return OK;
}

short generate_search_times(pfunc_search method, pfunc_key_generator generator, int order, char* file, int num_min, int num_max, int incr, int n_times)
{
  int tamano, i;
  int n_size= (num_max - num_min)/incr +1;

  PTIME_AA ptimes= (PTIME_AA)malloc(n_size*sizeof(ptimes[0]));

  if(ptimes==NULL){
    return ERR;
  }

  for(tamano=num_min, i=0; tamano<=num_max ;tamano+=incr, i++){
    if(average_search_time(method, generator, order, tamano, n_times, &ptimes[i])==ERR){
      free(ptimes);
      return ERR;
    }
  }
  
  if(save_time_table(file, ptimes, n_size)==ERR){
    free(ptimes);
    return ERR;
  }

  free(ptimes);

  return OK;
}

short average_search_time(pfunc_search metodo, pfunc_key_generator generator, int order, int N, int n_times, PTIME_AA ptime)
{ 
  PDICT pdict=NULL;
  int *perm=NULL, *keys_table=NULL;
  int tae=0, start=0, end=0, time_in_seconds=0, i=0, result=0, min_ob=N, max_ob=0, ppos=0;

  /*Create a dicctionary of size N*/
  pdict= init_dictionary(N, order);
  if(pdict==NULL){
    return ERR;
  }
 
  /*Create a permutation of size N*/
  perm= generate_perm(N);
  if(perm==NULL){
    free_dictionary(pdict);
    return ERR;
  }

  /*Insert the elements of the permutation into the dicctionary*/
  tae= massive_insertion_dictionary(pdict, perm, N);
  if(tae==ERR){
    free_dictionary(pdict);
    free(perm);
    return ERR;
  }

  /*Create the table of the keys that are going to be searched*/
  keys_table= (int*)malloc(N*n_times*sizeof(int));
  if(keys_table==NULL){
    free_dictionary(pdict);
    free(perm);
    return ERR;
  }
  
  generator(keys_table, N*n_times, N);

  /*Start the clock*/
  start= clock();

  for(i=0; i<n_times*N; i++){
    tae = metodo(pdict->table, 0, pdict->n_data - 1, keys_table[i], &ppos);

    if(tae<min_ob){
      min_ob= tae;
    }
    if(tae>max_ob){
      max_ob=tae;
    } 
    result +=tae;
  }

  /*End the clock*/
  end= clock();
  time_in_seconds = (double)((end - start)/CLOCKS_PER_SEC);

  /*estructura de AA_TIME*/
  ptime->average_ob= result/N*n_times;
  ptime->max_ob= max_ob;
  ptime->min_ob= min_ob;
  ptime->N= N;
  ptime->n_elems= n_times*N;
  ptime->time= time_in_seconds;

  free_dictionary(pdict);
  free(keys_table);
  free(perm);
  return OK;                      
}
