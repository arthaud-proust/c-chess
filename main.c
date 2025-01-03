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
        printf("\n%d", row + 1);
        for (int col = 0; col < COLS; col++) {
            printf("   %s", caseIcon(board, col, row));
        }
    }
    printf("\n    a   b   c   d   e   f   g   h");
}

Position positionFromStr(const char str[2]) {
    const Position position = {
        (int) str[0] - ASCII_LOWER_A,
        (int) str[1] - ASCII_ONE
    };

    return position;
}

Piece askPromotion(GameSnapshot *gameSnapshot, const Position destination) {
    Piece piece;
    do {
        printf("\nHow do you promote your pawn? (Q/R/B/N) ");
        printf("\nQ: Queen ");
        printf("\nR: Rook ");
        printf("\nB: Bishop ");
        printf("\nN: Knight ");
        printf("\nYou choice: ");

        char pieceChar;
        scanf("%1s", &pieceChar);
        piece = pieceFromChar(gameSnapshot->currentPlayer, pieceChar);
    } while (canPromoteTo(gameSnapshot, destination, piece));

    return piece;
}

int main(void) {
    GameSnapshot gameSnapshot = initialGameSnapshot();

    while (true) {
        renderBoard(gameSnapshot.board);

        if (isCurrentPlayerCheckmated(&gameSnapshot)) {
            printf(
                "\n\n%s player is checkmated!\n%s won",
                gameSnapshot.currentPlayer == WHITE ? "White" : "Black",
                gameSnapshot.currentPlayer == WHITE ? "Black" : "White"
            );
            return 0;
        }

        if (isCurrentPlayerStalemated(&gameSnapshot)) {
            printf("\n\n%s player is stalemated!\nNobody won", gameSnapshot.currentPlayer == WHITE ? "White" : "Black");
            return 0;
        }

        bool isInvalid = true;
        do {
            char originStr[3];
            char destinationStr[3];

            printf("\n\nIt's %s's turn", gameSnapshot.currentPlayer == WHITE ? "White" : "Black");

            if (isPlayerInCheck(&gameSnapshot, gameSnapshot.currentPlayer)) {
                printf("\nYour are in check");
            }

            printf("\nWhat piece do you move (in algebraic notation)?\n> ");
            scanf("%2s", originStr);
            printf("\nWhere do you move it ?\n> ");
            scanf("%2s", destinationStr);

            const Position origin = positionFromStr(originStr);
            const Position destination = positionFromStr(destinationStr);

            const ActionResult playResult = play(&gameSnapshot, origin, destination);

            if (playResult.success) {
                isInvalid = false;
                gameSnapshot = playResult.gameSnapshot;

                if (canPromote(&gameSnapshot, destination)) {
                    const Piece promotion = askPromotion(&gameSnapshot, destination);
                    const ActionResult promoteResult = promoteTo(&gameSnapshot, destination, promotion);

                    if (promoteResult.success) {
                        gameSnapshot = playResult.gameSnapshot;
                    } else {
                        printf("\nError");
                        return 1;
                    }
                }
            } else {
                printf("\n%s -> %s is invalid! Please try again.", originStr, destinationStr);
            }
        } while (isInvalid);
    }
}
