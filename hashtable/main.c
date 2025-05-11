#include <time.h>
#include "utils/utils.h"

int main(){
    int arrM[CINCO] = {200389, 6637, 9473, 12323, 15149};
    int idsToSearch[M];

    float allHashTableCreationTimes[CINCO] = {};
    float allHashTableSearchTimes[CINCO] = {};
    float allOccupancyRate[CINCO] = {};
    int allGreatestList[CINCO] = {};
    float allAverageSize[CINCO] = {};

    int testsPerformed[CINCO] = {};

    clock_t start, end;
    double cpu_time_used;
    for(int i = 0; i < CINCO; i++){
        int arrSize = arrM[i];

        PlayerHash *players[arrSize]={};

        start = clock();
        readPlayersFromCSVAndInsertInHashTable("data/players.csv", players, arrSize);
        end = clock();
        cpu_time_used = ((double)(end - start)) / (CLOCKS_PER_SEC/1000);



        allGreatestList[i] = getTheGreatestHashTableListSize(arrSize, players);
        allOccupancyRate[i] = countHashTableOccupancyRate(arrSize, players);
        allAverageSize[i] = getTheAverageHashTableListSize(arrSize, players);
        allHashTableCreationTimes[i] = (float)cpu_time_used;

        writeSingularResultsinFile("results/estatisticas_construção.txt", allHashTableCreationTimes, allOccupancyRate, allGreatestList, allAverageSize);

        destroyHashtablesLists(arrSize, players);
    }

    readAllQueriesIdFromCSV("data/consultas.csv", idsToSearch);
//    printf("%d", idsToSearch[M]);

//    for(int j = 0; j < M; j++){
//        start = clock();
//
//        for(int i = 0; i < CINCO; i++){
//            int arrSize = arrM[i];
//            int searchId = idsToSearch[j];
//
//            PlayerHash *searchedPlayer = searchPlayerInHashTableById(arrSize, searchId, players, &testsPerformed[i]);
//
//
//            allHashTableSearchTimes[i]
//        }
//
//        end = clock();
//        cpu_time_used = ((double)(end - start)) / (CLOCKS_PER_SEC/1000);
//    }

//    writeFormattedPlayerInFile("results/estatisticas_consultas.txt", player, testsPerformed);


    return 0;
}


