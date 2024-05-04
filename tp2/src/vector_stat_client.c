// ./vector_stat_client <vector dimension> <number processes / threads>

// HEADERS ------------------------------------------------------------------ //
// System
#include <stdlib.h>

#include <vector_stat_proc_utils.h>
// -------------------------------------------------------------------------- //

// MAIN --------------------------------------------------------------------- //
// argv[0] -> program name
// argv[1] -> array dimension
// argv[2] -> number of processes
int main(int argc, char *argv[])
{
    // Check arguments
    if(argc != 3)
    {
        printf("Syntax wrong. Usage: $ ./vector_stat_proc <vector dimension> <number processes / threads>");
        return -1;
    }

    long arraySize      = atoi(argv[1]);
    int numberThreads   = atoi(argv[2]);

    // Arrays
    int *arrayValues = (int *) malloc(sizeof(int) * arraySize);
    if(arrayValues == NULL) return -1;

    int *arraySubValues = (int *) malloc(sizeof(int) * arraySize);
    if(arraySubValues == NULL) return -1;

    // Initiate array with random numbers
    vector_init_rand(arrayValues, arraySize, LOWER_LIMIT, MAXIMUM_LIMIT);

    // Send to server
        // Call main function
        int count = vector_get_in_range_with_threads(arrayValues, arraySize, arraySubValues, LOWER_LIMIT, UPPER_LIMIT, numberThreads);
    // --------------

    printf("Counted %d valid numbers", count);

    // Free arrays
    free(arrayValues);
    free(arraySubValues);

    return 0;
}
// -------------------------------------------------------------------------- //
