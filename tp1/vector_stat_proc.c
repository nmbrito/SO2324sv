// ./vector_stat_proc <vector dimension> <number processes>

// HEADERS ------------------------------------------------------------------ // {{{1
// System
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Custom
#include "utilities.h"

// -------------------------------------------------------------------------- // 1}}}

// MAIN --------------------------------------------------------------------- // {{{1
// argv[0] -> program name
// argv[1] -> vector dimension
// argv[2] -> number of processes
int main(int argc, char *argv[])
{

    if(argc != 3)
    {
        printf("Syntax wrong. Usage: $ ./vector_stat_proc <vector dimension> <number processes>");

        return -1;
    }
    
    long arraySize = atoi(argv[1]);
    int numberProcesses = atoi(argv[2]);

    // Arrays
    int *arrayValues = createIntArrays(&arrayValues, arraySize);
    int *arraySubValues = createIntArrays(&arraySubValues, arraySize);

    // Give random numbers to array
    vector_init_rand(arrayValues, arraySize, LOWER_LIMIT, MAXIMUM_LIMIT);

    // Call main function
    int count = vector_get_in_range(arrayValues, arraySize, arraySubValues, LOWER_LIMIT, UPPER_LIMIT, numberProcesses);
    if(count == CHILD_RETURN_SUCCESS) return 0; // So child doesn't slip to main

    printf("Count: %d\n", count);

    free(arrayValues);
    free(arraySubValues);

    return 0;
}
// -------------------------------------------------------------------------- // 1}}}
