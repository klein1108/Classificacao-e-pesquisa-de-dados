#include "utils/utils.h"

int main(void){

    int arrLength = 0;
    char **words = readWords("domcasmurro.txt", &arrLength);

    int arrRepeatLength = 0;
    int wordsRepetitions[ARRAY_LENGTH] = {};

    int arrFilteredLength = 0;
    char **wordsFiltered = filterUniqueWordsAndCountRepetition(words, wordsRepetitions, &arrRepeatLength, arrLength, &arrFilteredLength);

    if (words == NULL) {
        printf("Erro ao ler palavras do arquivo.\n");
        return 1;
    }

//    printAllStringMalloc(words, arrLength, "nao filtrado");
//    printAllStringMalloc(wordsFiltered, arrFilteredLength ,"filtrado");

//    printArray(wordsRepetitions, arrRepeatLength);
    printf("Foram filtrados %d valores!\n", arrFilteredLength);
    printfFormatted(wordsFiltered, wordsRepetitions, arrFilteredLength);


    freeArrayStringMalloc(words, arrLength);
    freeArrayStringMalloc(wordsFiltered, arrFilteredLength);


    printf("FIM!");

    return 0;
}
