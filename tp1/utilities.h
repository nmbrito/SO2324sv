#ifndef UTILITIES_H
#define UTILITIES_H
// MACROS ------------------------------------------------------------------- //
// Provided (apoioTP1)
#define LOWER_LIMIT             0
#define UPPER_LIMIT             100
#define MAXIMUM_LIMIT           200

// Custom macros
#define CHILD                   0
#define READ                    STDIN_FILENO
#define WRITE                   STDOUT_FILENO
#define PIPE_UNICHANNEL         2
#define PIPE_BICHANNEL          4
#define ERROR_RETURN            -1
#define CHILD_RETURN_SUCCESS    -2

int vector_get_in_range(int v[], int v_sz, int sv[], int min, int max, int n_processes);
int *createIntArrays(int **array, long arrayDim);
int get_random(int min, int max);
void vector_init_rand(int v[], long dim, int min, int max);
int vector_get_in_range_seq(int v[], int v_sz, int sv[], int min, int max);
void codeEval();

#endif
