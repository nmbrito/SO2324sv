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

// Minhas macros
#define FILHO 0

// Macros apoioTP1
// Define o limite superior para a geração de valores aleatórios
#define LOWER_LIMIT       0
#define UPPER_LIMIT     100

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Utilização incorreta. Forma correta: ./vector_stat_proc <dimensão_vetor> <número_de_processos>");
        return -1;
    }

    int iterar;                         // TODO
    int numeroProcessos=atoi(argv[2]);  // Guarda o valor passado pelo segundo argumento
    int tubofd[2];                      // Canal de comunicação de leitura (0) e escrita (1)

    pipe(tubofd);                       // Cria o canal de comunicação

    // Este conteúdo será partilhado com os filhos, aqui não há egoísmo.
    // Variváreis do apoioTP1
        //long values_sz = 256*1024*1024L;
        long values_sz = atol(argv[1]);

        // allocate a vector of initial values
        int *values = malloc(sizeof(int) * values_sz);
        if (values == NULL) {
            fprintf(stderr, "Erro malloc\n");
            return -1;
        }
    
        // allocate a subvector where will be store values in a interval of values
        int *subvalues = malloc(sizeof(int) * values_sz);
        if (subvalues == NULL) {
            fprintf(stderr, "Erro malloc\n");
            return -1;
        }

        // initiate initial array of values 
        vector_init_rand(values, values_sz, LOWER_LIMIT, UPPER_LIMIT);

        struct timeval t1,t2;
        gettimeofday(&t1, NULL);

        // start of code to evaluate

        long count     = 0;
        int values_min = 50;
        int values_max = 100;

        count = vector_get_in_range(values, values_sz, subvalues, values_min, values_max);

        // end of code to evaluate

        gettimeofday(&t2, NULL);
        long elapsed = ((long)t2.tv_sec - t1.tv_sec) * 1000000L + (t2.tv_usec - t1.tv_usec);
        long sec = elapsed / (long)1e6;
        long aux = elapsed % (long)1e6;
        long mil = aux / (long)1e3;
        long mic = aux % (long)1e3;
         

        printf ("Elapsed time = %lds%ld,%ldms\n", sec, mil, mic);

        printf("Values between [%d..%d]: %ld\n", values_min, values_max, count);

    for(iterar=0; iterar < numeroProcessos; iterar++)
    {
        pid_t ramal=fork();
        if(ramal < FILHO)
        {
            // Falha na criação do ramal
            perror("Erro na criação do processo filho.");
            return -1;
        }
        else if(ramal == FILHO)
        {
            close(tubofd[0]);   // Fecha o canal de leitura (STDIN_FILENO = 0)
                                // Vai-se tirar partido do aspeto de clonagem para receber a leitura do vetor







            close(tubofd[1]);   // Fecha o canal de escrita (STDOUT_FILENO = 1)
        }
        else
        {
            close(tubofd[1]);   // Fecha o canal de escrita (STDOUT_FILENO = 1)






            close(tubofd[0]);   // Fecha o canal de leitura (STDIN_FILENO = 0)
        }
    }

    for(iterar=0; iterar < numeroProcessos; iterar++)
    {
        wait(NULL); // Garante que não há criação de processos orfãos
    }

    return 0;
}


