#ifndef VECTOR_STAT_PROC_FUNCS_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/time.h>
#endif

/*
 * int v[]          - vetor a analisar
 * int v_sz         - tamanho do vetor
 * int sv[]         - vetor onde será guardado o subvetor
 *
 * int n_processes  - número de processos a utilizar
 * A função devolve o número de elementos colocados no subvetor sv ou um valor negativo em caso de erro.
 */
int vector_get_in_range (int v[], int v_sz, int sv[], int min, int max, int n_processes)
{

}

// Funções do ApoioTP1
/*
 * Generates a random number between min and max.
 * The number sequence generated by the fuction rand is always the 
 * same because it uses the defaulta seed 0.
 */
int get_random(int min, int max) 
{
    return rand() % (max - min + 1) + min;
}

/**
 * Starts the vector with random values belonging to the interval [min..max]
 */
void vector_init_rand(int v[], long dim, int min, int max)
{
    for (long i = 0; i < dim; i++) {
        v[i] = get_random(min, max);
    }
}

// SEQUENTIAL!!!!
/**
 * Gets the subvector of values in the range [min..max]
 * 
 * returns the number of values store in subvector sv 
 */
//int vector_get_in_range (int v[], int v_sz, int sv[], int min, int max)
//{
//    long count = 0;
//
//    for (long i = 0; i < v_sz; i++) {
//        if (v[i] >= min && v[i] <= max) {
//            sv[count++] = v[i];
//        }
//    }        
//    return count;
//}