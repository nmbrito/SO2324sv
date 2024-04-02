// HEADERS ------------------------------------------------------------------ // {{{1
// System
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Custom
#include "utilities.h"

// -------------------------------------------------------------------------- // 1}}}

// ASSIGNMENT WORK----------------------------------------------------------- // {{{1
int vector_get_in_range(int v[], int v_sz, int sv[], int min, int max, int n_processes)
{
    // Array size section for each child
    long slices = v_sz / n_processes;
    long sliceLeftover = v_sz % n_processes;

    // Array position if there is remainder
    int addLeftover = 0;
    int moveLeftover = 0;

    // Store counted values written in sv array
    long svCount[1] = {0};

    // Resize sv (smaller array for children)
    int *svAddress = sv;
    sv = realloc(sv, (sizeof(int) * slices));

    // Pipe array
    int *pipesFDS = createIntArrays(&pipesFDS, (n_processes * PIPE_UNICHANNEL));
    int *pipesFDSAddress = pipesFDS;

    for(int ongoingProcesses = 0; ongoingProcesses < n_processes; ongoingProcesses++)
    {
        // Array element alignments
        if(sliceLeftover > 0)
        {
            addLeftover = 0;
            moveLeftover = 1;
            sliceLeftover--;
        }
        else
        {
            addLeftover = -1;
            moveLeftover = 0;
        }

        // Pipe creation
        pipe(pipesFDS);

        // Fork creation
        pid_t forker = fork();

        if(forker < CHILD)
        {
            perror("Error forking");
            return -1;
        }
        else if(forker == CHILD)
        {
            // Child will write only
            close(pipesFDS[READ]);

            // Write valid values to array
            for (long i = 0; i < (slices + addLeftover); i++)
            {
                if (v[i] >= min && v[i] <= max)
                {
                    sv[svCount[0]++] = v[i];
                }
            }

            // Pipe write counted valid numbers, then array
            write(pipesFDS[WRITE], svCount, sizeof(long));
            write(pipesFDS[WRITE], sv, (sizeof(int) * svCount[0]));

            // Pipe close
            close(pipesFDS[WRITE]);

            // Child needs to free these arrays
            free(v);
            free(sv);
            free(pipesFDS);

            return -2;
        }
        else
        {
            v += (slices+moveLeftover);     // Move to next element address
            pipesFDS += PIPE_UNICHANNEL;    // Move to next pipe address

        }
    }

    long countNumber = 0;

    // Recover original pipesFDS address
    pipesFDS = pipesFDSAddress;

    // Restores sv to full size
    sv = realloc(sv, (sizeof(int) * v_sz));

    // Parent reads all pipes
    for(int closeProcesses = 0; closeProcesses < n_processes; closeProcesses++)
    {
        // Parent will read only
        close(pipesFDS[WRITE]);

        // Read counted valid numbers
        read(pipesFDS[READ], svCount, sizeof(long));
        read(pipesFDS[READ], sv, sizeof(int) * svCount[0]);

        // Close pipe
        close(pipesFDS[READ]);

        // Store and sum valid counted numbers
        countNumber += svCount[0];

        // Move sv forward
        sv += (int) svCount[0]; //ISTO DEIXA-ME PREOCUPADO! Vai andar ints ou longs???

        // Next pair of pipes
        pipesFDS += PIPE_UNICHANNEL;

    }

    // Recover original sv address
    sv = svAddress;
    sv = realloc(sv, (sizeof(int) * countNumber));

    // Wait for children
    for(int closeProcesses = 0; closeProcesses < n_processes; closeProcesses++)
    {
        wait(NULL);
    }

    return countNumber;
}
// -------------------------------------------------------------------------- // 1}}}

// CUSTOM FUNCTIONS --------------------------------------------------------- // {{{1
int *createIntArrays(int **array, long arrayDim)
{
    printf("Initializing a vector of %ld bytes\n", arrayDim);

    *array = (int *) malloc(sizeof(int) * arrayDim);
    if (array == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        return -1;
        //exit(0); // Not yet
    }

    return *array;
}
// -------------------------------------------------------------------------- // 1}}}

// APOIOTP1 FUNCTIONS-------------------------------------------------------- // {{{1
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
