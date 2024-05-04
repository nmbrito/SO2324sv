// ./vector_stat_server <processing type>
// -p -> multiple processes
// -t -> multiple threads

/*
 * Passos:
 *  Definir socket TCP
 *  Servidor processa o vetor usando as funções anteriores
 *  O servidor deve ser estruturado de forma concorrente usando uma tarefa dedicada a cada ligação com um cliente.
 *
 *  Definir socket UNIX
 *  Um processo, múltiplas tarefas
 *
 *  Funcionalidade multiplas tarefas / multiplos processos
 */
// HEADERS ------------------------------------------------------------------ //
// System
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "vector_stat_proc_utils.h"
#include "vector_stat_server_utils.h"
// -------------------------------------------------------------------------- //

// MAIN --------------------------------------------------------------------- //
// argv[0] -> program name
// argv[1] -> processing type
int main(int argc, char *argv[])
{
    // Check arguments
    if(argc != 2)
    {
        printf("Syntax wrong. Usage: $ ./vector_stat_server <processing type> ");
        return -1;
    }

    // if t

    // if p

    int socket = tcp_socket_server_init(

    return 0;
}
