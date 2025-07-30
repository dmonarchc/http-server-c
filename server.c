#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
  #pragma comment(lib, "ws2_32.lib")
#endif

struct Server server_Constructor(int domain, int port, int service, int protocol, int backlog,
                                 unsigned long ip_interface, void (*launch)(struct Server *server)) {
    struct Server server;

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed: %d\n", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
#endif

    server.domain = domain;
    server.service = service;
    server.port = port;
    server.protocol = protocol;
    server.backlog = backlog;
    server.ip_interface = ip_interface;

    server.address.sin_family = domain;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(ip_interface);

    server.socket = socket(domain, service, protocol);
#ifdef _WIN32
    if (server.socket == INVALID_SOCKET) {
        fprintf(stderr, "Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        exit(EXIT_FAILURE);
    }
#else
    if (server.socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
#endif

    if (bind(server.socket, (struct sockaddr*)&server.address, sizeof(server.address)) < 0) {
#ifdef _WIN32
        fprintf(stderr, "Bind failed: %d\n", WSAGetLastError());
        CLOSESOCKET(server.socket);
        WSACleanup();
#else
        perror("Bind failed");
        CLOSESOCKET(server.socket);
#endif
        exit(EXIT_FAILURE);
    }

    if (listen(server.socket, backlog) < 0) {
#ifdef _WIN32
        fprintf(stderr, "Listen failed: %d\n", WSAGetLastError());
        CLOSESOCKET(server.socket);
        WSACleanup();
#else
        perror("Listen failed");
        CLOSESOCKET(server.socket);
#endif
        exit(EXIT_FAILURE);
    }

    server.launch = launch;
    return server;
}

void launch(struct Server *server) {
    char buffer[BUFFER_SIZE];

    while (1) {
        printf("=== WAITING FOR CONNECTION ===\n");
        socklen_t addrlen = sizeof(server->address);
        socket_t new_socket = accept(server->socket, (struct sockaddr*)&server->address, &addrlen);

#ifdef _WIN32
        if (new_socket == INVALID_SOCKET) {
            fprintf(stderr, "Accept failed: %d\n", WSAGetLastError());
            continue;
        }
#else
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }
#endif

        int bytesRead;
#ifdef _WIN32
        bytesRead = recv(new_socket, buffer, BUFFER_SIZE - 1, 0);
#else
        bytesRead = read(new_socket, buffer, BUFFER_SIZE - 1);
#endif

        if (bytesRead >= 0) {
            buffer[bytesRead] = '\0';
            puts(buffer);
        } else {
#ifdef _WIN32
            fprintf(stderr, "Error reading buffer: %d\n", WSAGetLastError());
#else
            perror("Error reading buffer");
#endif
        }

        const char *response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n\r\n"
            "<!DOCTYPE html>\r\n"
            "<html>\r\n"
            "<head><title>Testing Basic HTTP-SERVER</title></head>\r\n"
            "<body>Hello, Visitor!</body>\r\n"
            "</html>\r\n";

#ifdef _WIN32
        send(new_socket, response, (int)strlen(response), 0);
#else
        write(new_socket, response, strlen(response));
#endif

        CLOSESOCKET(new_socket);
    }

#ifdef _WIN32
    WSACleanup();
#endif
}