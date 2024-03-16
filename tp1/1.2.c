#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Forks and stuff
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CHILD 0

int main(int argc, char *argv[])
{
    printf("MSG 1\n");

    for(int i=0; i < 3; ++i)
    {
        if(fork() == 0)
        {
            printf("MSG 2\n");
        }
    }

    printf("MSG 3\n");

    return 0;
}
