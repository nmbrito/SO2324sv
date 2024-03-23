
    // Variváreis do apoioTP1
        //long values_sz = 256*1024*1024L;
        long values_sz = atol(argv[1]);

        // allocate a vector of initial values
        int *values = malloc(sizeof(int) * values_sz);
        if (values == NULL)
        {
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

        // initiate initial array of values 
        vector_init_rand(values, values_sz, LOWER_LIMIT, UPPER_LIMIT);

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
