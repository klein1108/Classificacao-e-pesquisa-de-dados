#include <time.h>
#include "utils/utils.h"

PlayerHash allPlayers[M] = {};

int main(){
    int arrM[CINCO] = {3793, 6637, 9473, 12323, 15149};

    float allHashTableCreationTimes[CINCO] = {};
    double allHashTableSearchTimes[CINCO] = {};
    float allOccupancyRate[CINCO] = {};
    int allGreatestList[CINCO] = {};
    float allAverageSize[CINCO] = {};


    int idsToSearch[M];
    int testsPerformed[CINCO][M] = {};

    clock_t start, end;
    double cpu_time_used;

    readAllQueriesIdFromCSV("data/consultas.csv", idsToSearch);

    //estatisticas_construção
    for(int i = 0; i < CINCO; i++){
        int arrSize = arrM[i];

        PlayerHash *players[arrSize] = {};

        start = clock();
        readPlayersFromCSVAndInsertInHashTable("data/players.csv", players, arrSize);
        end = clock();
        cpu_time_used = ((double)(end - start)) / (CLOCKS_PER_SEC/1000);



        allGreatestList[i] = getTheGreatestHashTableListSize(arrSize, players);
        allOccupancyRate[i] = countHashTableOccupancyRate(arrSize, players);
        allAverageSize[i] = getTheAverageHashTableListSize(arrSize, players);
        allHashTableCreationTimes[i] = (float)cpu_time_used;

        writeSingularResultsinFile("results/estatisticas_construção.txt", allHashTableCreationTimes, allOccupancyRate, allGreatestList, allAverageSize);







        //estatisticas_consultas
        PlayerHash *current;
        start = clock();
        for(int j = 0; j < M; j++){
            int aux = 0;
            current = searchPlayerInHashTableById(arrSize, idsToSearch[j], players, &aux);
            testsPerformed[i][j] = aux;

            if(current == NULL){
                allPlayers[j].sofifaId = NOT_FOUND_ID;
                strcpy(allPlayers[j].name, NOT_FOUND_NAME);
            } else {
                allPlayers[j].sofifaId = current->sofifaId;
                strcpy(allPlayers[j].name, current->name);
            }
        }
        end = clock();
        cpu_time_used = ((double)(end - start)) / (CLOCKS_PER_SEC/1000);
        allHashTableSearchTimes[i] =  cpu_time_used;
        printf("TEMPO: %.2lf ms\n", allHashTableSearchTimes[i]);



        destroyHashtablesLists(arrSize, players);


    }

    writeFormattedPlayerInFile("results/estatisticas_consultas.txt", allPlayers, M, testsPerformed, allHashTableSearchTimes, CINCO);





    return 0;
}


