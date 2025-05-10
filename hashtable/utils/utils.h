#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define M1 3793
#define MAX_LENGTH 256
#define END_LINE '\0'

typedef struct typePlayerHash{
    int sofifaId;
    char name[MAX_LENGTH];
    char playerPosition[MAX_LENGTH];
    struct typePlayerHash *next;
} PlayerHash;


PlayerHash* readPlayersFromCSVAndInsertInHashTable(const char *filename, PlayerHash *players[], int arrSize);

void destroyHashLine(PlayerHash *firstElement, int index);
void printHashTable(int arrSize, PlayerHash *players[]);
void insertPlayerInHashTableById(PlayerHash *players[], PlayerHash *newPlayer, int arrSize);
void destroyHashtablesLists(int arrSize, PlayerHash *players[]);



#endif // UTILS_H_INCLUDED
