#ifndef VECTOR_STAT_PROC_FUNCS_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/time.h>
#endif

int vector_get_in_range(int v[], int v_sz, int sv[], int min, int max, int n_processes);
int get_random(int min, int max);
void vector_init_rand(int v[], long dim, int min, int max);

