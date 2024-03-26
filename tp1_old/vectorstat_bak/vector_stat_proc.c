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
#define FILHO       0
#define ESCRITA     STDOUT_FILENO
#define LEITURA     STDIN_FILENO

// Macros apoioTP1
// Define o limite superior para a geração de valores aleatórios
#define LOWER_LIMIT 0
#define UPPER_LIMIT 100

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Utilização incorreta. Forma correta: ./vector_stat_proc <dimensão_vetor> <número_de_processos>");
        return -1;
    }

    int iterar;                                         // TODO
    int *vetorNumerosInteiros=(int *) malloc(argv[1]);
    int numeroProcessos=atoi(argv[2]);                  // Guarda o valor passado pelo segundo argumento
    int tuboFilho[2];                                   // Canal de comunicação de leitura (0) e escrita (1)
    int tuboPai[2];                                     // Canal de comunicação de leitura (0) e escrita (1)
    int *tubos=NULL;                                    // TODO para 2+ filhos

    pipe(tuboFilho);                                    // Cria o canal de comunicação
    pipe(tuboPai);                                      // Cria o canal de comunicação

    // Este conteúdo será partilhado com os filhos, aqui não há egoísmo.
    vector_get_in_range();

    for(iterar=0; iterar < numeroProcessos; iterar++)
    {
        int subvetorAtribuido=0;

        pid_t ramal=fork();
        if(ramal < FILHO)
        {
            // Falha na criação do ramal
            perror("Erro na criação do processo filho.");
            return -1;
        }
        else if(ramal == FILHO)
        {
            return processoFilho(); //TODO
        }
        else
        {
            //TODO: Delinear tarefas
            close(tubofd[1]);   // Fecha o canal de escrita (STDOUT_FILENO = 1)

            char *apontaMoradaVetor=NULL;



            close(tubofd[0]);   // Fecha o canal de leitura (STDIN_FILENO = 0)
        }
    }

    for(iterar=0; iterar < numeroProcessos; iterar++)
    {
        wait(NULL); // Garante que não há criação de processos orfãos
    }

    return 0;
}


