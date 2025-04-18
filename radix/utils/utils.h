#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LENGTH 10
#define ARRAY_LENGTH 100000
#define BUFFER_SIZE 1024

#define TRUE 1
#define FALSE 0

typedef struct {
    char word[WORD_LENGTH];
    int nTimes;
} WordText;

void printAllStringMalloc(char **str, int length, char *stringText);
void freeArrayStringMalloc(char **str, int length);
void stringArrayMalloc(char **str);
char** readWords(char *fileName, int* arrLength);
WordText* filterUniqueWordsAndCountRepetition(char **words, int arrLength, int *newArrLength);
void printArray(int* arr[], int length);
void printfFormatted(WordText *strFiltered , int strFilteredLength);

#endif // UTILS_H_INCLUDED
