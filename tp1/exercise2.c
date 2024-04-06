//Answers:
//F F F V

// HEADERS ------------------------------------------------------------------ // {{{1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
// -------------------------------------------------------------------------- // 1}}}

// MACROS ------------------------------------------------------------------- // {{{1
#define CHILD 0
// MACROS ------------------------------------------------------------------- // 1}}}

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
