#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define M 18948
#define CINCO 5
#define MAX_LENGTH 256
#define END_LINE '\0'

#define NOT_FOUND_ID 99999
#define NOT_FOUND_NAME "NAO_ENCONTRADO"


typedef struct typePlayerHash{
    int sofifaId;
    char name[MAX_LENGTH];
    char playerPosition[MAX_LENGTH];
    struct typePlayerHash *next;
} PlayerHash;


PlayerHash* readPlayersFromCSVAndInsertInHashTable(const char *filename, PlayerHash *players[], int arrSize);
void writeFormattedSingularResultInFile(FILE *file, void *arr, int arrSize, char type);
void writeSingularResultsinFile(const char *fileName,
                      float allTimes[],
                      float allOccupancyRate[],
                      int allGreatestList[],
                      float allAverageSize[]);
void writeFormattedPlayerInFile(const char *fileName, PlayerHash *player, int testsPerformed[]);
void readAllQueriesIdFromCSV(const char *filename, int arr[]);

void destroyHashLine(PlayerHash *firstElement, int index);
void printHashTable(int arrSize, PlayerHash *players[]);
void insertPlayerInHashTableById(PlayerHash *players[], PlayerHash *newPlayer, int arrSize);
void destroyHashtablesLists(int arrSize, PlayerHash *players[]);
PlayerHash* searchPlayerInHashTableById(int arrSize, int playerId, PlayerHash *players[], int *testsPerformeds);
float countHashTableOccupancyRate(int arrSize, PlayerHash *players[]);
int getTheGreatestHashTableListSize(int arrSize, PlayerHash *players[]);
float getTheAverageHashTableListSize(int arrSize, PlayerHash *player[]);


#endif // UTILS_H_INCLUDED
