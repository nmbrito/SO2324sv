// ASSIGNMENT WORK----------------------------------------------------------- //
int vector_get_in_range(int v[], int v_sz, int sv[], int min, int max, int n_processes)
{
    // TODO
}

// CUSTOM FUNCTIONS --------------------------------------------------------- //
void createVectors(int *vector, long vsize)
{
    printf("Initializing a vector of %ld bytes\n", values_sz);

    int *vector = malloc(sizeof(int) * vsize);
    if (values == NULL)
    }
        fprintf(stderr, "Memory allocation error\n");
        return -1;
    }
}

// APOIOTP1 FUNCTIONS-------------------------------------------------------- //
// Random number generator
int get_random(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

// Initiate vector with random numbers
void vector_init_rand(int v[], long dim, int min, int max)
{
    for (long i = 0; i < dim; i++)
    {
        v[i] = get_random(min, max);
    }
}

// Sequential version
int vector_get_in_range_seq(int v[], int v_sz, int sv[], int min, int max)
{
    long count = 0;

    for (long i = 0; i < v_sz; i++) {
        if (v[i] >= min && v[i] <= max) {
            sv[count++] = v[i];
        }
    }        
    return count;
}

// TODO
void codeEval()
{
    struct timeval t1,t2;
    gettimeofday(&t1, NULL);

    // start of code to evaluate
    long count     = 0;
    int values_min = 50;
    int values_max = 100;

    count = vector_get_in_range(values, values_sz, subvalues, values_min, values_max);
    // end of code to evaluate

    gettimeofday(&t2, NULL);
    long elapsed = ((long)t2.tv_sec - t1.tv_sec) * 1000000L + (t2.tv_usec - t1.tv_usec);
    long sec = elapsed / (long)1e6;
    long aux = elapsed % (long)1e6;
    long mil = aux / (long)1e3;
    long mic = aux % (long)1e3;

    printf ("Elapsed time = %lds%ld,%ldms\n", sec, mil, mic);

    printf("Values between [%d..%d]: %ld\n", values_min, values_max, count);
}
