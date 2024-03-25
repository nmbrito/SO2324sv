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

// MACROS ------------------------------------------------------------------- //
// Provided (apoioTP1)
#define LOWER_LIMIT             0
#define UPPER_LIMIT             100

// Custom macros
#define CHILD                   0
#define WRITE                   STDOUT_FILENO
#define READ                    STDIN_FILENO
#define PIPE_UNICHANNEL         2
#define PIPE_BICHANNEL          4
#define ARGUMENT_COUNT_ERROR    -1

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
    
    long vectorSize = atoi(argv[1]);
    int numberProcesses = atoi(argv[2]);

    int *vectorValues = NULL;
    int *vectorSubValues = NULL;

    createVectors(vectorValues, vectorSize);
    createVectors(vectorSubValues, vectorSize);

    return 0;
}
