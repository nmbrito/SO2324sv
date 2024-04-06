// HEADERS ------------------------------------------------------------------ // {{{1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
    if(argc != 2)
    {
        printf("Low arguments\n");
        return -1;
    }

    char *countArguments[4];

    countArguments[0] = strdup("wc");   // program: wc
    countArguments[1] = strdup("-w");   // arguments: -w
    countArguments[2] = argv[1];        // terminal argument
    countArguments[3] = NULL;           // mark end of array

    execvp(countArguments[0], countArguments);

    return 0;
}
