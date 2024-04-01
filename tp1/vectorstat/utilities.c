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
    int slices = v_sz / n_processes;        // Number of elements to assign
    int sliceLeftover = v_sz % n_processes; // Odd number residue

    int addLeftover = 0;                    // Adds value to v[] address
    int moveLeftover = 0;                   // Forward v[] address

    long svCount[1] = 0;                    // Number of items written in sv

    // Pipe array
    int *pipesFDS = createArrays(&pipesFDS, (n_processes * PIPE_UNICHANNEL));
    int *pipesFDSAddress = pipesFDS;

    for(int ongoingProcesses = 0; ongoingProcesses < n_processes; ongoingProcesses++)
    {
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
        if(forker < CHILD)  // Child error
        {
            perror("Error forking");
            return -1;
        }
        else if(forker == CHILD)    // Child work
        {
            close(pipesFDS[READ]);  // Child only writes to parent

            // *v to *(v+slices+addLeftover) // Valores, sem * = endereço
            long count = 0;
            for (long i = 0; i < (slices + addLeftover); i++) //Origina: for (long i = 0; i < v_sz; i++)
            {
                if (v[i] >= min && v[i] <= max)
                {
                    sv[count++] = v[i];
                    /**///sv[svCount[0]++] = v[i];
                }
            }        

            // Pipe write
            /**/write(pipesFDS[WRITE], svCount, (sizeof(long) * count));
            /**///write(pipesFDS[WRITE], svCount, (sizeof(long) * svCount[0]));
            write(pipesFDS[WRITE], sv, (sizeof(int) * count));
            /**///write(pipesFDS[WRITE], sv, (sizeof(int) * svCount[0]));

            // Pipe close
            close(pipesFDS[WRITE]);

            free(v);
            free(sv);
            free(pipesFDS);

            return 0;
        }
        else    // Parent work
        {
            v=v+(slices+moveLeftover);      // Move to next element address
            pipesFDS += PIPE_UNICHANNEL;    // Move to next pipe address

        }
    }

    /**/long countnumber = 0;

    pipesFDS = pipesFDSAddress;  // Recover original address
    sv = realloc(sv, (sizeof(int) * v_sz));

    for(int closeProcesses = 0; closeProcesses < n_processes; closeProcesses++)
    {
        close(pipesFDS[WRITE]);

        // Se isto funcionar, escuso de fazer a deteção do -1
        /**/read(pipesFDS[READ], svCount, sizeof(long) * 1);
        read(pipesFDS[READ], arraySubValues, sizeof(int) * svCount[0]);

        /**/countnumber += svCount[0];
        close(pipesFDS[READ]);
        pipesFDS += 1;

    }

    sv = realloc(sv, (sizeof(int) * countnumber));

    // Wait for children
    for(int closeProcesses = 0; closeProcesses < n_processes; closeProcesses++)
    {
        wait(NULL);
    }

    return countnumber;
}
// -------------------------------------------------------------------------- // 1}}}

// CUSTOM FUNCTIONS --------------------------------------------------------- // {{{1
int createArrays(int **vector, long vsize)
{
    printf("Initializing a vector of %ld bytes\n", vsize);

    *vector = (int *) malloc(sizeof(int) * vsize);
    if (vector == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        return -1;
    }
    
    return *vector;
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
