// Minhas funções

/*
 * int v[]  - vetor a analisar
 * int v_sz - tamanho do vetor
 * int sv[] - vetor onde será guardado o subvetor
 * int n_processes  - número de processos a utilizar
 * Devolve número de elementos colocados no subvetor sv ou -1 se erro.
 */
int vector_get_in_range(int v[], int v_sz, int sv[], int min, int max, int n_processes)
{
    int elementosPorFilho = v_sz / n_processes;
    int restos = v_sz % n_processes;
    int vOrigem = v;

    // Criação de pipes
    int *tubosFD = (int *) sizeof(int) * (n_processes * UNIDIRECIONAL);

    if(restos == 0)
    {
        int elementosPorFilhoRetificado = elementosPorFilho++;
    }

    for(elementosPorFilho; elementosPorFilho > 0; elementosPorFilho--)
    {
        for(restos; restos > 0; restos--, elementosPorFilho--)
        {
            processoFilho();
            v += elementosPorFilhoRetificado;
            tubosFD += UNIDIRECIONAL;
        }
            processoFilho();
            v += elementosPorFilho;
            tubosFD += UNIDIRECIONAL;
    }

    //long count = 0;
    //for (long i = 0; i < v_sz; i++)
    //{
    //    if (v[i] >= min && v[i] <= max)
    //    {
    //        sv[count++] = v[i];
    //    }
    //}        
    //return count;
}

// Funções do ApoioTP1
void alocaVetores(int *values, int *subvalues)
{
    printf("Initializing a vector of %ld bytes\n", values_sz);

    // allocate a vector of initial values
    int *values = malloc(sizeof(int) * values_sz);
    if (values == NULL)
    }
        fprintf(stderr, "Erro malloc\n");
        return -1;
    }
    
    // allocate a subvector where will be store values in a interval of values
    int *subvalues = malloc(sizeof(int) * values_sz);
    if (subvalues == NULL)
    {
        fprintf(stderr, "Erro malloc\n");
        return -1;
    }
}
// Gera número aleatório entre min e máx. Usa o default seed: 0.
int get_random(int min, int max) 
{
    return rand() % (max - min + 1) + min;
}

// Starts the vector with random values belonging to the interval [min..max]
void vector_init_rand(int v[], long dim, int min, int max)
{
    for (long i = 0; i < dim; i++)
    {
        v[i] = get_random(min, max);
    }
}

// Obtém o subvetor de valores entre min e máx. Devolve o valor guardado em sv.
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

void avaliaCodigo() //TODO
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
