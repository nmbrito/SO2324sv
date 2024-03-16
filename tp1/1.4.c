/*
 * Answers:
 *  F F V F
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Forks and stuff
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CHILD 0

int main(int argc, char *argv[])
{
    for(int i=0; i < 10; ++i)
    {
        execlp("date", "date", NULL);

        sleep(1);
    }

    return 0;
}
