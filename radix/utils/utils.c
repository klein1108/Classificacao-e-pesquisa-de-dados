#include "utils.h"

int comparingRanking(const void* a, const void* b){
    WordNode* p1 = (WordNode*)a;
    WordNode* p2 = (WordNode*)b;

    if (p1->wordCount != p2->wordCount) {
        return p2->wordCount - p1->wordCount;
    }
    return strcmp(p1->word, p2->word);
}

char* mergingName(char* merged, char* prefix, char* suffix){
    return sprintf(merged, "%s%s", prefix, suffix);
}

void readingFile(const char* fileName, char** words, int* nWords){
    char newFileName[100];
    mergingName(newFileName, "data/", fileName);

    FILE* file = fopen(newFileName, "r");

    char* node = malloc(sizeof(char) * MAX_CHAR);

    if (file == NULL) {
        printf("Error openning the file %s\n", newFileName);
        return;
    }

    *nWords = 0;

    if (fgets(node, MAX_CHAR, file) != NULL) {
        node[strcspn(node, "\n")] = '\0';

        char* token = strtok(node, " ");
        while (token != NULL && *nWords < MAX_WORDS) {
            words[*nWords] = malloc(strlen(token) + 1);
            if (words[*nWords] == NULL) {
                printf("Error trying to save the word %d\n", *nWords);
                break;
            }
            strcpy(words[*nWords], token);
            (*nWords)++;
            token = strtok(NULL, " ");
        }
    }

    fclose(file);

    printf("\nTotal words read: %d\n", *nWords);
}

void writingFile(const char* fileName, char** words, int nWords){
    char dir[] = "results/";
    char newFileName[50];
    sprintf(newFileName, "%s%s", dir, fileName);

    FILE* file = fopen(newFileName, "w");
    if (file == NULL) {
        printf("Error opening the file %s\n", fileName);
        return;
    }

    int i = 0;

    while(nWords > 0){

        fprintf(file, words[i]);
        fprintf(file, "\n");
        i++;
        nWords--;
    }

    fclose(file);

    return;
}

void countingWords(const char* fileName, char** words, int nWords){
    char newFileName[100];
    mergingName(newFileName, "results/", fileName);

    FILE* file = fopen(newFileName, "w");

    int count = 1;

    if (file == NULL) {
        printf("Error openning the file %s\n", newFileName);
        return;
    }


    for (int i = 1; i <= nWords; i++) {
        if (i < nWords && strcmp(words[i], words[i - 1]) == 0) {
            count++;
        } else {
            fprintf(file, "%s %d\n", words[i - 1], count);
            count = 1;
        }
    }

    fclose(file);
}

void rankingGenerator(const char* fileDataName, const char* fileResultName){
    char newFileDataName[100];
    char newFileResultName[100];

    mergingName(newFileResultName, "results/", fileResultName);
    mergingName(newFileDataName, "results/", fileDataName);

    FILE* fileData = fopen(newFileDataName, "r");

    if (fileData == NULL) {
        printf("Error opening the data file AQUI 1: %s\n", newFileDataName);
        return;
    }

    WordNode* nodes = malloc(sizeof(WordNode) * MAX_WORDS);

    if (!nodes) {
        printf("Error with the nodes malloc\n");
        fclose(fileData);
        return;
    }

    int total = 0;

    while (!feof(fileData) && total < MAX_WORDS) {
        if (fscanf(fileData, "%s %d\n", nodes[total].word, &nodes[total].wordCount) == 2) {
            total++;
        }
    }

    fclose(fileData);
    qsort(nodes, total, sizeof(WordNode), comparingRanking);

    FILE* fileResult = fopen(newFileResultName, "w");

    if (fileResult == NULL) {
        printf("Error opening the result file AQUI2: %s\n", newFileResultName);
        free(nodes);
        return;
    }

    int limit = (total < HUNDRED) ? total : HUNDRED;

    for (int i = 0; i < limit; i++) {
        fprintf(fileResult, "%s %d\n", nodes[i].word, nodes[i].wordCount);
    }

    fclose(fileResult);
    free(nodes);
}


