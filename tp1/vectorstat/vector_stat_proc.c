// ./vector_stat_proc <vector dimension> <number processes>

// HEADERS ------------------------------------------------------------------ //
// System
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Custom
#include "utilities.h"

// MAIN --------------------------------------------------------------------- //
// argv[0] -> program name
// argv[1] -> vector dimension
// argv[2] -> number of processes
int main(int argc, char *argv[])
{

    if(argc != 3)
    {
        printf("Utilização incorreta. Forma correta: ./vector_stat_proc <dimensão_vetor> <número_de_processos>");
        printf("Syntax wrong. Usage: $ ./vector_stat_proc <vector dimension> <number processes>");

        return -1;
    }
    
    long arraySize = atoi(argv[1]);
    int numberProcesses = atoi(argv[2]);

    // Arrays
    int *arrayValues = createArrays(&arrayValues, arraySize);
    int *arraySubValues = createArrays(&arraySubValues, arraySize);

    arrayValues[0] = 20;
    arrayValues[1] = 40;
    arrayValues[2] = 60;
    arrayValues[3] = 80;
    arrayValues[4] = 100;
    arrayValues[5] = 120;
    arrayValues[6] = 140;
    arrayValues[7] = 160;
    arrayValues[8] = 180;
    arrayValues[9] = 200;

    // Call main function
    int count = vector_get_in_range(arrayValues, arraySize, arraySubValues, LOWER_LIMIT, UPPER_LIMIT, numberProcesses);

    return 0;
}
