#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 600000
#define MAX_CHAR 4000000
#define HUNDRED 100

typedef struct {
    char word[100];
    int wordCount;
} WordNode;

int comparingRanking(const void* a, const void* b);
char* mergingName(char* merged, char* prefix, char* suffix);
void countingWords(const char* fileName, char** words, int nWords);
void readingFile(const char* fileName, char** words, int* nWords);
void writingFile(const char* fileName, char** words, int nWords);
void rankingGenerator(const char* fileDataName, const char* nomeSaida);

#endif // UTILS_H_INCLUDED
