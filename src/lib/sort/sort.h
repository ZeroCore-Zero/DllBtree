#ifndef SORTMETHOD_H_
#define SORTMETHOD_H_

// #ifdef __cplusplus
// extern "C" {
// #endif

#ifndef tartype
#define tartype double
#endif

#include "chainchart.h"

void insertsort(tartype val[],int num);
void bbsort(tartype val[],int num);
// void shellsort(tartype val[],int num);
void quicksort(tartype number[], int first, int last);

// #ifdef __cplusplus
// }
// #endif

#endif