#ifndef UTILITIES_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/time.h>
#endif

int vector_get_in_range(int v[], int v_sz, int sv[], int min, int max, int n_processes);
void createVectors(int *vector, long vsize);
int get_random(int min, int max);
void vector_init_rand(int v[], long dim, int min, int max);
int vector_get_in_range_seq(int v[], int v_sz, int sv[], int min, int max);
void codeEval();
