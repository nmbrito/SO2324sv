// ./vector_stat_proc <vector dimension> <number processes>

// HEADERS ------------------------------------------------------------------ // {{{1
// System
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "vector_stat_proc_utils.h"
// -------------------------------------------------------------------------- // 1}}}

// MAIN --------------------------------------------------------------------- // {{{1
// argv[0] -> program name
// argv[1] -> array dimension
// argv[2] -> number of processes
int main(int argc, char *argv[])
{
    // Check arguments
    if(argc != 3)
    {
        printf("Syntax wrong. Usage: $ ./vector_stat_proc <vector dimension> <number processes>");
        return -1;
    }

    long arraySize      = atoi(argv[1]);
    int numberProcesses = atoi(argv[2]);

    // Arrays
    int *arrayValues = (int *) malloc(sizeof(int) * arraySize);
    if(arrayValues == NULL) return -1;

    int *arraySubValues = (int *) malloc(sizeof(int) * arraySize);
    if(arraySubValues == NULL) return -1;

    // Initiate array with random numbers
    vector_init_rand(arrayValues, arraySize, LOWER_LIMIT, MAXIMUM_LIMIT);

    // Call main function
    int count = vector_get_in_range(arrayValues, arraySize, arraySubValues, LOWER_LIMIT, UPPER_LIMIT, numberProcesses);

    // Free arrays
    free(arrayValues);
    free(arraySubValues);

    return 0;
}
// -------------------------------------------------------------------------- // 1}}}
