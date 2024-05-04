// Part 1
///*
int main ()
{
    int s = tcp_serversocket_init(HOST, PORT);
    while (1)
    {
        int ns = tcp_serversocket_accept(s);
        handle_client(ns);
    }

    return 0;
}
//*/

// Part 2
/*
void `thHandleCient (void *arg)
{
    int ns = *((int *)arg);
    handle_client(ns);
    return NULL;
}

int main ()
{
    int s = tcp_serversocket_init(HOST, PORT);
    pthread_t th;
    while (1)
    {
        int ns = tcp_serversocket_accept(s);
        int *ps = malloc(sizeof(int));
        *ps = ns;
        pthread_create(&th, NULL,
        pthread_join(th);
    }

    return 0;
}
*/
