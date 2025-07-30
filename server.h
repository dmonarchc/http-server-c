#ifndef SERVER_H
#define SERVER_H

#ifdef _WIN32
  #include <winsock2.h>
  #include <ws2tcpip.h>
  typedef SOCKET socket_t;
  #define CLOSESOCKET(s) closesocket(s)
#else
  #include <netinet/in.h>
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <unistd.h>
  #include <string.h>
  #include <errno.h>
  typedef int socket_t;
  #define CLOSESOCKET(s) close(s)
#endif

#define BUFFER_SIZE 16000

struct Server {
    int domain;
    int port;
    int service;
    int protocol;
    int backlog;
    unsigned long ip_interface;

    socket_t socket;
    struct sockaddr_in address;

    void (*launch)(struct Server *server);
};

struct Server server_Constructor(int domain, int port, int service, int protocol, int backlog,
                                 unsigned long ip_interface, void (*launch)(struct Server *server));
void launch(struct Server *server);

#endif
