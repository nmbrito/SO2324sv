// ./vector_stat_proc <vector dimension> <number processes>

// Required
#include <stdlib.h>
#include <stdio.h>
// Forks
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
// Minhas funções
#include "vector_stat_proc_funcs.h"
#include "vector_stat_proc_filho.h"

// Minhas macros
#define FILHO           0
#define ESCRITA         STDOUT_FILENO
#define LEITURA         STDIN_FILENO
#define UNIDIRECIONAL   2
#define BIDIRECIONAL    4

// Macros apoioTP1
// Define o limite superior para a geração de valores aleatórios
#define LOWER_LIMIT     0
#define UPPER_LIMIT     100

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Utilização incorreta. Forma correta: ./vector_stat_proc <dimensão_vetor> <número_de_processos>");
        return -1;
    }

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

    return 0;
}
