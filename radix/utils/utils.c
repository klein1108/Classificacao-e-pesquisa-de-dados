#include "utils.h"

void printArray(int* arr[], int length){
    int i;
    for (i=0; i < length; i++) {
        printf("%d ", arr[i]);
    }

    printf("\nForam Contados %d valores com sucesso!\n", i);
}

void printAllStringMalloc(char **str, int length, char *stringText){
  printf("Array de strings %s:\n", stringText);
  for (int i = 0; i < length; i++) {
    printf("%s\n", str[i]);
  }
}

void freeArrayStringMalloc(char **str, int length){
  for (int i = 0; i < length; i++) {
      free(str[i]);
  }
  free(str);
}

char** readWords(char *fileName, int* arrLength) {
  FILE* file = fopen(fileName, "r");
  if (!file) {
      perror("Erro ao abrir o arquivo");
      return NULL;
  }

    char buffer[BUFFER_SIZE];
    char** words = NULL;
    *arrLength = 0;

    while (fgets(buffer, BUFFER_SIZE, file)) {
        char* palavra = strtok(buffer, " \t\n");
        while (palavra != NULL) {

            words = realloc(words, (*arrLength + 1) * sizeof(char*));
            if (!words) {
                perror("Erro ao alocar mem�ria");
                fclose(file);
                return NULL;
            }

            words[*arrLength] = malloc(strlen(palavra) + 1);
            if (!words[*arrLength]) {
                perror("Erro ao alocar mem�ria para a palavra");
                fclose(file);
                return NULL;
            }
            strcpy(words[*arrLength], palavra);

            (*arrLength)++;
            palavra = strtok(NULL, " \t\n"); // Pr�xima palavra
        }
    }

    fclose(file);
    return words;
}

char** filterUniqueWordsAndCountRepetition(char **str, int repetitions[], int *repetitionsLength, int arrLength, int *newArrLength) {
    int aux = 0;
    int capacidade = ARRAY_LENGTH;
    char** words = malloc(capacidade * sizeof(char*));

    for (int i = 0; i < arrLength; i++) {
        int repetida = FALSE;

        for (int j = 0; j < aux; j++) {

            if (strcmp(str[i], words[j]) == 0) {
                repetida = TRUE;
                if(repetitions[j] == 0){
                    (*repetitionsLength)++;
                    repetitions[j] = 1;         //ajuste q os valores comecam em 0 e ele deve ter aparecido pelo menos uma vez para repetir
                }
                repetitions[j]++;

                break;
            }
        }

        if (!repetida) {
            if (aux >= capacidade) {
                capacidade *= 2;
                words = realloc(words, capacidade * sizeof(char*));
            }

            words[aux] = malloc(strlen(str[i]) + 1);
            strcpy(words[aux], str[i]);

            aux++;
        }
    }

    *newArrLength = aux;
    return words;
}

void printfFormatted(char **strFiltered,int repetitions[], int strFilteredLength){
    for(int i = 0; i < strFilteredLength; i++){
        printf("- %s repetiu %d vezes\n", strFiltered[i], repetitions[i]);
    }
}
