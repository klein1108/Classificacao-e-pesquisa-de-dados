#include <stdio.h>
#include "utils/utils.h"

int main(){
    int arrM[5] = {3793, 6637, 9473, 12323, 15149};

    for(int i = 0; i < 5; i++){
        int index = arrM[i];
        PlayerHash *players[index]={};
        readPlayersFromCSVAndInsertInHashTable("data/players.csv", players, index);
        destroyHashtablesLists(index, players);
    }

    return 0;
}


