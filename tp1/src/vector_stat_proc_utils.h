#ifndef VECTOR_STAT_PROC_UTILS_H
#define VECTOR_STAT_PROC_UTILS_H
// MACROS ------------------------------------------------------------------- // {{{1
// Provided (apoioTP1)
#define LOWER_LIMIT             0
#define UPPER_LIMIT             100
#define MAXIMUM_LIMIT           200
// Custom macros
#define CHILD                   0
#define PIPE_UNICHANNEL         2
// -------------------------------------------------------------------------- // 1}}}

// FUNCTIONS ---------------------------------------------------------------- // {{{1
int vector_get_in_range(int v[], int v_sz, int sv[], int min, int max, int n_processes);
int get_random(int min, int max);
int vector_get_in_range_seq(int v[], int v_sz, int sv[], int min, int max);
void vector_init_rand(int v[], long dim, int min, int max);
//void codeEval();
// -------------------------------------------------------------------------- // 1}}}

#endif

