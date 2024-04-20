// HEADERS ------------------------------------------------------------------ // {{{1
#include <error.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
// -------------------------------------------------------------------------- // 1}}}

// MACROS ------------------------------------------------------------------- // {{{1
// MACROS ------------------------------------------------------------------- // 1}}}

//void process_work(long niter)
void *process_work(void *niterCasted)
{
    long niter = (long) niterCasted;

    for (long i = 0; i < niter; i++)
    {
        sqrt(rand());
    }
    
    return NULL;
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Low arguments\n");
        return -1;
    }

    int threadNumber=atoi(argv[1]);
    long tooLongForVoid = 1e9;

    pthread_t *threadID = (pthread_t *) malloc(sizeof(pthread_t) * threadNumber);

    // Create threads
    for(int iterate = 0; iterate < threadNumber; iterate++)
    {
        pthread_create(&threadID[iterate], NULL, process_work, &tooLongForVoid);
    }

    // Join threads
    for(int iterate = 0; iterate < threadNumber; iterate++)
    {
        pthread_join(threadID[iterate], NULL);
    }

    return 0;
}
