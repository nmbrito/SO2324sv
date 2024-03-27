#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "child.h"

//int childlabor(int **v, int **v2)
int childlabor()
{
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
        printf("ALLOOOOOO");
        return 0;
    }
}
