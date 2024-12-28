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

void renderBoard(Piece board[COLS][ROWS]) {
    for (int row = ROWS - 1; row >= 0; row--) {
        printf("\n%d", row + 1);
        for (int col = 0; col < COLS; col++) {
            printf("   %s", pieceIcon(board[col][row]));
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

int main(void) {
    Color currentPlayer = WHITE;

    Piece board[COLS][ROWS];
    fillBoardWithInitialPieces(board);

    while (true) {
        renderBoard(board);

        Position origin;
        Position destination;

        bool isInvalid = true;
        do {
            char originStr[3];
            char destinationStr[3];

            printf("\n\nIt's %s's turn", currentPlayer == WHITE ? "White" : "Black");
            printf("\nWhat piece do you move (in algebraic notation)? ");
            scanf("%2s", originStr);
            printf("\nWhere do you move it ? ");
            scanf("%2s", destinationStr);

            origin = positionFromStr(originStr);
            destination = positionFromStr(destinationStr);

            if (canMovePieceTo(board, currentPlayer, origin, destination)) {
                isInvalid = false;
            } else {
                printf("\n%s -> %s is invalid! Please try again.", originStr, destinationStr);
            }
        } while (isInvalid);

        moveTo(board, origin, destination);

        currentPlayer = currentPlayer == WHITE ? BLACK : WHITE;
    }
    return 0;
}
