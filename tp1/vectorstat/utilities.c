#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "utilities.h"

// ASSIGNMENT WORK----------------------------------------------------------- //
int vector_get_in_range(int v[], int v_sz, int sv[], int min, int max, int n_processes)
{
    int slices = v_sz / n_processes;
    int sliceLeftover = v_sz % n_processes;
    int countnumber = 0;

    // Pipe array
    int *pipesfds = createArrays(&pipesfds, n_processes * PIPE_UNICHANNEL);

    for(n_processes; n_processes > 0; n_processes--)
    {
        for(sliceLeftover; sliceLeftover > 0; sliceLeftover--, n_processes--)
        {
            // TODO: send
            // Enviar *v a *(v+slices)) -> à partida está feito
            countnumber = childlabor(&v, &(v+slices));
            //int i=childlabor();
            v=v+(slices+1);
            pipesfds += PIPE_UNICHANNEL;
        }

        // TODO: send
        // Enviar *v a *(v+(slices-1)) -> à partida está feito
        countnumber = childlabor(&v, &(v+slices-1));
        //int i=childlabor();
        v=v+slices;
        pipesfds += PIPE_UNICHANNEL;
    }

    wait(NULL); // Parent waits for children
    //for(int i = 0; i > n_processes; i+=PIPE_UNICHANNEL)
    //{
    //    close(pipesfds[i];
    //}

    return countnumber;
}

// CUSTOM FUNCTIONS --------------------------------------------------------- //
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

// APOIOTP1 FUNCTIONS-------------------------------------------------------- //
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
