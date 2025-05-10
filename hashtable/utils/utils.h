#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define M 18944
#define MAX_LENGTH 100

typedef struct typePlayerHash{
    int sofifaId;
    char name[MAX_LENGTH];
    char playerPosition[MAX_LENGTH];
    struct typePlayerHash *next;
} PlayerHash;


void destroyHashLine(PlayerHash *firstElement, int index);
void printHashTable(int arrSize, PlayerHash *players[]);
void insertPlayerInHashTableById(PlayerHash *players[], PlayerHash *newPlayer);
void destroyHashtablesLists(int arrSize, PlayerHash *players[]);


#endif // UTILS_H_INCLUDED
