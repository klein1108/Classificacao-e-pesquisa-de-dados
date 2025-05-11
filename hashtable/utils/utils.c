#include "utils.h"

void readAllQueriesIdFromCSV(const char *filename, int arr[]){
    FILE* file = fopen(filename, "r");
    int i = 0;
    if (!file) {
        printf("Error openning the file %s\n", filename);
        return;
    } else {
        char line[MAX_LENGTH];
        while(fgets(line, sizeof(line), file)){
            arr[i] = atoi(line);
            i++;
        }
    }
}

PlayerHash* readPlayersFromCSVAndInsertInHashTable(const char *filename, PlayerHash *players[], int arrSize){
    FILE* file = fopen(filename, "r");

    if (!file) {
        printf("Error openning the file %s\n", filename);
        return;
    } else {
        char line[MAX_LENGTH];
        int count = 0;
        //ignora primeira linha
        fgets(line, sizeof(line), file);


        while(fgets(line, sizeof(line), file)){
            line[strcspn(line, "\n")] = END_LINE;

            PlayerHash *newPlayer = (PlayerHash*) malloc(sizeof(PlayerHash));
            newPlayer->next = NULL;

            // GET ID FROM STRING ROW WITH ',' SEPARATORS
            char *aux = strtok(line, ",");
            if(!aux){
                printf("ERROR: While getting id\n");
                free(newPlayer);
                return;
            } else {
                newPlayer->sofifaId = atoi(aux);
            }

            // GET NAME FROM STRING ROW WITH ',' SEPARATORS
            aux = strtok(NULL, ",");
            if (!aux){
                printf("ERROR: While getting name\n");
                free(newPlayer);
                return;
            } else {
                char newName[MAX_LENGTH];
                strncpy(newName, aux, MAX_LENGTH);
                newName[MAX_LENGTH - 1] = END_LINE;
                strcpy(newPlayer->name, newName);
            }

            // GET POSITIONS FROM STRING ROW WITH ',' SEPARATORS
            aux = strtok(NULL, "\n");
             if (!aux){
                printf("ERROR: While getting positions\n");
                free(newPlayer);
                return;
            } else {
                char position[MAX_LENGTH];
                strncpy(position, aux, MAX_LENGTH);
                position[MAX_LENGTH - 1] = END_LINE;
                strcpy(newPlayer->playerPosition, position);
            }
            count++;
            insertPlayerInHashTableById(players, newPlayer, arrSize);

        }
        fclose(file);
        printf("HASH TABLE LENGTH %d -> Total players added: %d\n", arrSize, count);

    }

}

void writeFormattedSingularResultInFile(FILE *file, void *arr, int arrSize, char type) {
    for (int i = 0; i < arrSize; i++) {
        switch(type){
            case 'f':
                fprintf(file, "%.2f", ((float *)arr)[i]);
                break;
            case 'i':
                fprintf(file, "%d", ((int *)arr)[i]);
                break;
        }

        if (i < arrSize - 1){
            fprintf(file, ",");
        }
    }
    fprintf(file, "\n");
}

void writeSingularResultsinFile(const char *fileName,
                      float allTimes[],
                      float allOccupancyRate[],
                      int allGreatestList[],
                      float allAverageSize[]) {

    FILE *file = fopen(fileName, "w");
    if (!file) {
        perror("Error while opening the file");
        return;
    }

    writeFormattedSingularResultInFile(file, allTimes, CINCO, 'f');
    writeFormattedSingularResultInFile(file, allOccupancyRate, CINCO, 'f');
    writeFormattedSingularResultInFile(file, allGreatestList, CINCO, 'i');
    writeFormattedSingularResultInFile(file, allAverageSize, CINCO, 'f');

    fclose(file);
}

void writeFormattedPlayerInFile(const char *fileName, PlayerHash *player, int testsPerformed[]) {
    FILE *file = fopen(fileName, "a");
    if (!file) {
        perror("Error while opening the file");
        return;
    }

    int id;
    char name[MAX_LENGTH];
    char pos[MAX_LENGTH];

    if (player == NULL) {
        id = NOT_FOUND_ID;
        strcpy(name, NOT_FOUND_NAME);
        strcpy(pos, NOT_FOUND_NAME);
    } else {
        id = player->sofifaId;
        strcpy(name, player->name);
        strcpy(pos, player->playerPosition);
    }


    fprintf(file, "%d,%s,%s,", id, name , pos);

    int testsPerformedLength = sizeof(testsPerformed)/sizeof(int);
    for(int i = 0; i < testsPerformedLength; i++){
        if(i == testsPerformedLength - 1){
            fprintf(file, "%d\n", testsPerformed[i]);
        } else {
            fprintf(file, "%d,", testsPerformed[i]);
        }
    }
    fclose(file);
}

/// Trocar para a pasta Hash -> Hash.h  -> Hash.c
void destroyHashLine(PlayerHash *firstElement, int index){
    PlayerHash *current = firstElement;
    PlayerHash *aux = firstElement;

    while (current != NULL) {
        aux = current;
        current = current->next;
        free(aux);
    }
    printf("\n\tSuccessfully destroyed line %d!\n", index);
}

void printHashTable(int arrSize, PlayerHash *players[]){
    for (int i = 0; i < arrSize; i++) {
        printf("Bucket %d:\n", i);
        PlayerHash *current = players[i];
        if (current == NULL) {
            printf("  NULL\n");
        } else {
            while (current != NULL) {
                printf("  Name: %s (ID: %ld)\n", current->name, current->sofifaId);
                current = current->next;
            }
        }
    }
}


void insertPlayerInHashTableById(PlayerHash *players[], PlayerHash *newPlayer, int arrSize){
    int indexNewPlayer = newPlayer->sofifaId;
    int module = (int) indexNewPlayer % arrSize;

    if(players[module] == NULL){
        players[module] = newPlayer;
    } else {
        PlayerHash *current = players[module];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newPlayer;
    }
}

PlayerHash* searchPlayerInHashTableById(int arrSize, int playerId, PlayerHash *players[], int *testsPerformeds){
    int module = (int) playerId % arrSize;
    PlayerHash *current = players[module];

    while(current != NULL){
        (*testsPerformeds)++;

        if(current->sofifaId == playerId){
            return current;
        } else {
            current = current->next;
        }
    }

    return NULL;
}

int getTheGreatestHashTableListSize(int arrSize, PlayerHash *players[]){
    int greaterListSize = 0;
    int count = 0;

    for(int i = 0; i < arrSize; i++){
        PlayerHash *aux = players[i];
        while(aux != NULL){
            count++;
            aux = aux->next;
        }

        if(count > greaterListSize){
            greaterListSize = count;
        }

        count = 0;
    }

    return greaterListSize;
}

float getTheAverageHashTableListSize(int arrSize, PlayerHash *player[]){
    float averageSize = 0;
    int occupiedKeysCount = 0;
    int allListSizeCount = 0;

    for(int i = 0; i < arrSize; i++){
        PlayerHash *aux = player[i];
        if(aux != NULL){
            occupiedKeysCount++;
        }

        while(aux != NULL){
            allListSizeCount++;
            aux = aux->next;
        }
    }
    averageSize = (float) allListSizeCount / occupiedKeysCount;
    return averageSize;
}

float countHashTableOccupancyRate(int arrSize, PlayerHash *players[]){
    int usedKeys = 0;
    float occupancyRate;
    for(int i = 0; i < arrSize; i++){
        if(players[i] != NULL){
            usedKeys++;
        }
    }

    occupancyRate = (float)usedKeys/arrSize;
    return occupancyRate;
}

void destroyHashtablesLists(int arrSize, PlayerHash *players[]){
    int count = 0;
    for (int i = 0; i < arrSize; i++) {
        PlayerHash *current = players[i];

        while (current != NULL) {
            PlayerHash *aux = current;
            current = current->next;
            free(aux);
            count++;
        }
    }
    printf("HASH TABLE LENGTH: %d -> Total players removed: %d\n\n", arrSize, count);
}


