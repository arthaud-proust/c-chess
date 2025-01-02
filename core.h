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
    BR, // Black Rook
    BN, // Black Knight
    BP, // Black Pawn
} Piece;

extern const int ROWS;
extern const int COLS;

extern const int ASCII_LOWER_A;
extern const int ASCII_ONE;

const int WHITE_PAWN_ROW_PROMOTION;
const int BLACK_PAWN_ROW_PROMOTION;

typedef struct {
    int col;
    int row;
} Position;

typedef struct {
    Piece board[8][8];
    Color currentPlayer;
    bool hasWhiteLostCastling;
    bool hasBlackLostCastling;
} GameSnapshot;

typedef struct {
    GameSnapshot gameSnapshot;
    bool success;
} ActionResult;

typedef struct {
    Position kingOrigin;
    Position kingDestination;
    Position rookOrigin;
    Position rookDestination;
} CastlingPositions;

const CastlingPositions WHITE_CASTLING_KING_SIDE;

const CastlingPositions WHITE_CASTLING_QUEEN_SIDE;

const CastlingPositions BLACK_CASTLING_KING_SIDE;

const CastlingPositions BLACK_CASTLING_QUEEN_SIDE;

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

GameSnapshot appliedMove(const GameSnapshot *gameSnapshot, Position origin, Position destination);

Piece pieceAtColRow(Piece board[COLS][ROWS], int col, int row);

Piece pieceAt(Piece board[COLS][ROWS], Position position);

Position positionOfPiece(Piece board[COLS][ROWS], Piece piece);

bool isEmptyAtColRow(Piece board[COLS][ROWS], int col, int row);

bool isEmptyAt(Piece board[COLS][ROWS], Position position);

bool isColumnEmptyBetween(Piece board[COLS][ROWS], Position start, Position end);

bool isRowEmptyBetween(Piece board[COLS][ROWS], Position start, Position end);

bool isDiagonalEmptyBetween(Piece board[COLS][ROWS], Position start, Position end);

bool isPositionOnBoard(Position position);

bool isMoveValid(const GameSnapshot *gameSnapshot, Position origin, Position destination);

bool isPieceThreatened(const GameSnapshot *gameSnapshot, Position piece);

bool isPlayerInCheck(GameSnapshot *gameSnapshot, Color player);

bool canPlay(GameSnapshot *gameSnapshot, Position origin, Position destination);

bool canPromote(GameSnapshot *gameSnapshot, Position origin);

bool canPromoteTo(GameSnapshot *gameSnapshot, Position origin, Piece promotion);

ActionResult play(GameSnapshot *gameSnapshot, Position origin, Position destination);

ActionResult promoteTo(GameSnapshot *gameSnapshot, Position origin, Piece promotion);

void constructBoard(Piece board[COLS][ROWS]);

void fillBoardWithInitialPieces(Piece board[COLS][ROWS]);

GameSnapshot initialGameSnapshot();

#endif //CORE_H
