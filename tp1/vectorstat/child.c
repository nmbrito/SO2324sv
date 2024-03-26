#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "child.h"
int childlabor(int **v, int **v2)
{
    // Pipe creation
    //if(pipe(pipesfds) < 0)
    //{
    //    perror("Error creating pipe");
    //    return -1;
    //}

    // Fork creation
    pid_t forker = fork();
    if(forker < CHILD)
    {
        perror("Error forking");
        return -1;
    }
    else if(forker == CHILD)
    {
        //close(pipesfds[READ]);
        printf("Eu sou filho %d", forker);
        return 0;
    }
    else
    {
        //close(pipesfds[WRITE]);

    }
}

