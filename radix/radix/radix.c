#include "Radix.h"

int charAt(const char* s, int d){
    return (d < strlen(s)) ? (unsigned char)s[d] : -1;
}

void radixSortMSD_aux(char** a, char** aux, int lo, int hi, int d)
{
    if (hi <= lo) return;

    int count[HUNDRED_TWENTY_EIGHT + 2] = {0};

    for (int i = lo; i <= hi; i++) {
        int c = charAt(a[i], d);
        count[c + 2]++;
    }

    for (int r = 0; r < HUNDRED_TWENTY_EIGHT + 1; r++) {
        count[r + 1] += count[r];
    }

    for (int i = lo; i <= hi; i++) {
        int c = charAt(a[i], d);
        aux[count[c + 1]++] = a[i];
    }

    for (int i = lo; i <= hi; i++) {
        a[i] = aux[i - lo];
    }

    for (int r = 0; r < HUNDRED_TWENTY_EIGHT; r++) {
        radixSortMSD_aux(a, aux, lo + count[r], lo + count[r + 1] - 1, d + 1);
    }
}

void radixSortMSD(char** a, int n)
{
    char** aux = malloc(n * sizeof(char*));
    if (aux == NULL) {
        printf("Error with the memory allocation.\n");
        return;
    }

    radixSortMSD_aux(a, aux, 0, n - 1, 0);
    free(aux);
}
