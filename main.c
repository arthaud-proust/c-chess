#include <stdio.h>
#include <stdbool.h>
#include "core.h"

const char *pieceIcon(const Piece piece) {
    switch (piece) {
        case WHITE_KING:
            return "♔";
        case WHITE_QUEEN:
            return "♕";
        case WHITE_BISHOP:
            return "♗";
        case WHITE_ROCK:
            return "♖";
        case WHITE_KNIGHT:
            return "♘";
        case WHITE_PAWN:
            return "♙";
        case BLACK_KING:
            return "♚";
        case BLACK_QUEEN:
            return "♛";
        case BLACK_BISHOP:
            return "♝";
        case BLACK_ROCK:
            return "♜";
        case BLACK_KNIGHT:
            return "♞";
        case BLACK_PAWN:
            return "♟";
        case EMPTY:
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

void setupBoard(Piece board[COLS][ROWS]) {
    for (int col = 0; col < COLS; col++) {
        for (int row = 0; row < ROWS; row++) {
            board[row][col] = EMPTY;
        }
    }

    board[0][0] = WHITE_ROCK;
    board[1][0] = WHITE_KNIGHT;
    board[2][0] = WHITE_BISHOP;
    board[4][0] = WHITE_QUEEN;
    board[3][0] = WHITE_KING;
    board[5][0] = WHITE_BISHOP;
    board[6][0] = WHITE_KNIGHT;
    board[7][0] = WHITE_ROCK;
    for (int row = 0; row < ROWS; row++) {
        board[row][1] = WHITE_PAWN;
    }

    board[0][7] = BLACK_ROCK;
    board[1][7] = BLACK_KNIGHT;
    board[2][7] = BLACK_BISHOP;
    board[4][7] = BLACK_QUEEN;
    board[3][7] = BLACK_KING;
    board[5][7] = BLACK_BISHOP;
    board[6][7] = BLACK_KNIGHT;
    board[7][7] = BLACK_ROCK;
    for (int row = 0; row < ROWS; row++) {
        board[row][6] = BLACK_PAWN;
    }
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
    setupBoard(board);

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
