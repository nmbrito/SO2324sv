// System
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "vector_stat_proc_utils.h"
// ------------------------------------------------------------------------------------- //

// ASSIGNMENT WORK---------------------------------------------------------------------- //
// void vector_get_in_range_threadwork();
void *vector_get_in_range_threadwork(void *receivedThreadStructure)
{
    ThreadArguments *collectedThread = receivedThreadStructure;
    ThreadResult *result = (threadResult *) malloc(sizeof(threadResult));

    auxIni = collectedThread->sliceIndexIni;
    auxEnd = collectedThread->sliceIndexEnd;

    auxMin = collectedThread->min;
    auxMax = collectedThread->max;

    result->svCounter = 0;
    result->svThread = (int *) malloc(sizeof(svThread));

    for(; auxIni < auxEnd ; auxIni++) // Write valid values to array
    {
        if(v[auxIni] >= auxMin && v[auxIni] <= auxMax)
        {
            result->svThread[result->svCounter] = v[auxIni];
        }
    }
    
    free(collectedThread);
    return result;
}

// int vector_get_in_range(int v[], int v_sz, int sv[], int min, int max, int n_threads);
int vector_get_in_range(int v[], int v_sz, int sv[], int min, int max, int n_threads)
{
    long slices = v_sz / n_processes;                                                                       // Number of sections splits in the array depending on number of processes
    long sliceLeftover = v_sz % n_processes;                                                                // Store residue for further split calculations
    int sliceAddLeftover = 0;

    //long *svCount = (long *) malloc(sizeof(long) * n_threads);

    pthread_t *threadID = (pthread_t *) malloc(sizeof(pthread_t) * threadNumber);
    if(threadID == NULL) return -1;

    for(int ongoingThreads = 0; ongoingThreads < n_threads; ongoingThreads++)
    {
        ThreadArguments *currentThread = (ThreadArguments *) malloc(sizeof(ThreadArguments));
        if(currentThread == NULL) return -1;

        if(sliceLeftover > 0)                                                                               // If there is a remainder, it must be added to slice
        {
            sliceAddLeftover = 1;
            sliceLeftover--;
        }
        else
        {
            sliceAddLeftover = 0;
        }

        // Supply structure with values
        currentThread->sliceIndexIni = ongoingThreads * slices + sliceAddLeftover;
        currentThread->sliceIndexEnd = currentThread->sliceIndexIni + slices + sliceAddLeftover;            // Array ending index, if there is a remainder, add it

        currentThread->min = min;
        currentThread->max = max;

        pthread_create(&threadID[ongoingThreads], NULL, vector_get_in_range_threadwork, &currentThread);    // Create thread
    }

    long sumOfsvCounters = 0;
    long positionSV = 0;

    for(int closeThreads = 0; closeThreads < n_threads; closeThreads++)         // Wait for threads
    {
        ThreadResult *resultCollector;
        pthread_join(threadID[closeThreads], NULL, &resultCollector);

        sumOfsvCounters = sumOfsvCounters + resultCollector->svCounter;
        for(int currentIndex = 0; currentIndex < resultCollector->svCounter; currentIndex++, positionSV++)
        {
            sv[positionSV] = resultCollector[currentIndex];
        }

        free(resultCollector);
    }

    sv = (int *) realloc(sv, sizeof(int) * sumOfsvCount);                               // Resize subarray to counted value
    if(sv == NULL) return -1;

    return sumOfsvCounters;
}

// int vector_get_in_range(int v[], int v_sz, int sv[], int min, int max, int n_processes);
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

    for(int ongoingProcesses = 0; ongoingProcesses < n_processes; ongoingProcesses++)   //
    {
        if(sliceLeftover > 0)                                                           // If there is a remainder, it must be added to slice
        {
            sliceAddLeftover = 1;
            sliceLeftover--;
        }
        else
        {
            sliceAddLeftover = 0;
        }

        sliceIndexEnd = sliceIndexEnd + slices + sliceAddLeftover;                      // Array ending index, if there is a remainder, add it

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

            write(pipesFDS[pipeIndex+1], svCount, sizeof(long));                        // Write counted value
            write(pipesFDS[pipeIndex+1], sv, sizeof(long) * svCount[0]);                // Write valid numbers

            close(pipesFDS[pipeIndex+1]);                                               // Close read channel (1)

            free(pipesFDS);
            free(sv);

            exit(0);
        }

        sliceIndexIni = sliceIndexEnd;                                                  // Adjust subarray next beginning
        pipeIndex += PIPE_UNICHANNEL;                                                   // Next pipe set
    }                                                                                   //

    long sumOfsvCount = 0;

    for(pipeIndex = 0; pipeIndex < (n_processes * PIPE_UNICHANNEL); pipeIndex += PIPE_UNICHANNEL)
    {
        //TODO: Safe read
        close(pipesFDS[pipeIndex+1]);                                                   // Close read channel (1)

        read(pipesFDS[pipeIndex], svCount, sizeof(long));
        read(pipesFDS[pipeIndex], &sv[sumOfsvCount], sizeof(int) * svCount[0]);

        sumOfsvCount = sumOfsvCount + svCount[0];

        close(pipesFDS[pipeIndex]);                                                     // Close write channel (0)
    }

    for(int closeProcesses = 0; closeProcesses < n_processes; closeProcesses++)         // Wait for children
    {
        wait(NULL);
    }

    sv = (int *) realloc(sv, sizeof(int) * sumOfsvCount);                               // Resize subarray to counted value
    if(sv == NULL) return -1;

    free(pipesFDS);

    return sumOfsvCount;
}
// ------------------------------------------------------------------------------------- //
// ------------------------------------------------------------------------------------- //

// CUSTOM FUNCTIONS -------------------------------------------------------------------- //
// ------------------------------------------------------------------------------------- //

// APOIOTP1 FUNCTIONS------------------------------------------------------------------- //
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
// ------------------------------------------------------------------------------------- //
