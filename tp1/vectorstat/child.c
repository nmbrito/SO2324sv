int childlabor(int **v, int **v2)
{
    // Pipe creation
    if(pipe(pipesfds) < 0)
    {
        perror("Error creating pipe");
        return -1;
    }

    // Fork creation
    pid_t forker = fork();
    if(forker < CHILD)
    {
        perror("Error forking");
        return -1;
    }
    else if(forker == CHILD)
    {
        close(pipesfds[READ]);

    }
    else
    {
        close(pipesfds[WRITE]);
    }
}

