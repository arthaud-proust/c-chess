#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>

#include "core.h"
#include "socket.h"
#include "ui.h"

void handleGame(SocketId socket, Color self);

void setupLocal();

void setupServer();

void setupClient();

void stop();

void handleStop(int signal);

void bindSignalAction();

SocketId globalClientSocket;
SocketId globalServerSocket;

int main(void) {
    fflush(stdin);
    bindSignalAction();

    printf("Welcome on Chess.local!\n");
    int action = 0;
    do {
        printf("- (0): 2 players on same computer\n");
        printf("- (1): Host a game\n");
        printf("- (2): Join a game\n");
        printf("> ");
        scanf("%d", &action);
    } while (action != 0 && action != 1 && action != 2);

    switch (action) {
        case 0:
            setupLocal();
            break;
        case 1:
            setupServer();
            break;
        case 2:
            setupClient();
            break;
        default:
            break;
    }

    stop();
}

void setupLocal() {
    GameSnapshot gameSnapshot = initialGameSnapshot();

    while (true) {
        renderBoard(gameSnapshot.board);

        if (isCurrentPlayerCheckmated(&gameSnapshot)) {
            displayCheckmatedMessage(gameSnapshot.currentPlayer);
            break;
        }

        if (isCurrentPlayerStalemated(&gameSnapshot)) {
            displayStalematedMessage(gameSnapshot.currentPlayer);
            break;
        }

        gameSnapshot = handleCurrentPlayerTurn(&gameSnapshot);
    }
}

void setupServer() {
    globalServerSocket = createServerSocket();

    printf("Waiting for client connection...\n");

    globalClientSocket = waitForClientConnection(globalServerSocket);

    handleGame(globalClientSocket, WHITE);
}

void setupClient() {
    printf("What is host ip ?\n> ");
    char hostIp[255];
    fflush(stdin);
    fgets(hostIp, sizeof(hostIp), stdin);

    globalClientSocket = connectToHost(hostIp);

    handleGame(globalClientSocket, BLACK);
}

void handleGame(const SocketId socket, const Color self) {
    printf("You are %s\n", self == WHITE ? "White" : "Black");

    GameSnapshot gameSnapshot = initialGameSnapshot();

    while (true) {
        if (gameSnapshot.currentPlayer == self) {
            renderBoard(gameSnapshot.board);

            if (isCurrentPlayerCheckmated(&gameSnapshot)) {
                displayCheckmatedMessage(gameSnapshot.currentPlayer);
                break;
            }

            if (isCurrentPlayerStalemated(&gameSnapshot)) {
                displayStalematedMessage(gameSnapshot.currentPlayer);
                break;
            }

            gameSnapshot = handleCurrentPlayerTurn(&gameSnapshot);

            if (!sendSnapshotToSocket(socket, &gameSnapshot)) {
                printf("Disconnected.\n");
                break;
            }
        } else {
            renderBoard(gameSnapshot.board);

            printf("Waiting %s to play\n", self == WHITE ? "Black" : "White");

            gameSnapshot = waitForSnapshotFromSocket(socket);
        }
    }
}

void stop() {
    if (globalClientSocket) {
        closeSocket(globalClientSocket);
    }

    if (globalServerSocket) {
        closeSocket(globalServerSocket);
    }
}

void handleStop(int signal) {
    stop();

    abort();
}

void bindSignalAction(void) {
    struct sigaction act;

    // Reset all bits to avoid conflict with old data
    bzero(&act, sizeof(act));

    act.sa_handler = &handleStop;

    sigaction(SIGINT, &act, NULL);
    sigaction(SIGTERM, &act, NULL);
}
