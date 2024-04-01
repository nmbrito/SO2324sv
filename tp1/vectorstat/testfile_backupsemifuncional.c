
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

// MACROS ------------------------------------------------------------------- //
// Provided (apoioTP1)
#define LOWER_LIMIT             0
#define UPPER_LIMIT             100

// Custom macros
#define CHILD                   0
#define READ                    STDIN_FILENO
#define WRITE                   STDOUT_FILENO
#define PIPE_UNICHANNEL         2
#define PIPE_BICHANNEL          4
#define ARGUMENT_COUNT_ERROR    -1

// MAIN --------------------------------------------------------------------- // {{{1
// argv[0] -> program name
// argv[1] -> vector dimension
// argv[2] -> number of processes
int main(int argc, char *argv[])
{

    if(argc != 3)
    {
        printf("Utilização incorreta. Forma correta: ./vector_stat_proc <dimensão_vetor> <número_de_processos>");
        printf("Syntax wrong. Usage: $ ./vector_stat_proc <vector dimension> <number processes>");

        return -1;
    }

    long arraySize = atoi(argv[1]);
    int numberProcesses = atoi(argv[2]);
    int pipesize = numberProcesses * PIPE_UNICHANNEL;

    int slices = arraySize / numberProcesses;        // Number of elements to assign
    int sliceLeftover = arraySize % numberProcesses; // Odd number residue

    int addLeftover = 0;                    // Adds value to v[] address
    int moveLeftover = 0;                   // Forward v[] address

    long svNumberQTD = 0;                   // Number of items written in sv
    
    // Arrays
    int *arrayValues = (int *) malloc(sizeof(int) * arraySize);
    int *arraySubValues = (int *) malloc(sizeof(int) * ((arraySize / numberProcesses) + 1)); // ou ((arraySize / numberProcesses) + 1)
    int *pipesfds = (int *) malloc(sizeof(int) * pipesize);
    int *pipesfdsBackup = pipesfds;

    arrayValues[0] = 20;
    arrayValues[1] = 40;
    arrayValues[2] = 60;
    arrayValues[3] = 80;
    arrayValues[4] = 100;
    arrayValues[5] = 120;
    arrayValues[6] = 140;
    arrayValues[7] = 160;
    arrayValues[8] = 180;
    arrayValues[9] = 200;

    for(int ongoingProcesses = 0; ongoingProcesses < numberProcesses; ongoingProcesses++)
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

        pipe(pipesfds);

        // Fork creation
        pid_t forker = fork();
        if(forker < CHILD) // Fork error
        {
            perror("Error forking");
            return -1;
        }
        else if(forker == CHILD) // Child work
        {
            close(pipesfds[READ]);  // Child only writes to parent

            long count = 0;
            for (long i = 0; i < (slices+addLeftover); i++)
            {
                if (arrayValues[i] >= LOWER_LIMIT && arrayValues[i] <= UPPER_LIMIT)
                {
                    arraySubValues[count++] = arrayValues[i];
                }
            }
            //arraySubValues[count+1] = -1;
            //count++;
            //realloc(arraySubValues, sizeof(int) * count);

            //pipesfds[WRITE] = count;
            
            //write(pipesfds[WRITE], count, sizeof(long)); //se a estratégia do -1 for usada, isto desaparece
            write(pipesfds[WRITE], arraySubValues, sizeof(int) * count);

            close(pipesfds[WRITE]);

            free(arrayValues);
            free(arraySubValues);
            free(pipesfds);

            return 0;
        }
        else // Parent work
        {
            arrayValues=arrayValues+(slices+moveLeftover);      // Move to next element address
            pipesfds += PIPE_UNICHANNEL;    // Move to next pipe address
        }
    }

    pipesfds = pipesfdsBackup; //NOTE: Isto bomba
    //int *arraySubValuesMaster = (int *) malloc(sizeof(int) * arraySize);

    for(int i = 0; i < numberProcesses; i++)
    {
        close(pipesfds[WRITE]);

        //long counted = pipesfds[READ];
        //read(pipesfds[READ], &svNumberQTD, sizeof(long));
        read(pipesfds[READ], arraySubValues, sizeof(int)*10);

        close(pipesfds[WRITE]);
        pipesfds += 1;
    }

    for(int closeProcesses = 0; closeProcesses < numberProcesses; closeProcesses++)
    {
        wait(NULL); // Parent waits for children
    }
//size_t read (int fd, void* buf, size_t cnt);
//size_t write (int fd, void* buf, size_t cnt);

}
