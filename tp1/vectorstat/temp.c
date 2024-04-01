
//int *arrayValues = NULL;
//int *arraySubValues = NULL;
//printf("slices: %d\n", slices);

//printf("De: %x\n a %x\n", v, v+slices);         // address
//printf("De: %d\n a %d\n", *v, *(v+slices));   // content
//printf("atual: %d\n", *v);   // content
//printf("De: %d\n a %d\n", *v, *(v+slices-1));   // content
//printf("atual: %d\n", *v);   // content




//Sliceleftover
            // TODO: send
            // Enviar *v a *(v+slices)) -> à partida está feito
            //countnumber = childlabor(&v, &(v+slices));
//Sem Sliceleftover
        // TODO: send
        // Enviar *v a *(v+(slices-1)) -> à partida está feito
        //countnumber = childlabor(&v, &(v+slices-1));


    //for(int i = 0; i > n_processes; i+=PIPE_UNICHANNEL)
    //{
    //    close(pipesfds[i];
    //}

    for(n_processes; n_processes > 0; n_processes--)
    {
        // This section happens if the number of elements or processes is odd
        for(sliceLeftover; sliceLeftover > 0; sliceLeftover--, n_processes--)
        {
            // Enviar *v a *(v+slices)) -> à partida está feito
            int i=childlabor();

            v=v+(slices+1);                 // Move to next element address
            pipesfds += PIPE_UNICHANNEL;    // Move to next pipe address
        }
        // Enviar *v a *(v+(slices-1)) -> à partida está feito

        int i=childlabor();

        v=v+slices;                     // Move to next element address
        pipesfds += PIPE_UNICHANNEL;    // Move to next pipe address
    }

//CHILDLABOR
    // Pipe creation
    //if(pipe(pipesfds) < 0)
    //{
    //    perror("Error creating pipe");
    //    return -1;
    //}


    for(int i = 0; i < (n_processes * PIPE_UNICHANNEL); i+=2)
    {
        close(pipesfds[i+1]);

        long counted = pipesfds[i];
        read(pipesfds[i] , , );

    }
