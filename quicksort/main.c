#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_ARRAY 1000000

#define MEDIANA 0
#define RANDOM 1

#define HOARE 0
#define LOMUTO 1

void quicksort(int c[], int i, int f, int* troca, int* rec, int tipo, int part);
int mediana_de_3(int c[], int x, int y, int z);
int particao_lomuto(int C[], int left, int right, int* trocas);
int particao_hoare(int C[], int left, int right, int* trocas);



int main() {

    srand(time(NULL));

    clock_t start, end;
    double cpu_time_used;

    int *vetorRandomLomuto = (int *)malloc(TAM_ARRAY * sizeof(int));
    int *vetorRandomHoare = (int *)malloc(TAM_ARRAY * sizeof(int));
    int *vetorMedianaLomuto = (int *)malloc(TAM_ARRAY * sizeof(int));
    int *vetorMedianaHoare = (int *)malloc(TAM_ARRAY * sizeof(int));

    int troca=0, rec = 0;

    for ( int i = 0 ; i < TAM_ARRAY ; i++)
    {
        int num = rand() % TAM_ARRAY;
        vetorRandomLomuto[i] =  num;
        vetorRandomHoare[i] = num;
        vetorMedianaLomuto[i] = num;
        vetorMedianaHoare[i] = num;
    }


    printf("QuickSort Random Lomuto: \n");
    start = clock();

    quicksort(vetorRandomLomuto, 0, TAM_ARRAY - 1, &troca, &rec, RANDOM, LOMUTO);

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Tempo: %f segundos\n", cpu_time_used);
    printf("Com %d trocas e %d recurcoes\n\n", troca, rec);

    troca = 0;
    rec = 0;




    printf("QuickSort Random Hoare: \n");
    start = clock();

    quicksort(vetorRandomHoare, 0, TAM_ARRAY - 1, &troca, &rec, RANDOM, HOARE);

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Tempo: %f segundos\n", cpu_time_used);
    printf("Com %d trocas e %d recurcoes\n\n", troca, rec);

    troca = 0;
    rec = 0;




    printf("QuickSort Mediana Lomuto: \n");

    start = clock();
    quicksort(vetorMedianaLomuto, 0, TAM_ARRAY - 1, &troca, &rec, MEDIANA, LOMUTO);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Tempo: %f segundos\n", cpu_time_used);
    printf("Com %d trocas e %d recurcoes\n\n", troca, rec);

    troca = 0;
    rec = 0;




    printf("QuickSort Mediana Hoare: \n");
    start = clock();

    quicksort(vetorMedianaHoare, 0, TAM_ARRAY - 1, &troca, &rec, MEDIANA, HOARE);

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Tempo: %f segundos\n", cpu_time_used);
    printf("Com %d trocas e %d recurcoes\n\n", troca, rec);

    troca = 0;
    rec = 0;


    free(vetorRandomLomuto);
    free(vetorRandomHoare);
    free(vetorMedianaLomuto);
    free(vetorMedianaHoare);

    return 0;
}

int particao_lomuto(int vet[], int esq, int dir, int* contaTrocas){
    int chave = vet[esq];
    int storeindex = esq + 1;
    int aux;

    for (int i = esq+1; i <= dir; i++){
        if (vet[i] < chave){

            aux = vet[i];
            vet[i] = vet[storeindex];
            vet[storeindex] = aux;

            (*contaTrocas)++;
            storeindex++;
        }
    }

    aux = vet[esq];
    vet[esq] = vet[storeindex-1];
    vet[storeindex-1] = aux;

    (*contaTrocas)++;

    return (storeindex-1);
}

int particao_hoare(int vet[], int esq, int dir, int* contaTrocas){
    int chave, i, j;
    chave = vet[esq]; i = esq; j = dir;

    while (i<j) {
        while(vet[j] > chave && i < j) j--;
        vet[i] = vet[j];
        (*contaTrocas)++;
        while(vet[i] <= chave && i < j) i++ ;
        vet[j] = vet[i];
        (*contaTrocas)++;
    }
    vet[j] = chave;
    return i;
}

int mediana_de_3(int vet[], int x, int y, int z){
    if ((vet[y] >= vet[x] && vet[y] <= vet[z]) || (vet[y] >= vet[z] && vet[y] <= vet[x])) {
        return y;
    }
    else if ((vet[x] >= vet[y] && vet[x] <= vet[z]) || (vet[x] >= vet[z] && vet[x] <= vet[y])) {
        return x;
    }
    else {
        return z;
    }

}

void quicksort(int vet[], int posInicial, int posFinal, int* contaTrocas, int* contaRecursao, int TIPO, int PARTICAO){

    if(posFinal > posInicial){
        int p, r, aux;

        switch(TIPO){
            case MEDIANA:

                int meio = (posInicial + posFinal)/2;
                r =  mediana_de_3(vet, meio, posInicial, posFinal);

                aux = vet[posInicial];
                vet[posInicial] = vet[r];
                vet[r] = aux;

            break;

            case RANDOM:
                r = (rand() % (posFinal - posInicial + 1)) + posInicial;

                aux = vet[posInicial];
                vet[posInicial] = vet[r];
                vet[r] = aux;
            break;
        }

        switch(PARTICAO){
            case HOARE:
                p = particao_hoare(vet, posInicial, posFinal, contaTrocas);
            break;
            case LOMUTO:
                p = particao_lomuto(vet, posInicial, posFinal, contaTrocas);
            break;

        }

        (*contaRecursao)++;
        quicksort(vet, posInicial, p-1, contaTrocas, contaRecursao, TIPO, PARTICAO);
        (*contaRecursao)++;
        quicksort(vet, p+1, posFinal, contaTrocas, contaRecursao, TIPO, PARTICAO);
    }
}

