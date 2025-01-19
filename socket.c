#include "socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

const int PORT = 8080;
const int IP = INADDR_ANY;

// Host functions
ServerSocketId createServerSocket() {
    struct sockaddr_in server_addr;
    const ServerSocketId server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket < 0) {
        perror("Error when creating socket\n");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(IP);
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("Error when binding address\n");
        close(server_socket);
        exit(1);
    }

    if (listen(server_socket, 5) < 0) {
        perror("Error when listening\n");
        close(server_socket);
        exit(1);
    }

    return server_socket;
}

ClientSocketId waitForClientConnection(const ServerSocketId server_socket) {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    const ClientSocketId client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_len);

    if (client_socket < 0) {
        perror("Error when accepting connection\n");
        close(server_socket);
        exit(1);
    }

    return client_socket;
}

// Client functions
ClientSocketId connectToHost(const char *host_ip) {
    struct sockaddr_in server_addr;

    const ClientSocketId client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error when creating socket\n");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // server_addr.sin_addr.s_addr = htonl(IP);
    server_addr.sin_addr.s_addr = inet_addr(host_ip);
    if (server_addr.sin_addr.s_addr == INADDR_NONE) {
        perror("Invalid IP address\n");
        close(client_socket);
        exit(1);
    }


    const socklen_t server_len = sizeof(server_addr);

    if (connect(client_socket, (struct sockaddr *) &server_addr, server_len) < 0) {
        perror("Error during connection\n");
        close(client_socket);
        exit(1);
    }

    return client_socket;
}

// Both side functions
MessageSentSuccessfully sendSnapshotToSocket(const SocketId socket, const GameSnapshot *snapshot) {
    const ssize_t sig = send(socket, snapshot, sizeof(*snapshot), MSG_NOSIGNAL);

    return sig != -1;
}

GameSnapshot waitForSnapshotFromSocket(const SocketId socket) {
    GameSnapshot snapshot;
    read(socket, &snapshot, sizeof(snapshot));

    return snapshot;
}

void closeSocket(const SocketId socket) {
    close(socket);
}
