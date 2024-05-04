// HEADERS ------------------------------------------------------------------ //
// System
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "vector_stat_proc_utils.h"
#include "vector_stat_server_utils.h"
// -------------------------------------------------------------------------- //

// TCP/IP socket
int tcp_socket_server_init (int serverPort)
{

}

int tcp_socket_server_accept (int serverSocket)
{

}

int tcp_socket_client_init (const char *host, int port)

// Unix socket
int un_socket_server_init (const char *serverEndPoint)
{

}

int un_socket_server_accept (int serverSocket)
{

}

int un_socket_client_init (const char *serverEndPoint)
{

}

// From iohelpers ----------------------------------------------------------- //
int writen(int fd, const void * buf, size_t count) 
{
    int nBytesWR;
    const char * ptbuf = buf;
    size_t bytesToSend = count;

    while (bytesToSend > 0) 
    {
        nBytesWR = write(fd, ptbuf, bytesToSend);

        if (nBytesWR <= 0) 
            return nBytesWR;

        ptbuf += nBytesWR;
        bytesToSend -= nBytesWR;
    }

    return count;
}

int readn(int fd, void * buf, size_t count) 
{
    char * ptbuf = buf;
    size_t bytesToReceive = count;
    
    while (bytesToReceive > 0) 
    {
        int nBytesRD = read(fd, ptbuf, bytesToReceive);
        
        if (nBytesRD <= 0) 
			return nBytesRD;
			
        ptbuf += nBytesRD;
        bytesToReceive -= nBytesRD;
    }
    
    return count;
}

int readn2(int fd, void * buf, size_t count) 
{
    char * ptbuf = buf;
    size_t bytesToReceive = count;
    
    while (bytesToReceive > 0) 
    {
        int nBytesRD = read(fd, ptbuf, bytesToReceive);
        
        if (nBytesRD < 0) 
			return nBytesRD;
		
		if(nBytesRD == 0)
			return count - bytesToReceive;
			
        ptbuf += nBytesRD;
        bytesToReceive -= nBytesRD;
    }
    
    return count;
}

int tcp_socket_create(char* ip, int port)
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);

    int flag = 1;
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) == -1)
        return -1;

    if(sfd < 0)
        return sfd;

    struct sockaddr_in address;

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    //address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(port);

    int res = bind(sfd, (struct sockaddr*)&address, sizeof(address));
    if(res < 0)
        return res;

    res = listen(sfd, 5);
    if(res < 0)
        return res;

    return sfd;
}

int tcp_socket_accept(int socketFd)
{
    struct sockaddr_in client;
    socklen_t length = sizeof(client);
    int clifd = accept(socketFd, (struct sockaddr*)&client, &length);

    return clifd;
}

int tcp_socket_connect(char* ip, int port)
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(sfd < 0 )
        return sfd;

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    //address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(port);
    
    if(connect(sfd, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        close(sfd);
        return -1;
    }
        
    return sfd;
}

void fatal(char* msg)
{
    printf("--ERROR--\n");
    printf("%s\n%s\n", msg, strerror(errno));
    printf("---------\n");
    exit(-1);
}
