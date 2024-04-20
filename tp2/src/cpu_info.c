// HEADERS ------------------------------------------------------------------ // {{{1
// System
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
// -------------------------------------------------------------------------- // 1}}}

// MACROS ------------------------------------------------------------------- // {{{1
#define BUFSIZE 1500
#define CHILD   0
// -------------------------------------------------------------------------- // 1}}}

//TODO: buffer size very limited... must be the same size as lscpu
int main(int argc, char *argv[])
{
    int pipes[2];

    pipe(pipes);

    if(fork() == CHILD)
    {
        char *countArguments[2];

        countArguments[0] = strdup("lscpu");    // program: wc
        countArguments[1] = NULL;               // mark end of array

        dup2(pipes[1], STDOUT_FILENO);

        execvp(countArguments[0], countArguments);

        exit(0);
    }

    //char *buf = (char *) malloc(sizeof(char) * strlen(pipes[0]);
    char buf[BUFSIZE];

    read(pipes[0], buf, sizeof(char) * BUFSIZE);

    for(int i = 0; i < BUFSIZE; i++)
    {
        buf[i] = toupper(buf[i]);
    }

    write(1, buf, BUFSIZE);

    wait(NULL);

    return 0;
}
