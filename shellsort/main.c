///InsertionSort exemplo em C
/// Aluno: Lucas Klein (586981)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int pot_2[] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576};
int tresN_mais_um[] = {1,4,13,40,121,364,1093,3280,9841,29524,88573,265720,797161,2391484};
int ciura[] = {1,4,10,23,57,132,301,701,1577,3548,7983,17961,40412,90927,204585,460316,1035711};

void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1], that are greater than key,
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Function to print an array
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void shell_sort(int arr[], int n, int arrTipo[]){
    clock_t start, end;
    double cpu_time_used;
    int h = 1;
    int conta = 0;
    int index, aux;

    for(index = 0, aux = 0; arrTipo[aux] <= n-1; aux++){
            if(arrTipo[aux] <= n-1){
               h = arrTipo[aux];
                index = aux;
            }

    }

    start = clock(); // Start time
    for(index; index >=0; index--){
        h = arrTipo[index];
        printf("H = %d\n", h);
        for (int i = h; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= h && arr[j - h] > temp; j -= h) {
                conta++;
                arr[j] = arr[j - h];
            }
            arr[j] = temp;
        }

//        print_array(arr, n);

    }

    end = clock(); // End time
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // Convert to seconds
    printf("Execution time: %f seconds\n", cpu_time_used);
    printf("Moves = %d\n", conta);
}




void randomize_array(int arrPot2[], int arrTresMaisUM[], int arrCiura[], int arrSize){
 // Gera os números aleatórios
    for (int i = 0; i < arrSize; i++) {
        int num = rand() % 100; // Números entre 0 e 99
        arrPot2[i] = num;
        arrTresMaisUM[i] = num;
        arrCiura[i] = num;

    }

}


// Main function to test the insertion sort
int main() {
    int n = 100000;

    int arrPot2[n];
    int arrTresMaisUM[n];
    int arrCiura[n];




    randomize_array(arrPot2, arrTresMaisUM, arrCiura, n);


    printf("Shellsort POT 2:\n");

    shell_sort(arrPot2, n, pot_2);



    printf("\nShellsort 3N + 1:\n");


    shell_sort(arrTresMaisUM, n, tresN_mais_um);



    printf("\nShellsort CIURA:\n");

    shell_sort(arrCiura, n, ciura);


    return 0;
}