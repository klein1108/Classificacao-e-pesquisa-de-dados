#include "utils.h"

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

void insertPlayerInHashTableById(PlayerHash *players[], PlayerHash *newPlayer){
    //necessario alterar essa logica para modulo
    int index = newPlayer->sofifaId;
    int alreadyInsertedError = FALSE;

    if(players[index] == NULL){
        players[index] = newPlayer;
    } else {
        PlayerHash *current = players[index];
        while (current->next != NULL) {
            //VERIFICAR JOGADOR JA INSERIDO QUANDO AJUSTAR LOGICA POR MODULO
//            if(current->sofifaId == newPlayer->sofifaId){
//                //alreadyInsertedError = TRUE
//            }
            current = current->next;
        }

        //IF(!alreadyInsertedError)
        current->next = newPlayer;
    }

     printf("Player %s has been successfully inserted\n", newPlayer->name);
}

void destroyHashtablesLists(int arrSize, PlayerHash *players[]){
    for (int i = 0; i < arrSize; i++) {
        PlayerHash *current = players[i];
        while (current != NULL) {
            PlayerHash *aux = current;
            current = current->next;
            free(aux);
        }
    }
}
