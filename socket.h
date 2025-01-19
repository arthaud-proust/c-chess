#ifndef SOCKET_H
#define SOCKET_H
#include "core.h"

typedef int SocketId;
typedef SocketId ClientSocketId;
typedef SocketId ServerSocketId;
typedef bool MessageSentSuccessfully;

// Host functions
ServerSocketId createServerSocket();

ClientSocketId waitForClientConnection(ServerSocketId server_socket);


// Client functions
ClientSocketId connectToHost(const char *host_ip);

// Both side functions
MessageSentSuccessfully sendSnapshotToSocket(SocketId socket, const GameSnapshot *snapshot);

GameSnapshot waitForSnapshotFromSocket(SocketId socket);

void closeSocket(SocketId socket);

#endif //SOCKET_H
