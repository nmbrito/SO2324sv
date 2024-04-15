// HEADERS ----------------------------------------------------------------------------- // {{{1
// System
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "vector_stat_proc_utils.h"
// ------------------------------------------------------------------------------------- // 1}}}

// ASSIGNMENT WORK---------------------------------------------------------------------- // {{{1
// int vector_get_in_range(int v[], int v_sz, int sv[], int min, int max, int n_processes); {{{2
int vector_get_in_range(int v[], int v_sz, int sv[], int min, int max, int n_processes)
{
    long slices = v_sz / n_processes;                                                   // Number of sections splits in the array depending on number of processes
    long sliceLeftover = v_sz % n_processes;                                            // Store residue for further split calculations

    long svCount[1] = {0};                                                              // Stores counted values written in sv array by child process

    int *pipesFDS = (int *) malloc(sizeof(int) * (PIPE_UNICHANNEL * n_processes));
    if(pipesFDS == NULL) return -1;

    int *pipesFDS_addr = pipesFDS;                                                        // Save pipesFDS original address

    for(int ongoingProcesses = 0; ongoingProcesses < n_processes; ongoingProcesses++)   // {{{3
    {

        pipe(pipesFDS);                                                                 // Pipe creation for each child

        pid_t forker = fork();                                                          // Fork creation
        if(forker < CHILD)
        {
            perror("Error forking");
            exit(-1);
        }
        else if(forker == CHILD)
        {
            close(pipesFDS[READ]);                                                      // Child will write only

            //for (long i = 0; i < (slices + addLeftover); i++)                           // Write valid values to array
            //{
            //    if (v[i] >= min && v[i] <= max)
            //    {
            //        sv[svCount[0]++] = v[i];
            //    }
            //}

            // TODO

            close(pipesFDS[WRITE]);
            free(pipesFDS);

            exit(0);
        }

        pipesFDS += PIPE_UNICHANNEL;                                                    // Next pipe set
    }                                                                                   // 3}}}

    pipesFDS = pipesFDS_addr;
    long countNumbers = 0;

    for(int closeProcesses = 0; closeProcesses < n_processes; closeProcesses++)         // Waits for children
    {
        wait(NULL);
    }

    free(pipesFDS);

    return countNumbers;
}
// ------------------------------------------------------------------------------------- // 2}}}
// ------------------------------------------------------------------------------------- // 1}}}

// CUSTOM FUNCTIONS -------------------------------------------------------------------- // {{{1
// ------------------------------------------------------------------------------------- // 1}}}

// APOIOTP1 FUNCTIONS------------------------------------------------------------------- // {{{1
// Random number generator
int get_random(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

// Initiate vector with random numbers
void vector_init_rand(int v[], long dim, int min, int max)
{
    for (long i = 0; i < dim; i++)
    {
        v[i] = get_random(min, max);
    }
}

// Sequential version
int vector_get_in_range_seq(int v[], int v_sz, int sv[], int min, int max)
{
    long count = 0;

    for (long i = 0; i < v_sz; i++)
    {
        if (v[i] >= min && v[i] <= max)
        {
            sv[count++] = v[i];
        }
    }
    return count;
}

// TODO
/*
void codeEval()
{
    struct timeval t1,t2;
    gettimeofday(&t1, NULL);

    // start of code to evaluate
    long count     = 0;
    int values_min = 50;
    int values_max = 100;

    //count = vector_get_in_range(values, values_sz, subvalues, values_min, values_max);
    // end of code to evaluate

    gettimeofday(&t2, NULL);
    long elapsed = ((long)t2.tv_sec - t1.tv_sec) * 1000000L + (t2.tv_usec - t1.tv_usec);
    long sec = elapsed / (long)1e6;
    long aux = elapsed % (long)1e6;
    long mil = aux / (long)1e3;
    long mic = aux % (long)1e3;

    printf ("Elapsed time = %lds%ld,%ldms\n", sec, mil, mic);

    printf("Values between [%d..%d]: %ld\n", values_min, values_max, count);
}
*/
// ------------------------------------------------------------------------------------- // 1}}}
