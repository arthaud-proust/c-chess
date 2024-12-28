#include "core.h"
#include <stdbool.h>
#include <stdlib.h>

const int ROWS = 8;
const int COLS = 8;

const int ASCII_LOWER_A = 97;
const int ASCII_ONE = 49;

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
        if (pieceAtDestination) {
            return areSamePositions(destination, atLeftOf(atTopOf(origin, 1), 1))
                   || areSamePositions(destination, atRightOf(atTopOf(origin, 1), 1));
        }

        if (
            origin.row == 1
            && areSamePositions(destination, atTopOf(origin, 2))
        ) {
            return true;
        }
        return areSamePositions(destination, atTopOf(origin, 1));
    }

    if (pieceAtOrigin == BLACK_PAWN) {
        if (pieceAtDestination) {
            return areSamePositions(destination, atLeftOf(atBottomOf(origin, 1), 1))
                   || areSamePositions(destination, atRightOf(atBottomOf(origin, 1), 1));
        }

        if (
            origin.row == 6
            && areSamePositions(destination, atBottomOf(origin, 2))
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
