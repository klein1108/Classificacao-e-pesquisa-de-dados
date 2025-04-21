#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HUNDRED_TWENTY_EIGHT 128

void radixSortMSD_aux(char** a, char** aux, int lo, int hi, int d);
void radixSortMSD(char** a, int n);
int charAt(const char* s, int d);
