// Answers:
// F F V F

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
    for(int i=0; i < 10; ++i)
    {
        execlp("date", "date", NULL);

        sleep(1);
    }

    return 0;
}
