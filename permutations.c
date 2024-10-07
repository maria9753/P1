/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre, Carmen Gómez, María Pozo
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */


#include "permutations.h"
#include "swap.h"

/***************************************************/
/* Function: random_num Date: 27/09/2024           */
/* Authors: Carmen Gómez, María Pozo               */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup)
{
  return rand () % (sup - inf + 1) + inf;
}

/***************************************************/
/* Function: generate_perm Date: 27/09/2024        */
/* Authors: Carmen Gómez, María Pozo               */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int* generate_perm(int N)
{
  int i;
  int *perm = (int*) malloc (N * sizeof(int));

  for (i = 0; i < N; i++) 
    perm[i] = i + 1;
  
  for (i = 0; i < N; i++) 
    swap(&perm[i], &perm[random_num(i, N - 1)]);
  
  return perm;
}

/***************************************************/
/* Function: generate_permutations Date:04/10/2024 */
/* Authors: Carmen Gómez, María Pozo               */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int** generate_permutations(int n_perms, int N)
{
  int i;

  int **perms = (int**) malloc (n_perms * sizeof(int*));

  for (i = 0; i < n_perms; i++) 
    perms[i] = generate_perm(N);
  
  return perms;
}

