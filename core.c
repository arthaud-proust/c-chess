#include "core.h"

#include <iso646.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int ROWS = 8;
const int COLS = 8;

const int ASCII_LOWER_A = 97;
const int ASCII_ONE = 49;

const int WHITE_PAWN_ROW_PROMOTION = 7;
const int BLACK_PAWN_ROW_PROMOTION = 0;

const CastlingPositions WHITE_CASTLING_KING_SIDE = {
    {4, 0},
    {6, 0},
    {7, 0},
    {5, 0}
};

const CastlingPositions WHITE_CASTLING_QUEEN_SIDE = {
    {4, 0},
    {2, 0},
    {0, 0},
    {3, 0}
};

const CastlingPositions BLACK_CASTLING_KING_SIDE = {
    {4, 7},
    {6, 7},
    {7, 7},
    {5, 7}
};

const CastlingPositions BLACK_CASTLING_QUEEN_SIDE = {
    {4, 7},
    {2, 7},
    {0, 7},
    {3, 7}
};


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

GameSnapshot appliedMove(const GameSnapshot *gameSnapshot, const Position origin, const Position destination) {
    GameSnapshot nextGameSnapshot = {};

    for (int col = 0; col < COLS; col++) {
        for (int row = 0; row < ROWS; row++) {
            nextGameSnapshot.board[col][row] = gameSnapshot->board[col][row];
        }
    }

    const Piece pieceMoved = pieceAt(gameSnapshot->board, origin);

    moveTo(nextGameSnapshot.board, origin, destination);

    if (
        pieceMoved == WK
        && areSamePositions(origin, WHITE_CASTLING_KING_SIDE.kingOrigin)
        && areSamePositions(destination, WHITE_CASTLING_KING_SIDE.kingDestination)
    ) {
        moveTo(nextGameSnapshot.board, WHITE_CASTLING_KING_SIDE.rookOrigin, WHITE_CASTLING_KING_SIDE.rookDestination);
    }

    if (
        pieceMoved == WK
        && areSamePositions(origin, WHITE_CASTLING_QUEEN_SIDE.kingOrigin)
        && areSamePositions(destination, WHITE_CASTLING_QUEEN_SIDE.kingDestination)
    ) {
        moveTo(nextGameSnapshot.board, WHITE_CASTLING_QUEEN_SIDE.rookOrigin, WHITE_CASTLING_QUEEN_SIDE.rookDestination);
    }

    if (
        pieceMoved == BK
        && areSamePositions(origin, BLACK_CASTLING_KING_SIDE.kingOrigin)
        && areSamePositions(destination, BLACK_CASTLING_KING_SIDE.kingDestination)
    ) {
        moveTo(nextGameSnapshot.board, BLACK_CASTLING_KING_SIDE.rookOrigin, BLACK_CASTLING_KING_SIDE.rookDestination);
    }

    if (
        pieceMoved == BK
        && areSamePositions(origin, BLACK_CASTLING_QUEEN_SIDE.kingOrigin)
        && areSamePositions(destination, BLACK_CASTLING_QUEEN_SIDE.kingDestination)
    ) {
        moveTo(nextGameSnapshot.board, BLACK_CASTLING_QUEEN_SIDE.rookOrigin, BLACK_CASTLING_QUEEN_SIDE.rookDestination);
    }

    nextGameSnapshot.currentPlayer = gameSnapshot->currentPlayer == WHITE ? BLACK : WHITE;
    nextGameSnapshot.hasWhiteLostCastling = gameSnapshot->hasWhiteLostCastling;
    nextGameSnapshot.hasBlackLostCastling = gameSnapshot->hasBlackLostCastling;

    if (pieceMoved == WK || pieceMoved == WR) {
        nextGameSnapshot.hasWhiteLostCastling = true;
    }

    if (pieceMoved == BK || pieceMoved == BR) {
        nextGameSnapshot.hasBlackLostCastling = true;
    }

    return nextGameSnapshot;
}

GameSnapshot appliedPromotion(const GameSnapshot *gameSnapshot, const Position origin, const Piece promotion) {
    GameSnapshot nextGameSnapshot = {};

    for (int col = 0; col < COLS; col++) {
        for (int row = 0; row < ROWS; row++) {
            nextGameSnapshot.board[col][row] = gameSnapshot->board[col][row];
        }
    }

    nextGameSnapshot.board[origin.col][origin.row] = promotion;

    return nextGameSnapshot;
}

Piece pieceAtColRow(Piece board[COLS][ROWS], const int col, const int row) {
    return board[col][row];
}

Piece pieceAt(Piece board[COLS][ROWS], const Position position) {
    return pieceAtColRow(board, position.col, position.row);
}

Position positionOfPiece(Piece board[COLS][ROWS], const Piece piece) {
    Position position = {-1, -1};

    for (int col = 0; col < COLS; col++) {
        for (int row = 0; row < ROWS; row++) {
            if (board[col][row] == piece) {
                position.col = col;
                position.row = row;
            }
        }
    }

    return position;
}

bool isEmptyAtColRow(Piece board[COLS][ROWS], const int col, const int row) {
    return pieceAtColRow(board, col, row) == __;
}

bool isEmptyAt(Piece board[COLS][ROWS], const Position position) {
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
    const int dx = end.col - start.col;
    const int dy = end.row - start.row;

    if (abs(dx) != abs(dy)) {
        return false;
    }

    const int steps = abs(dx); // Nombre de cases à parcourir
    const int xStep = dx / steps; // Direction en x (+1 ou -1)
    const int yStep = dy / steps; // Direction en y (+1 ou -1)

    for (int i = 1; i < steps; i++) {
        const int col = start.col + i * xStep;
        const int row = start.row + i * yStep;
        if (pieceAtColRow(board, col, row)) {
            return false;
        }
    }

    return true;
}

bool isPositionOnBoard(const Position position) {
    return 0 <= position.col && position.col < COLS && 0 <= position.row && position.row < ROWS;
}

bool isMoveValid(const GameSnapshot *gameSnapshot, const Position origin, const Position destination) {
    const Piece pieceAtOrigin = pieceAt(gameSnapshot->board, origin);
    const Color pieceColorAtOrigin = pieceColor(pieceAtOrigin);
    const Piece pieceAtDestination = pieceAt(gameSnapshot->board, destination);
    const Color pieceColorAtDestination = pieceColor(pieceAtDestination);

    if (!isPositionOnBoard(destination)) {
        return false;
    }

    if (!pieceAtOrigin) {
        return false;
    }

    if (pieceAtDestination && pieceColorAtDestination == pieceColorAtOrigin) {
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
            && isColumnEmptyBetween(gameSnapshot->board, origin, destination)
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
            && isColumnEmptyBetween(gameSnapshot->board, origin, destination)
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
        const CastlingPositions *kingSide = gameSnapshot->currentPlayer == WHITE ? &WHITE_CASTLING_KING_SIDE : &BLACK_CASTLING_KING_SIDE;
        const CastlingPositions *queenSide = gameSnapshot->currentPlayer == WHITE ? &WHITE_CASTLING_QUEEN_SIDE : &BLACK_CASTLING_QUEEN_SIDE;
        const bool hasLostCastling = gameSnapshot->currentPlayer == WHITE ? gameSnapshot->hasWhiteLostCastling : gameSnapshot->hasBlackLostCastling;

        if (areSamePositions(origin, kingSide->kingOrigin) && areSamePositions(destination, kingSide->kingDestination)) {
            return !hasLostCastling && isRowEmptyBetween(gameSnapshot->board, kingSide->kingOrigin, kingSide->rookOrigin);
        }

        if (areSamePositions(origin, queenSide->kingOrigin) && areSamePositions(destination, queenSide->kingDestination)) {
            return !hasLostCastling && isRowEmptyBetween(gameSnapshot->board, queenSide->kingOrigin, queenSide->rookOrigin);
        }

        return rowsBetween(origin, destination) <= 1 && colsBetween(origin, destination) <= 1;
    }

    if (pieceAtOrigin == WR || pieceAtOrigin == BR) {
        return isRowEmptyBetween(gameSnapshot->board, origin, destination)
               || isColumnEmptyBetween(gameSnapshot->board, origin, destination);
    }

    if (pieceAtOrigin == WB || pieceAtOrigin == BB) {
        return isDiagonalEmptyBetween(gameSnapshot->board, origin, destination);
    }

    if (pieceAtOrigin == WQ || pieceAtOrigin == BQ) {
        return isRowEmptyBetween(gameSnapshot->board, origin, destination)
               || isColumnEmptyBetween(gameSnapshot->board, origin, destination)
               || isDiagonalEmptyBetween(gameSnapshot->board, origin, destination);
    }

    return false;
}

bool isPieceThreatened(const GameSnapshot *gameSnapshot, const Position piece) {
    if (!isPositionOnBoard(piece)) {
        return false;
    }

    Position piecePosition = {-1, -1};
    for (int col = 0; col < COLS; col++) {
        for (int row = 0; row < ROWS; row++) {
            piecePosition.col = col;
            piecePosition.row = row;

            if (areSamePositions(piece, piecePosition)) {
                continue;
            }

            if (isMoveValid(gameSnapshot, piecePosition, piece)) {
                return true;
            }
        }
    }

    return false;
}

bool isPlayerInCheck(GameSnapshot *gameSnapshot, const Color player) {
    const Position kingPosition = positionOfPiece(gameSnapshot->board, player == WHITE ? WK : BK);

    return isPieceThreatened(gameSnapshot, kingPosition);
}

bool canPlay(GameSnapshot *gameSnapshot, const Position origin, const Position destination) {
    const Color pieceColorAtOrigin = pieceColor(pieceAt(gameSnapshot->board, origin));

    if (pieceColorAtOrigin != gameSnapshot->currentPlayer) {
        return false;
    }

    if (!isMoveValid(gameSnapshot, origin, destination)) {
        return false;
    }

    GameSnapshot nextSnapshot = appliedMove(gameSnapshot, origin, destination);

    return !isPlayerInCheck(&nextSnapshot, gameSnapshot->currentPlayer);
}

bool canPromote(GameSnapshot *gameSnapshot, const Position origin) {
    const Piece piece = pieceAt(gameSnapshot->board, origin);
    const Color color = pieceColor(piece);

    if (color != gameSnapshot->currentPlayer) {
        return false;
    }

    if (piece == WP) {
        return origin.row == WHITE_PAWN_ROW_PROMOTION;
    }

    if (piece == BP) {
        return origin.row == BLACK_PAWN_ROW_PROMOTION;
    }

    return false;
}

bool canPromoteTo(GameSnapshot *gameSnapshot, const Position origin, const Piece promotion) {
    return canPromote(gameSnapshot, origin)
           && pieceColor(promotion) == gameSnapshot->currentPlayer
           && (
               promotion == WQ
               || promotion == WB
               || promotion == WR
               || promotion == WN
               || promotion == BQ
               || promotion == BB
               || promotion == BR
               || promotion == BN
           );
}


ActionResult play(GameSnapshot *gameSnapshot, const Position origin, const Position destination) {
    const ActionResult result = {
        appliedMove(gameSnapshot, origin, destination),
        canPlay(gameSnapshot, origin, destination)
    };

    return result;
}

ActionResult promoteTo(GameSnapshot *gameSnapshot, const Position origin, const Piece promotion) {
    const ActionResult result = {
        appliedPromotion(gameSnapshot, origin, promotion),
        canPromote(gameSnapshot, origin)
    };

    return result;
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
