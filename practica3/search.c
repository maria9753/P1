/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include <stdlib.h>
#include <math.h>
#include "search.h"
#include "swap.h"

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be 
 *				 allocated externally to the function.
 */
  
/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more 
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) 
  {
    keys[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  }

  return;
}

PDICT init_dictionary (int size, char order)
{
	PDICT pdict=NULL;
  int i=0;

  pdict= (PDICT)malloc(sizeof(DICT));

  if( pdict==NULL )
  {
    return NULL;
  }

  pdict->table= (int*)malloc(size*sizeof(pdict->table[0]));

  if(pdict->table==NULL)
  {
    free(pdict);
    return NULL;
  }

  pdict->size= size;
  pdict->n_data= 0;
  pdict->order= order;
  for(i=0; i<size; i++)
  {
    pdict->table[i]=0;
  }

  return pdict;
}

void free_dictionary(PDICT pdict)
{
	free(pdict->table);
  free(pdict);
  return;
}

int insert_dictionary(PDICT pdict, int key)
{
  int tae=0;
  int A, j= pdict->n_data - 1;              

	if(pdict==NULL)
  {
    return ERR;
  }

  if (pdict->n_data < pdict->size) 
  {
    pdict->table[pdict->n_data]=key;
    pdict->n_data++;
    tae++;
  }

  if(pdict->order==SORTED)
  {
    A= pdict->table[pdict->n_data - 1];

    while(j>=0 && pdict->table[j]>A){
      pdict->table[j+1]=pdict->table[j];
      tae++;
      j--;
    }

    pdict->table[j+1]=A;
  }

  return tae;
}

int massive_insertion_dictionary (PDICT pdict, int *keys, int n_keys)
{
  int tae=0, i, result=0;

  if(pdict==NULL || keys==NULL){
    return ERR;
  }

  for(i=0; i<n_keys; i++){
    tae=insert_dictionary(pdict, keys[i]);
    if(tae==ERR){
      return ERR;
    }
    result +=tae;
  }
	
  return result;
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method)
{
	if(pdict==NULL)
  {
    return ERR;
  }

  return method(pdict->table, 0, pdict->n_data - 1, key, ppos);
}


/* Search functions of the Dictionary ADT */
int bin_search(int *table,int F,int L,int key, int *ppos)
{
	int medio = F + (L - F) / 2;
  int tae1 = 0, tae2=0;

  if (F > L) {
    *ppos = -1;
    return NOT_FOUND;
  }

  tae1++;
  if(table[medio] == key) 
  {
    *ppos = medio;
    return tae1;
  } 
  
  else if (table[medio] > key)
  {
    tae2=bin_search(table, F, medio - 1, key, ppos);
    if(tae2==NOT_FOUND){
      return NOT_FOUND;
    }
    return tae1 + tae2;
  } 
  
  else 
  {
    tae2=bin_search(table, medio + 1, L, key, ppos);
    if(tae2==NOT_FOUND){
      return NOT_FOUND;
    }
    return tae1 + tae2;
  }
}

int lin_search(int *table,int F,int L,int key, int *ppos)
{
  int i, tae = 0;

  for (i = F; i <= L; i++)
  {
    tae++;
    if (table[i] == key)
    {
      *ppos = i;
      return tae;
    }
  }

  return NOT_FOUND;
}

int lin_auto_search(int *table,int F,int L,int key, int *ppos)
{
	int i, tae = 0;

  for (i = F; i <= L; i++)
  {
    tae++;
    if (table[i] == key)
    {
      *ppos = i;
      if (i > 0) 
      {
        swap(&table[i], &table[i - 1]);
      }
      return tae;
    }
  }
  *ppos = -1;
  return NOT_FOUND;
}


