#ifndef CHILD_H
#define CHILD_H
// MACROS ------------------------------------------------------------------- //
// Provided (apoioTP1)
#define LOWER_LIMIT             0
#define UPPER_LIMIT             100

// Custom macros
#define CHILD                   0
#define READ                    STDIN_FILENO
#define WRITE                   STDOUT_FILENO
#define PIPE_UNICHANNEL         2
#define PIPE_BICHANNEL          4
#define ARGUMENT_COUNT_ERROR    -1

int childlabor();

#endif
