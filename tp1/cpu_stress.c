/*
 * Realize um programa cpu_stress com o objetivo de simular uma
 * carga de processamento no(s) CPU(s) disponíveis no sistema
 * através da criação de múltiplos processos.
 * 
 * Este programa recebe pelos argumentos da linha de comando o
 * número de processos auxiliares (processos filho) a serem criados.
 * Cada um dos processos auxiliares executa a função
 * process_work. Na Figura 1 ilustra-se a utilização desta função
 * num programa sequencial.
 * 
 * O processo pai só deve terminar depois de garantir que todos os
 * processos filho terminaram a sua execução.
 * Utilize os programas htop, top e ps num terminal para acompanhar
 * a execução do seu programa.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Forks and stuff
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CHILD 0

void process_work(long niter)
{
    for (long i=0; i < niter; i++)
    {
        sqrt(rand());
    }
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Low arguments\n");
        return 0;
    }

    int iterate;
    int numberChildren=atoi(argv[1]);

    for(iterate=0; iterate < numberChildren; iterate++)
    {
        pid_t pids=fork();
        //TODO: if fork fails
        if(pids == CHILD)
        {
            process_work(1e9);
            return 0;
        }
    }

    for(iterate=0; iterate < numberChildren; iterate++)
    {
        wait(NULL);
    }

    return 0;
}
