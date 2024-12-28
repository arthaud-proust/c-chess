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

extern const int ROWS;
extern const int COLS;

extern const int ASCII_LOWER_A;
extern const int ASCII_ONE;

typedef struct {
    int col;
    int row;
} Position;

bool areSamePositions(const Position a, const Position b);

Position withSameRow(const Position position, const int col);

Position withSameCol(const Position position, const int row);

Position atTopOf(const Position position, const int distance);

Position atBottomOf(const Position position, const int distance);

Position atLeftOf(const Position position, const int distance);

Position atRightOf(const Position position, const int distance);

int rowsBetween(const Position a, const Position b);

int colsBetween(const Position a, const Position b);

Color pieceColor(const Piece piece);

void moveTo(Piece board[COLS][ROWS], const Position origin, const Position destination);

Piece pieceAt(Piece board[COLS][ROWS], const Position position);

bool emptyAt(Piece board[COLS][ROWS], const Position position);

bool canMovePieceTo(Piece board[COLS][ROWS], const Color currentPlayer, const Position origin, const Position destination);

#endif //CORE_H
