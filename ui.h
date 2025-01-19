#ifndef UI_H
#define UI_H
#include "core.h"

void renderBoard(Piece board[COLS][ROWS]);

void displayCheckmatedMessage(Color currentPlayer);

void displayStalematedMessage(Color currentPlayer);

GameSnapshot handleCurrentPlayerTurn(GameSnapshot *gameSnapshot);

#endif //UI_H
