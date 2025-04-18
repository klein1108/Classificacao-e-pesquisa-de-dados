#include "utils/utils.h"

int main(void){

    int arrLength = 0;
    char **words = readWords("domcasmurro.txt", &arrLength);

    int arrRepeatLength = 0;
    int wordsRepetitions[ARRAY_LENGTH] = {};

    int arrFilteredLength = 0;

    WordText *wordFiltered = filterUniqueWordsAndCountRepetition(words, arrLength, &arrFilteredLength);

    if (words == NULL) {
        printf("Erro ao ler palavras do arquivo.\n");
        return 1;
    }

    printf("Foram filtrados %d valores!\n", arrFilteredLength);





    printfFormatted(wordFiltered, arrFilteredLength);

    freeArrayStringMalloc(words, arrLength);
    free(wordFiltered);

    printf("FIM!\n");

    return 0;
}
