// HEADERS ------------------------------------------------------------------ // {{{1
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
// -------------------------------------------------------------------------- // 1}}}

// MACROS ------------------------------------------------------------------- // {{{1
#define CHILD 0
// MACROS ------------------------------------------------------------------- // 1}}}

void process_work(long niter)
{
    for (long i = 0; i < niter; i++)
    {
        sqrt(rand());
    }
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Low arguments\n");
        return -1;
    }

    int iterate = 0;
    int numberChildren=atoi(argv[1]);

    for(; iterate < numberChildren; iterate++)
    {
        pid_t pids = fork();

        if(pids < CHILD)
        {
            perror("ERROR");
            return -1;
        }
        else if(pids == CHILD)
        {
            process_work(1e9);
            return 0;
        }
    }

    for(iterate=0; iterate < numberChildren; iterate++)
    {
        wait(NULL);
    }

    return 0;
}
