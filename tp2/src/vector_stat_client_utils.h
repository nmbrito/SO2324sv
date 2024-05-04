#ifndef VECTOR_STAT_PROC_UTILS_H
#define VECTOR_STAT_PROC_UTILS_H
// MACROS ------------------------------------------------------------------- // {{{1
// Provided (apoioTP1)
#define LOWER_LIMIT             0
#define UPPER_LIMIT             100
// Custom macros
#define CHILD                   0
#define PIPE_UNICHANNEL         2
#define MAXIMUM_LIMIT           200
// -------------------------------------------------------------------------- // 1}}}

int tcp_socket_server_init (int serverPort);
int tcp_socket_server_accept (int serverSocket);
int tcp_socket_client_init (const char *host, int port);
int un_socket_server_init (const char *serverEndPoint); int un_socket_server_accept (int serverSocket);
int un_socket_client_init (const char *serverEndPoint);
