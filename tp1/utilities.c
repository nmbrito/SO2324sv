// HEADERS ----------------------------------------------------------------------------- // {{{1
// System
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Custom
#include "utilities.h"
// ------------------------------------------------------------------------------------- // 1}}}

// ASSIGNMENT WORK---------------------------------------------------------------------- // {{{1
// int vector_get_in_range(int v[], int v_sz, int sv[], int min, int max, int n_processes); {{{2
int vector_get_in_range(int v[], int v_sz, int sv[], int min, int max, int n_processes)
{
    long slices = v_sz / n_processes;                                                   // Number of sections splits in the array depending on number of processes
    long sliceLeftover = v_sz % n_processes;                                            // Store residue for further split calculations

    int addLeftover = 0;                                                                // Aligns elements depending on residue
    int moveLeftover = 0;                                                               // Aligns array forward move depending on residue

    long svCount[1] = {0};                                                              // Stores counted values written in sv array by child process

    int *vAddress = v;                                                                  // Stores the original v address
    int *svAddress = sv;                                                                // Stores the original sv address
                                                                                        //
    sv = realloc(sv, (sizeof(int) * slices));                                           // Instead of sending a sizeable array, send only the needed size

    int *pipesFDS = createIntArrays(&pipesFDS, (n_processes * PIPE_UNICHANNEL));        // Create pipe array
    int *pipesFDSAddress = pipesFDS;                                                    // Stores the original pipe address

    for(int ongoingProcesses = 0; ongoingProcesses < n_processes; ongoingProcesses++)
    {
        if(sliceLeftover > 0)                                                           // Array adjustment
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

        pipe(pipesFDS);                                                                 // Pipe creation for each child

        pid_t forker = fork();                                                          // Fork creation

        if(forker < CHILD)
        {
            perror("Error forking");
            return ERROR_RETURN;
        }
        else if(forker == CHILD)
        {
            close(pipesFDS[READ]);                                                      // Child will write only

            for (long i = 0; i < (slices + addLeftover); i++)                           // Write valid values to array
            {
                if (v[i] >= min && v[i] <= max)
                {
                    sv[svCount[0]++] = v[i];
                }
            }

            write(pipesFDS[WRITE], svCount, sizeof(long));                              // Send counted numbers to parent
            write(pipesFDS[WRITE], sv, (sizeof(int) * svCount[0]));                     // Then write the subarray to parent

            close(pipesFDS[WRITE]);                                                     // After job done, close write pipe

            free(v);                                                                    // Child free array
            free(sv);                                                                   // Child free subarray
            free(pipesFDS);                                                             // Child free pipe array

            return CHILD_RETURN_SUCCESS;                                                // It cannot return 0, otherwise it'll be stuck in main
        }
        else
        {
            v += (slices+moveLeftover);                                                 // Move to next slice address
            pipesFDS += PIPE_UNICHANNEL;                                                // Move to next pipe address
        }
    }

    long countNumber = 0;                                                               // Allows parent process to store counted values

    pipesFDS = pipesFDSAddress;                                                         // Restores original pipesFDS address

    sv = realloc(sv, (sizeof(int) * v_sz));                                             // Restores subarray to full size

    for(int closeProcesses = 0; closeProcesses < n_processes; closeProcesses++)         // Pipe reading
    {
        close(pipesFDS[WRITE]);                                                         // Parent will read only

        read(pipesFDS[READ], svCount, sizeof(long));                                    // Read the counted valid numbers
        read(pipesFDS[READ], sv, sizeof(int) * svCount[0]);                             // Read svCount[0] bytes of the subarray sent by child process

        close(pipesFDS[READ]);                                                          // Close the read pipe

        countNumber += svCount[0];                                                      // Sums the valid counted values to the previous read

        sv += svCount[0];                                                               // Align the array for the next read

        pipesFDS += PIPE_UNICHANNEL;                                                    // Next pair os pipes
    }

    v = vAddress;                                                                       // Because the v array was moved around, restore the original address
    sv = svAddress;                                                                     // Because the subarray was moved around, restore the original address
    sv = realloc(sv, (sizeof(int) * countNumber));                                      // Resize the subvalues to the number of read valid values

    pipesFDS = pipesFDSAddress;                                                         // Restores, yet again, the pipe address

    free(pipeFDS);                                                                      // PipeFDS array was created in this function, array gets freed

    for(int closeProcesses = 0; closeProcesses < n_processes; closeProcesses++)         // Waits for children
    {
        wait(NULL);
    }

    return countNumber;
}
// ------------------------------------------------------------------------------------- // 2}}}
// ------------------------------------------------------------------------------------- // 1}}}

// CUSTOM FUNCTIONS -------------------------------------------------------------------- // {{{1
// int *createIntArrays(int **array, long arrayDim); ----------------------------------- // {{{2
int *createIntArrays(int **array, long arrayDim)
{
    printf("Initializing a vector of %ld bytes\n", arrayDim);

    *array = (int *) malloc(sizeof(int) * arrayDim);
    if (array == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        return ERROR_RETURN;
        //exit(0); // Not yet
    }

    return *array;
}
// ------------------------------------------------------------------------------------- // 2}}}
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
// ------------------------------------------------------------------------------------- // 1}}}
