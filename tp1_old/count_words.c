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
#include <string.h>
#include <math.h>

// Forks and stuff
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CHILD 0

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Low arguments\n");
        return -1;
    }

    char *countArguments[4];
    countArguments[0]=strdup("wc"); // program: wc
    countArguments[1]=strdup("-w"); // arguments: -w
    countArguments[2]=argv[1];      // terminal argument
    countArguments[3]=NULL;         // mark end of array

    execvp(countArguments[0], countArguments);

    return 0;
}
