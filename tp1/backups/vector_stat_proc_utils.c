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
    long sliceAddLeftover = 0;                                                          // Variable that accounts an element leftover
    long sliceIndexIni = 0;                                                             // [0, x[
    long sliceIndexEnd = 0;                                                             // [x, y[

    long svCount[1] = {0};                                                              // Stores counted values written in sv array by child process

    int pipeIndex = 0;
    int *pipesFDS = (int *) malloc(sizeof(int) * (PIPE_UNICHANNEL * n_processes));      // Create pipe array
    if(pipesFDS == NULL) return -1;

    sv = (int *) realloc(sv, sizeof(int) * (slices+1));                                                 // Resize subarray for children
    if(sv == NULL) return -1;

    for(int ongoingProcesses = 0; ongoingProcesses < n_processes; ongoingProcesses++)   // {{{3
    {
        if(sliceLeftover > 0)
        {
            sliceAddLeftover = 1;
            sliceLeftover--;
        }
        else
        {
            sliceAddLeftover = 0;
        }

        sliceIndexEnd = sliceIndexEnd + slices + sliceAddLeftover;

            //DEBUG ----------------------------------------------------
                printf("Sending initial index: %ld\n", sliceIndexIni);
                printf("Sending ending index: %ld\n", sliceIndexEnd);
            // ---------------------------------------------------------

        pipe(pipesFDS+pipeIndex);                                                       // Pipe creation for each child

        pid_t forker = fork();                                                          // Fork creation
        if(forker < CHILD)
        {
            perror("Error forking");
            exit(-1);
        }
        else if(forker == CHILD)
        {
            //TODO: Safe write
            close(pipesFDS[pipeIndex]);                                                 // Close write channel (0)

            for(; sliceIndexIni < sliceIndexEnd ; sliceIndexIni++)                      // Write valid values to array
            {
                if(v[sliceIndexIni] >= min && v[sliceIndexIni] <= max)
                {
                    sv[svCount[0]++] = v[sliceIndexIni];
                }
            }

            //DEBUG ----------------------------------------------------
                printf("Child %d numbers: ", getpid());
                for(long i = 0; i < svCount[0]; i++)
                {
                    printf("%d ", sv[i]);
                }
                printf("\n");
            // ---------------------------------------------------------

            write(pipesFDS[pipeIndex+1], svCount, sizeof(long));
            write(pipesFDS[pipeIndex+1], sv, sizeof(long) * svCount[0]);

            //DEBUG ----------------------------------------------------
                printf("Count child %d: %ld\n\n", getpid(), svCount[0]);
            // ---------------------------------------------------------

            close(pipesFDS[pipeIndex+1]);                                               // Close read channel (1)
            free(pipesFDS);

            exit(0);
        }

        sliceIndexIni = sliceIndexEnd;
        pipeIndex += PIPE_UNICHANNEL;                                                   // Next pipe set
    }                                                                                   // 3}}}

    long sumOfsvCount = 0;

    sv = (int *) realloc(sv, sizeof(int) * v_sz);
    if(sv == NULL) return -1;

            //DEBUG ----------------------------------------------------
                long i = 0;
            // ---------------------------------------------------------

    for(pipeIndex = 0; pipeIndex < (n_processes * PIPE_UNICHANNEL); pipeIndex += PIPE_UNICHANNEL)
    {
        //TODO: Safe read
        close(pipesFDS[pipeIndex+1]);                                                   // Close read channel (1)
                                                                                        //
        read(pipesFDS[pipeIndex], svCount, sizeof(long));

            //DEBUG ----------------------------------------------------
                printf("Parent count read: %ld\n", svCount[0]);
            // ---------------------------------------------------------

        read(pipesFDS[pipeIndex], &sv[sumOfsvCount], sizeof(int) * svCount[0]);

        sumOfsvCount = sumOfsvCount + svCount[0];

            //DEBUG ----------------------------------------------------
                printf("\n\nPipe %d read: ", pipeIndex);
                for(; i < sumOfsvCount; i++)
                {
                    printf("%d ", sv[i]);
                }
                i = sumOfsvCount;
                printf("\n");
            // ---------------------------------------------------------

        close(pipesFDS[pipeIndex]);                                                     // Close write channel (0)
    }

    for(int closeProcesses = 0; closeProcesses < n_processes; closeProcesses++)         // Waits for children
    {
        wait(NULL);
    }

            //DEBUG ----------------------------------------------------
                printf("\n\nFinal subarray values: ");
                for(long i = 0; i < sumOfsvCount; i++)
                {
                    printf("%d ", sv[i]);
                }
                printf("\n");
                printf("Returning a total sum of: %ld\n", sumOfsvCount);
            // ---------------------------------------------------------

    free(pipesFDS);

    return sumOfsvCount;
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
