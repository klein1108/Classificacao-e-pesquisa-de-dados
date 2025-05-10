#include "utils.h"

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
                return;
            } else {
                newPlayer->sofifaId = atoi(aux);
            }

            // GET NAME FROM STRING ROW WITH ',' SEPARATORS
            aux = strtok(NULL, ",");
            if (!aux){
                printf("ERROR: While getting name\n");
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
        printf("HASH TABLE %d LENGTH -> Total players added: %d\n", arrSize, count);

    }

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
    printf("HASH TABLE %d LENGTH -> Total players removed: %d\n", arrSize, count);
}


