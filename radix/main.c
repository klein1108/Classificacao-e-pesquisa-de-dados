#include "radix/Radix.h"
#include "utils/utils.h"

int main()
{
    int nWords = 0;

    char** words = malloc(sizeof(char*) * MAX_WORDS);
    if (words == NULL) {
        printf("Error with the main memory allocation.\n");
        return 1;
    }

    readingFile("test1.txt", words, &nWords);
    radixSortMSD(words, nWords);
    writingFile("test1_sorted.txt", words, nWords);
    countingWords("test1_counted.txt", words, nWords);
    rankingGenerator("test1_counted.txt", "test1_ranked.txt");

    readingFile("test2.txt", words, &nWords);
    radixSortMSD(words, nWords);
    writingFile("test2_sorted.txt", words, nWords);
    countingWords("test2_counted.txt", words, nWords);
    rankingGenerator("test2_counted.txt", "test2_ranked.txt");

    readingFile("test3.txt", words, &nWords);
    radixSortMSD(words, nWords);
    writingFile("test3_sorted.txt", words, nWords);
    countingWords("test3_counted.txt", words, nWords);
    rankingGenerator("test3_counted.txt", "test3_ranked.txt");

    readingFile("test4.txt", words, &nWords);
    radixSortMSD(words, nWords);
    writingFile("test4_sorted.txt", words, nWords);
    countingWords("test4_counted.txt", words, nWords);
    rankingGenerator("test4_counted.txt", "test4_ranked.txt");

    readingFile("domcasmurro.txt", words, &nWords);
    radixSortMSD(words, nWords);
    writingFile("domcasmurro_sorted.txt", words, nWords);
    countingWords("domcasmurro_counted.txt", words, nWords);
    rankingGenerator("domcasmurro_counted.txt", "domcasmurro_ranked.txt");


    readingFile("war_and_peace.txt", words, &nWords);
    radixSortMSD(words, nWords);
    writingFile("war_and_peace_sorted.txt", words, nWords);
    countingWords("war_and_peace_counted.txt", words, nWords);
    rankingGenerator("war_and_peace_counted.txt", "war_and_peace_ranked.txt");


    for (int i = 0; i < nWords; i++) {
        free(words[i]);
    }

    free(words);

    return 0;
}
