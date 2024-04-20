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
#define BUFSIZE 128
#define CHILD   0
// -------------------------------------------------------------------------- // 1}}}

int main(int argc, char *argv[])
{
    int pipes[2];

    pipe(pipes);

    if(fork() == CHILD)
    {
        char *countArguments[2];

        countArguments[0] = strdup("lscpu");        // program: lscpu
        countArguments[1] = NULL;                   // mark end of array

        close(pipes[0]);                            // close read channel

        dup2(pipes[1], STDOUT_FILENO);              // redirect standard output to pipe write channel

        execvp(countArguments[0], countArguments);  // exec lscpu
        perror("exec error");

        exit(0);
    }
    else
    {
        char buf[BUFSIZE];  // store buffer
        int byteCount = 0;  // initiate a counter

        close(pipes[1]);    // close write pipe

        do
        {
            byteCount = read(pipes[0], buf, sizeof(char) * BUFSIZE);    // count the number of read bytes and store in buf
            for(int i = 0; i < byteCount; i++)
            {
                buf[i] = toupper(buf[i]);                               // upper case each char
            }

            write(STDOUT_FILENO, buf, byteCount);                       // write it out

        }while(byteCount > 0);

        wait(NULL);

        return 0;
    }
}
