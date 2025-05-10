#include <stdio.h>
#include "utils/utils.h"

int main(){
    PlayerHash *players[2]={NULL};
    int arrSize = 2; // alterar para M-1

    // Exibindo a "tabela"
    printHashTable(arrSize, players);

    // teste criacao dos elementos -- aqui vai coleta de informacoes dos arquivos
    PlayerHash *teste1 = (PlayerHash*) malloc(sizeof(PlayerHash));
    PlayerHash *teste2 = (PlayerHash*) malloc(sizeof(PlayerHash));

    strcpy(teste1->name, "Lucas");
    teste1->next = NULL;
    teste1->sofifaId = 0;

    strcpy(teste2->name, "Klein");
    teste2->next = NULL;
    teste2->sofifaId = 0;

    //inserindo teste1
    insertPlayerInHashTableById(players, teste1);

    //inserindo teste2
    insertPlayerInHashTableById(players, teste2);

    // Exibindo a "tabela"
    printHashTable(arrSize, players);

    // Liberar memória
    destroyHashtablesLists(arrSize, players);

    return 0;
}
