// ./vector_stat_proc <vector dimension> <number processes>

// HEADERS ------------------------------------------------------------------ //
// System
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

<<<<<<< HEAD
// Custom
#include "utilities.h"
=======
// Minhas macros
#define FILHO           0
#define ESCRITA         STDOUT_FILENO
#define LEITURA         STDIN_FILENO
#define UNIDIRECIONAL   2
#define BIDIRECIONAL    4
>>>>>>> 921f24bcf04357f794b1ad900bd79bba9a65a7fe

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

<<<<<<< HEAD
    int *vectorValues = NULL;
    int *vectorSubValues = NULL;

    createVectors(vectorValues, vectorSize);
    createVectors(vectorSubValues, vectorSize);


=======
    // Argumentos
    long numeroElementos = atol(argv[1]);
    int numeroProcessos = atoi(argv[2]);

    // Variáveis auxiliares
    int iterador = 0;

    // Vetores
    int *vectorInteiros = NULL;
    int *subvetorInteiros = NULL;

    // Cria e aloca os vetores
    alocaVetores(vectorInteiros, subvetorInteiros);
    vector_init_rand(vectorInteiros, subvetorInteiros, LOWER_LIMIT, UPPER_LIMIT);

    vector_get_in_range(vectorInteiros, numeroElementos, subvetorInteiros, LOWER_LIMIT, UPPER_LIMIT, numeroProcessos);
>>>>>>> 921f24bcf04357f794b1ad900bd79bba9a65a7fe

    return 0;
}
