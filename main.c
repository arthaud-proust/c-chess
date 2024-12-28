#include <iso646.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Play to chess in terminal

// Board definition :
// Piece board[int col][int row]
//
// Relation with algebraic notation
// row (number) = row-1
// column (letter) = col-1
//
// Examples:
// A = a1 = board[0][0]
// B = b3 = board[1][2]
// C = e8 = board[4][7]
// D = h8 = board[7][7]
// 8 - - - - C - - D
// 7 - - - - - - - -
// 6 - - - - - - - -
// 5 - - - - - - - -
// 4 - - - - - - - -
// 3 - B - - - - - -
// 2 - - - - - - - -
// 1 A - - - - - - -
//   a b c d e f g h

typedef enum {
    NONE = 0,
    WHITE,
    BLACK,
} Color;

typedef enum {
    EMPTY = 0,
    WHITE_KING,
    WHITE_QUEEN,
    WHITE_BISHOP,
    WHITE_ROCK,
    WHITE_KNIGHT,
    WHITE_PAWN,
    BLACK_KING,
    BLACK_QUEEN,
    BLACK_BISHOP,
    BLACK_ROCK,
    BLACK_KNIGHT,
    BLACK_PAWN,
} Piece;

const int ROWS = 8;
const int COLS = 8;

const int ASCII_LOWER_A = 97;
const int ASCII_ONE = 49;

typedef struct {
    int col;
    int row;
} Position;

bool areSamePositions(const Position a, const Position b) {
    return a.col == b.col && a.row == b.row;
}

Position withSameRow(const Position position, const int col) {
    const Position newPosition = {
        col,
        position.row
    };

    return newPosition;
}

Position withSameCol(const Position position, const int row) {
    const Position newPosition = {
        position.col,
        row
    };

    return newPosition;
}

Position atTopOf(const Position position, const int distance) {
    const Position newPosition = {
        position.col,
        position.row + distance
    };

    return newPosition;
}

Position atBottomOf(const Position position, const int distance) {
    const Position newPosition = {
        position.col,
        position.row - distance
    };

    return newPosition;
}

Position atLeftOf(const Position position, const int distance) {
    const Position newPosition = {
        position.col - distance,
        position.row
    };

    return newPosition;
}

Position atRightOf(const Position position, const int distance) {
    const Position newPosition = {
        position.col + distance,
        position.row
    };

    return newPosition;
}

int rowsBetween(const Position a, const Position b) {
    return abs(a.row - b.row);
}

int colsBetween(const Position a, const Position b) {
    return abs(a.col - b.col);
}

Color pieceColor(const Piece piece) {
    switch (piece) {
        case WHITE_KING:
        case WHITE_QUEEN:
        case WHITE_BISHOP:
        case WHITE_ROCK:
        case WHITE_KNIGHT:
        case WHITE_PAWN:
            return WHITE;
        case BLACK_KING:
        case BLACK_QUEEN:
        case BLACK_BISHOP:
        case BLACK_ROCK:
        case BLACK_KNIGHT:
        case BLACK_PAWN:
            return BLACK;
        case EMPTY:
            return NONE;
    }
    return NONE;
}

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

void moveTo(Piece board[COLS][ROWS], const Position origin, const Position destination) {
    board[destination.col][destination.row] = board[origin.col][origin.row];
    board[origin.col][origin.row] = EMPTY;
}

Piece pieceAt(Piece board[COLS][ROWS], const Position position) {
    return board[position.col][position.row];
}

bool emptyAt(Piece board[COLS][ROWS], const Position position) {
    return pieceAt(board, position) == EMPTY;
}


bool canMovePieceTo(Piece board[COLS][ROWS], const Color currentPlayer, const Position origin, const Position destination) {
    const Piece pieceAtOrigin = pieceAt(board, origin);
    const Color pieceColorAtOrigin = pieceColor(pieceAtOrigin);
    const Piece pieceAtDestination = pieceAt(board, destination);
    const Color pieceColorAtDestination = pieceColor(pieceAtDestination);

    if (!pieceAtOrigin) {
        return false;
    }

    if (pieceColorAtOrigin != currentPlayer) {
        return false;
    }

    if (pieceAtDestination && pieceColorAtOrigin == pieceColorAtDestination) {
        return false;
    }

    if (pieceAtOrigin == WHITE_PAWN) {
        if (
            origin.row == 1
            && areSamePositions(destination, atTopOf(origin, 2))
        ) {
            return true;
        }
        return areSamePositions(destination, atTopOf(origin, 1));
    }

    if (pieceAtOrigin == BLACK_PAWN) {
        if (
            origin.row == 7
            && areSamePositions(destination, atTopOf(origin, 2))
        ) {
            return true;
        }
        return areSamePositions(destination, atBottomOf(origin, 1));
    }

    if (pieceAtOrigin == BLACK_KNIGHT || pieceAtOrigin == WHITE_KNIGHT) {
        return (rowsBetween(origin, destination) == 2 && colsBetween(origin, destination) == 1)
               || (rowsBetween(origin, destination) == 1 && colsBetween(origin, destination) == 2);
    }

    if (pieceAtOrigin == BLACK_KING || pieceAtOrigin == WHITE_KING) {
        return rowsBetween(origin, destination) <= 1 && colsBetween(origin, destination) <= 1;
    }

    return false;
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
    Piece board[COLS][ROWS] = {
        {WHITE_ROCK, WHITE_PAWN, EMPTY, EMPTY, EMPTY, EMPTY, BLACK_PAWN, BLACK_ROCK},
        {WHITE_KNIGHT, WHITE_PAWN, EMPTY, EMPTY, EMPTY, EMPTY, BLACK_PAWN, BLACK_KNIGHT},
        {WHITE_BISHOP, WHITE_PAWN, EMPTY, EMPTY, EMPTY, EMPTY, BLACK_PAWN, BLACK_BISHOP},
        {WHITE_QUEEN, WHITE_PAWN, EMPTY, EMPTY, EMPTY, EMPTY, BLACK_PAWN, BLACK_QUEEN},
        {WHITE_KING, WHITE_PAWN, EMPTY, EMPTY, EMPTY, EMPTY, BLACK_PAWN, BLACK_KING},
        {WHITE_BISHOP, WHITE_PAWN, EMPTY, EMPTY, EMPTY, EMPTY, BLACK_PAWN, BLACK_BISHOP},
        {WHITE_KNIGHT, WHITE_PAWN, EMPTY, EMPTY, EMPTY, EMPTY, BLACK_PAWN, BLACK_KNIGHT},
        {WHITE_ROCK, WHITE_PAWN, EMPTY, EMPTY, EMPTY, EMPTY, BLACK_PAWN, BLACK_ROCK},
    };

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
