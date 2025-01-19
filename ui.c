#include "ui.h"

#include <stdio.h>
#include <stdbool.h>
#include "core.h"

const char *pieceIcon(const Piece piece) {
    switch (piece) {
        case WK:
            return "♔";
        case WQ:
            return "♕";
        case WB:
            return "♗";
        case WR:
            return "♖";
        case WN:
            return "♘";
        case WP:
            return "♙";
        case BK:
            return "♚";
        case BQ:
            return "♛";
        case BB:
            return "♝";
        case BR:
            return "♜";
        case BN:
            return "♞";
        case BP:
            return "♟";
        case __:
            return " ";
    }
    return " ";
}

bool isOdd(const int x) {
    return x % 2;
}

const char *caseIcon(Piece board[COLS][ROWS], const int col, const int row) {
    if (board[col][row] == __) {
        return (!isOdd(col) && !isOdd(row)) || (isOdd(col) && isOdd(row)) ? "◼" : " ";
    }

    return pieceIcon(board[col][row]);
}

Piece pieceFromChar(const Color color, const char pieceChar) {
    switch (pieceChar) {
        case 'K':
            return color == WHITE ? WK : BK;
        case 'Q':
            return color == WHITE ? WQ : BQ;
        case 'R':
            return color == WHITE ? WR : BR;
        case 'B':
            return color == WHITE ? WB : BB;
        case 'N':
            return color == WHITE ? WN : BN;
        case 'P':
            return color == WHITE ? WP : BP;
        default:
            return __;
    }
}

void renderBoard(Piece board[COLS][ROWS]) {
    for (int row = ROWS - 1; row >= 0; row--) {
        printf("%d", row + 1);
        for (int col = 0; col < COLS; col++) {
            printf("   %s", caseIcon(board, col, row));
        }
        printf("\n");
    }
    printf("    a   b   c   d   e   f   g   h\n");
}

Move moveFromStr(const char str[4]) {
    const Move move = {
        {
            (int) str[0] - ASCII_LOWER_A,
            (int) str[1] - ASCII_ONE
        },
        {
            (int) str[2] - ASCII_LOWER_A,
            (int) str[3] - ASCII_ONE
        },
    };

    return move;
}

Piece askPromotion(GameSnapshot *gameSnapshot, const Position destination) {
    Piece piece;
    do {
        printf("How do you promote your pawn? (Q/R/B/N)\n");
        printf("Q: Queen\n");
        printf("R: Rook\n");
        printf("B: Bishop\n");
        printf("N: Knight\n");
        printf("\n> ");

        char pieceChar;
        scanf("%1s", &pieceChar);
        piece = pieceFromChar(gameSnapshot->currentPlayer, pieceChar);
    } while (canPromoteTo(gameSnapshot, destination, piece));

    return piece;
}

GameSnapshot handlePromotion(GameSnapshot *gameSnapshot, const Move moveDone) {
    if (!canPromote(gameSnapshot, moveDone.destination)) {
        return *gameSnapshot;
    }

    do {
        const Piece promotion = askPromotion(gameSnapshot, moveDone.destination);
        const ActionResult promoteResult = promoteTo(gameSnapshot, moveDone.destination, promotion);

        if (promoteResult.success) {
            return promoteResult.gameSnapshot;
        }

        printf("Impossible to promote this piece.\n");
    } while (true);
}

GameSnapshot handleCurrentPlayerTurn(GameSnapshot *gameSnapshot) {
    do {
        printf("\nIt's %s's turn\n", gameSnapshot->currentPlayer == WHITE ? "White" : "Black");

        char moveStr[4 + 1];
        if (isPlayerInCheck(gameSnapshot, gameSnapshot->currentPlayer)) {
            printf("You are in check\n");
        }

        printf("What do you play ? (e.g: d2d4)\n> ");
        scanf("%4s", moveStr);

        const Move move = moveFromStr(moveStr);

        const ActionResult playResult = play(gameSnapshot, move.origin, move.destination);

        if (playResult.success) {
            return handlePromotion(&playResult.gameSnapshot, move);
        }

        printf("%s is invalid! Please try again.\n", moveStr);
    } while (true);
}

void displayCheckmatedMessage(const Color currentPlayer) {
    printf(
        "\n%s player is checkmated!\n%s won\n",
        currentPlayer == WHITE ? "White" : "Black",
        currentPlayer == WHITE ? "Black" : "White"
    );
}

void displayStalematedMessage(const Color currentPlayer) {
    printf("\n%s player is stalemated!\nNobody won\n", currentPlayer == WHITE ? "White" : "Black");
}
