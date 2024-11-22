/**
 *
 * Descripcion: Swap function implementation
 *
 * Fichero: swap.c
 * Autor: Carmen Gómez, María Pozo 
 * Version: 1.1
 * Fecha: 7-10-2024
 *
 */

#include "swap.h"

/***************************************************/
/* Function: swap Date: 27/09/2024                 */
/* Authors: Carmen Gómez, María Pozo               */
/*                                                 */
/* Function that swaps the position two given      */
/* elements                                        */
/*                                                 */
/* Input:                                          */
/* int element1: element located in the lower      */
/* position                                        */
/* int element2: element in the higher position    */
/***************************************************/
void swap(int *element1, int *element2) {
  int aux = *element1;
  *element1 = *element2;
  *element2 = aux;
}

