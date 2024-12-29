#ifndef CORE_H
#define CORE_H

#include <stdbool.h>

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
    WHITE = 2,
    BLACK,
} Color;

typedef enum {
    __ = 0,
    WK = 4, // White King
    WQ, // White Queen
    WB, // White Bishop
    WR, // White Rock
    WN, // White Knight
    WP, // White Pawn
    BK, // Black King
    BQ, // Black Queen
    BB, // Black Bishop
    BR, // Black Rock
    BN, // Black Knight
    BP, // Black Pawn
} Piece;

extern const int ROWS;
extern const int COLS;

extern const int ASCII_LOWER_A;
extern const int ASCII_ONE;

typedef struct {
    int col;
    int row;
} Position;

bool areSamePositions(Position a, Position b);

Position withSameRow(Position position, int col);

Position withSameCol(Position position, int row);

Position atTopOf(Position position, int distance);

Position atBottomOf(Position position, int distance);

Position atLeftOf(Position position, int distance);

Position atRightOf(Position position, int distance);

int rowsBetween(Position a, Position b);

int colsBetween(Position a, Position b);

Color pieceColor(Piece piece);

void moveTo(Piece board[COLS][ROWS], Position origin, Position destination);

Piece pieceAtColRow(Piece board[COLS][ROWS], int col, int row);

Piece pieceAt(Piece board[COLS][ROWS], Position position);

Position positionOfPiece(Piece board[COLS][ROWS], Piece piece);

bool isEmptyAtColRow(Piece board[COLS][ROWS], int col, int row);

bool isEmptyAt(Piece board[COLS][ROWS], Position position);

bool isColumnEmptyBetween(Piece board[COLS][ROWS], Position start, Position end);

bool isRowEmptyBetween(Piece board[COLS][ROWS], Position start, Position end);

bool isDiagonalEmptyBetween(Piece board[COLS][ROWS], Position start, Position end);

bool isPositionOnBoard(Position position);

bool isMoveValid(Piece board[COLS][ROWS], Position origin, Position destination);

bool isKingInCheck(Piece board[COLS][ROWS], Color currentPlayer);

void constructBoard(Piece board[COLS][ROWS]);

void fillBoardWithInitialPieces(Piece board[COLS][ROWS]);

#endif //CORE_H
