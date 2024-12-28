#include "core.h"

#include <iso646.h>
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
        case WK:
        case WQ:
        case WB:
        case WR:
        case WN:
        case WP:
            return WHITE;
        case BK:
        case BQ:
        case BB:
        case BR:
        case BN:
        case BP:
            return BLACK;
        case __:
            return NONE;
    }
    return NONE;
}


void moveTo(Piece board[COLS][ROWS], const Position origin, const Position destination) {
    board[destination.col][destination.row] = board[origin.col][origin.row];
    board[origin.col][origin.row] = __;
}

Piece pieceAtColRow(Piece board[COLS][ROWS], const int col, const int row) {
    return board[col][row];
}

Piece pieceAt(Piece board[COLS][ROWS], const Position position) {
    return pieceAtColRow(board, position.col, position.row);
}

bool emptyAtColRow(Piece board[COLS][ROWS], const int col, const int row) {
    return pieceAtColRow(board, col, row) == __;
}

bool emptyAt(Piece board[COLS][ROWS], const Position position) {
    return pieceAt(board, position) == __;
}

bool isColumnEmptyBetween(Piece board[COLS][ROWS], const Position start, const Position end) {
    if (start.col != end.col) {
        return false;
    }

    const int rowStart = start.row <= end.row ? start.row : end.row;
    const int rowEnd = start.row <= end.row ? end.row : start.row;

    for (int row = rowStart + 1; row < rowEnd; row++) {
        if (pieceAtColRow(board, start.col, row)) {
            return false;
        }
    }

    return true;
}

bool isRowEmptyBetween(Piece board[COLS][ROWS], const Position start, const Position end) {
    if (start.row != end.row) {
        return false;
    }

    const int colStart = start.col <= end.col ? start.col : end.col;
    const int colEnd = start.col <= end.col ? end.col : start.col;

    for (int col = colStart + 1; col < colEnd; col++) {
        if (pieceAtColRow(board, col, start.row)) {
            return false;
        }
    }

    return true;
}

bool isDiagonalEmptyBetween(Piece board[COLS][ROWS], const Position start, const Position end) {
    if (rowsBetween(start, end) != colsBetween(start, end)) {
        return false;
    }

    const int colStart = start.col <= end.col ? start.col : end.col;
    const int colEnd = start.col <= end.col ? end.col : start.col;

    const int rowStart = start.row <= end.row ? start.row : end.row;
    const int rowEnd = start.row <= end.row ? end.row : start.row;

    for (int col = colStart + 1; col < colEnd; col++) {
        for (int row = rowStart + 1; row < rowEnd; row++) {
            if (pieceAtColRow(board, col, row)) {
                return false;
            }
        }
    }

    return true;
}

bool canMovePieceTo(Piece board[COLS][ROWS], const Color currentPlayer, const Position origin, const Position destination) {
    const Piece pieceAtOrigin = pieceAt(board, origin);
    const Color pieceColorAtOrigin = pieceColor(pieceAtOrigin);
    const Piece pieceAtDestination = pieceAt(board, destination);
    const Color pieceColorAtDestination = pieceColor(pieceAtDestination);

    if (destination.col < 0 || COLS <= destination.col || destination.row < 0 || ROWS <= destination.row) {
        return false;
    }

    if (!pieceAtOrigin) {
        return false;
    }

    if (pieceColorAtOrigin != currentPlayer) {
        return false;
    }

    if (pieceAtDestination && pieceColorAtDestination == currentPlayer) {
        return false;
    }

    if (pieceAtOrigin == WP) {
        if (pieceAtDestination) {
            return areSamePositions(destination, atLeftOf(atTopOf(origin, 1), 1))
                   || areSamePositions(destination, atRightOf(atTopOf(origin, 1), 1));
        }

        if (
            origin.row == 1
            && areSamePositions(destination, atTopOf(origin, 2))
            && isColumnEmptyBetween(board, origin, destination)
        ) {
            return true;
        }
        return areSamePositions(destination, atTopOf(origin, 1));
    }

    if (pieceAtOrigin == BP) {
        if (pieceAtDestination) {
            return areSamePositions(destination, atLeftOf(atBottomOf(origin, 1), 1))
                   || areSamePositions(destination, atRightOf(atBottomOf(origin, 1), 1));
        }

        if (
            origin.row == 6
            && areSamePositions(destination, atBottomOf(origin, 2))
            && isColumnEmptyBetween(board, origin, destination)
        ) {
            return true;
        }
        return areSamePositions(destination, atBottomOf(origin, 1));
    }

    if (pieceAtOrigin == WN || pieceAtOrigin == BN) {
        return (rowsBetween(origin, destination) == 2 && colsBetween(origin, destination) == 1)
               || (rowsBetween(origin, destination) == 1 && colsBetween(origin, destination) == 2);
    }

    if (pieceAtOrigin == WK || pieceAtOrigin == BK) {
        return rowsBetween(origin, destination) <= 1 && colsBetween(origin, destination) <= 1;
    }

    if (pieceAtOrigin == WR || pieceAtOrigin == BR) {
        return isRowEmptyBetween(board, origin, destination) || isColumnEmptyBetween(board, origin, destination);
    }

    if (pieceAtOrigin == WB || pieceAtOrigin == BB) {
        return isDiagonalEmptyBetween(board, origin, destination);
    }

    return false;
}

void constructBoard(Piece board[COLS][ROWS]) {
    for (int col = 0; col < COLS; col++) {
        for (int row = 0; row < ROWS; row++) {
            board[row][col] = __;
        }
    }
}

void fillBoardWithInitialPieces(Piece board[COLS][ROWS]) {
    constructBoard(board);

    board[0][0] = WR;
    board[1][0] = WN;
    board[2][0] = WB;
    board[4][0] = WQ;
    board[3][0] = WK;
    board[5][0] = WB;
    board[6][0] = WN;
    board[7][0] = WR;
    for (int row = 0; row < ROWS; row++) {
        board[row][1] = WP;
    }

    board[0][7] = BR;
    board[1][7] = BN;
    board[2][7] = BB;
    board[4][7] = BQ;
    board[3][7] = BK;
    board[5][7] = BB;
    board[6][7] = BN;
    board[7][7] = BR;
    for (int row = 0; row < ROWS; row++) {
        board[row][6] = BP;
    }
}
