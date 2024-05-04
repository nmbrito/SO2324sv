#ifndef VECTOR_STAT_SERVER_UTILS_H
#define VECTOR_STAT_SERVER_UTILS_H
// MACROS ------------------------------------------------------------------- // {{{1
// Provided (apoioTP1)
#define LOWER_LIMIT             0
#define UPPER_LIMIT             100
// Custom macros
#define CHILD                   0
#define PIPE_UNICHANNEL         2
#define MAXIMUM_LIMIT           200
// -------------------------------------------------------------------------- // 1}}}

int tcp_socket_server_init (int serverPort);                // From iohelpers
int tcp_socket_server_accept (int serverSocket);            // From iohelpers
int tcp_socket_client_init (const char *host, int port);    // From iohelpers

int un_socket_server_init (const char *serverEndPoint);
int un_socket_server_accept (int serverSocket);
int un_socket_client_init (const char *serverEndPoint);

// From SO2324sv iohelpers files
int readn(int fd, void * buf, size_t count);
int writen(int fd, const void * buf, size_t count); 
int tcp_socket_create(char* ip, int port);
int tcp_socket_accept(int socketFd);
int tcp_socket_connect(char* ip, int port);
void fatal(char* msg);


#endif
