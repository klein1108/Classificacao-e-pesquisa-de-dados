#include<stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10
#define MAX_RANDOM_VAL 50

#define HOARE 0
#define LOMOTO 1


void quicksort_random(int vet[], int posInicial, int posFinal, int* contaTrocas, int TIPO_PARTICAO){
    int r, p, aux;
    if(posFinal > posInicial){
        r = posInicial + rand() % (posFinal - posInicial + 1);

        aux = vet[posInicial];
        vet[posInicial] = vet[r];
        vet[r] = aux;
        *contaTrocas = *contaTrocas + 1;
        printf("TROCOU -> troca = %d\t", *contaTrocas);
        print_array(vet, ARRAY_SIZE);


        p = particiona_lomuto(vet, posInicial, posFinal, contaTrocas);
        quicksort(vet, posInicial, p-1, contaTrocas, TIPO_PARTICAO);
        quicksort(vet, p+1, posFinal, contaTrocas, TIPO_PARTICAO);

    }
}

void quicksort(int vet[], int posInicial, int posFinal, int* contaTrocas, int TIPO_PARTICAO){
    int pivo;
    if(posFinal > posInicial){
        if(TIPO_PARTICAO == HOARE){
            pivo = particiona_hoare(vet, posInicial, posFinal, contaTrocas);
        } else {
            pivo = particiona_lomuto(vet, posInicial, posFinal, contaTrocas);
        }
        quicksort(vet, posInicial, pivo-1, contaTrocas, TIPO_PARTICAO);
        quicksort(vet, pivo+1, posFinal, contaTrocas, TIPO_PARTICAO);

    }
}

int particiona_lomuto(int vet[], int esq, int dir, int* contaTrocas){
    int chave = vet[esq];
    int storeIndex = esq + 1;
    int aux;

    for(int i = esq + 1; i <= dir; i++){
        if(vet[i] < chave){
            //swap 1
            aux = vet[i];
            vet[i] = vet[storeIndex];
            vet[storeIndex] = aux;
            storeIndex++;

            *contaTrocas = *contaTrocas + 1;
            printf("TROCOU 1-> troca = %d\t", *contaTrocas);
            print_array(vet, ARRAY_SIZE);

        }
    }
    //swap 2
    aux = vet[esq];
    vet[esq] = vet[storeIndex-1];
    vet[storeIndex-1] = aux;

    *contaTrocas = *contaTrocas + 1;
    printf("TROCOU 2-> troca = %d\t", *contaTrocas);
    print_array(vet, ARRAY_SIZE);
    return (storeIndex-1);

}
int particiona_hoare(int vet[], int esq, int dir, int* contaTrocas){
    int chave, i, j, aux;
    chave = vet[esq];
    i = esq;
    j = dir+1;

    while(1){
        while(vet[++i] <= chave) if (i == dir) break;
        while(chave < vet[--j]) if (j == esq) break;
        if(i >= j) break;
        aux = vet[i];
        vet[i] = vet[j];
        vet[j] = aux;

        *contaTrocas = *contaTrocas + 1;
        printf("TROCOU 3 -> troca = %d\t", *contaTrocas);
        print_array(vet, ARRAY_SIZE);
    }
        aux = vet[esq];
        vet[esq] = vet[j];
        vet[j] = aux;
        *contaTrocas = *contaTrocas + 1;
        printf("TROCOU 4 -> troca = %d\t", *contaTrocas);
        print_array(vet, ARRAY_SIZE);
    return j;
}


// Function to print an array
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}



void randomize_array(int vetLomotoDefault[], int vetLomotoRandom[], int vetLomotoAvarage[],
                     int vetHoareDefault[], int vetHoareRandom[], int vetHoareAvarage[]){
    for (int i = 0; i < ARRAY_SIZE; i++) {
        int num = rand() % MAX_RANDOM_VAL + 1; // Numero aleatorio entre 0 até MAX_RANDOM_VAL
        vetLomotoDefault[i] = num;
        vetLomotoRandom[i] = num;
        vetLomotoAvarage[i] = num;

        vetHoareDefault[i] = num;
        vetHoareRandom[i] = num;
        vetHoareAvarage[i] = num;
    }

}

int main(){
    srand(time(NULL));
    //Lomoto
    int vetLomotoDefault[ARRAY_SIZE];
    int vetLomotoRandom[ARRAY_SIZE];
    int vetLomotoAvarage[ARRAY_SIZE];

    //Hoare
    int vetHoareDefault[ARRAY_SIZE];
    int vetHoareRandom[ARRAY_SIZE];
    int vetHoareAvarage[ARRAY_SIZE];

    randomize_array(vetLomotoDefault, vetLomotoRandom, vetLomotoAvarage,
                     vetHoareDefault, vetHoareRandom, vetHoareAvarage);

    int contaTrocas = 0;

    printf("LOMOTO PADRAO:\n");

    print_array(vetLomotoDefault, ARRAY_SIZE);
    quicksort(vetLomotoDefault, 0, ARRAY_SIZE-1, &contaTrocas, LOMOTO);
    print_array(vetLomotoDefault, ARRAY_SIZE);


    printf("\nLOMOTO RANDOMICO:\n");

    contaTrocas = 0;
    print_array(vetLomotoRandom, ARRAY_SIZE);
    quicksort_random(vetLomotoRandom, 0, ARRAY_SIZE-1, &contaTrocas, LOMOTO);
    print_array(vetLomotoRandom, ARRAY_SIZE);

    printf("\nHOARE DEFAULT:\n");

    contaTrocas = 0;
    print_array(vetHoareDefault, ARRAY_SIZE);
    quicksort_random(vetHoareDefault, 0, ARRAY_SIZE-1, &contaTrocas, HOARE);
    print_array(vetHoareDefault, ARRAY_SIZE);

    return 0;
}
