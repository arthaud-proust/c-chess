#include "tau/tau.h"
#include "core.h"

TAU_MAIN()

Position positionOfPiece(Piece movesBoard[COLS][ROWS], const Piece piece) {
    Position position = {-1, -1};

    for (int col = 0; col < COLS; col++) {
        for (int row = 0; row < ROWS; row++) {
            if (movesBoard[col][row] == piece) {
                position.col = col;
                position.row = row;
            }
        }
    }

    return position;
}

void ASSERT_VALID_MOVES_MATCH(Piece board[COLS][ROWS], const Color player, const Position pieceToMove, bool validMoves[COLS][ROWS]) {
    REQUIRE_TRUE(pieceToMove.col > -1 && pieceToMove.row > -1, "Piece not found");

    for (int col = 0; col < COLS; col++) {
        for (int row = 0; row < ROWS; row++) {
            const bool expectedCanMove = validMoves[col][row];
            const Position destination = {col, row};
            CHECK_EQ(
                canMovePieceTo(board, player, pieceToMove, destination),
                expectedCanMove,
                "Expected %d:%d->%d:%d to be %s",
                pieceToMove.col,
                pieceToMove.row,
                destination.col,
                destination.row,
                expectedCanMove ? "valid" : "invalid"
            );
        }
    }
}

TEST(isColumnEmptyBetween, return_false_if_not_same_column) {
    Piece board[8][8] = {
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };

    const Position start = {0, 0};
    const Position end = {1, 0};

    CHECK_FALSE(isColumnEmptyBetween(board, start, end));
    CHECK_FALSE(isColumnEmptyBetween(board, end, start));
}

TEST(isColumnEmptyBetween, return_true_if_no_piece_between_start_and_end) {
    Piece board[8][8] = {
        {WP, __, WP, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };

    const Position start = {0, 0};
    const Position end = {0, 2};

    CHECK_TRUE(isColumnEmptyBetween(board, start, end));
    CHECK_TRUE(isColumnEmptyBetween(board, end, start));
}

TEST(isColumnEmptyBetween, return_false_if_piece_between_start_and_end) {
    Piece board[8][8] = {
        {WP, WP, WP, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };

    const Position start = {0, 0};
    const Position end = {0, 2};

    CHECK_FALSE(isColumnEmptyBetween(board, start, end));
    CHECK_FALSE(isColumnEmptyBetween(board, end, start));
}

TEST(isRowEmptyBetween, return_false_if_not_same_row) {
    Piece board[8][8] = {
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };

    const Position start = {0, 0};
    const Position end = {0, 2};

    CHECK_FALSE(isRowEmptyBetween(board, start, end));
    CHECK_FALSE(isRowEmptyBetween(board, end, start));
}

TEST(isRowEmptyBetween, return_true_if_no_piece_between_start_and_end) {
    Piece board[8][8] = {
        {WP, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {WP, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };

    const Position start = {0, 0};
    const Position end = {2, 0};

    CHECK_TRUE(isRowEmptyBetween(board, start, end));
    CHECK_TRUE(isRowEmptyBetween(board, end, start));
}

TEST(isRowEmptyBetween, return_false_if_piece_between_start_and_end) {
    Piece board[8][8] = {
        {WP, __, __, __, __, __, __, __},
        {WP, __, __, __, __, __, __, __},
        {WP, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };

    const Position start = {0, 0};
    const Position end = {2, 0};

    CHECK_FALSE(isRowEmptyBetween(board, start, end));
    CHECK_FALSE(isRowEmptyBetween(board, end, start));
}

TEST(isDiagonalEmptyBetween, return_false_if_not_same_diagonal) {
    Piece board[8][8] = {
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };

    const Position start = {0, 0};
    const Position end = {1, 0};

    CHECK_FALSE(isDiagonalEmptyBetween(board, start, end));
    CHECK_FALSE(isDiagonalEmptyBetween(board, end, start));
}

TEST(isDiagonalEmptyBetween, return_true_if_no_piece_between_start_and_end) {
    Piece board[8][8] = {
        {WP, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, WP, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };

    const Position start = {0, 0};
    const Position end = {2, 2};

    CHECK_TRUE(isDiagonalEmptyBetween(board, start, end));
    CHECK_TRUE(isDiagonalEmptyBetween(board, end, start));
}

TEST(isDiagonalEmptyBetween, return_false_if_piece_between_start_and_end) {
    Piece board[8][8] = {
        {WP, __, __, __, __, __, __, __},
        {__, WP, __, __, __, __, __, __},
        {__, __, WP, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };

    const Position start = {0, 0};
    const Position end = {2, 2};

    CHECK_FALSE(isDiagonalEmptyBetween(board, start, end));
    CHECK_FALSE(isDiagonalEmptyBetween(board, end, start));
}

TEST(all, cannot_move_other_player_piece) {
    Piece board[8][8] = {
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, WP, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };
    const Position pieceToMove = positionOfPiece(board, WP);

    bool validMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_VALID_MOVES_MATCH(board, BLACK, pieceToMove, validMoves);
}

TEST(all, cannot_move_piece_on_another_if_same_colour) {
    Piece board[8][8] = {
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, WP, WP, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };
    const Position pieceToMove = {3, 2};

    bool validMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_VALID_MOVES_MATCH(board, WHITE, pieceToMove, validMoves);
}

TEST(all, cannot_move_piece_out_of_board) {
    Piece board[8][8] = {
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, WP},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };
    const Position pieceToMove = positionOfPiece(board, WP);

    bool validMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };
    ASSERT_VALID_MOVES_MATCH(board, WHITE, pieceToMove, validMoves);

    const Position outOfBoard = {3, 8};
    REQUIRE_EQ(
        canMovePieceTo(board, WHITE, pieceToMove, outOfBoard),
        false
    );
}

TEST(pawn, white_can_move_1_cell_front_when_not_at_start_row) {
    Piece board[8][8] = {
        {__, __, WP, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };
    const Position pieceToMove = positionOfPiece(board, WP);

    bool validMoves[8][8] = {
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_VALID_MOVES_MATCH(board, WHITE, pieceToMove, validMoves);
}

TEST(pawn, white_can_move_1_or_2_cells_front_when_at_start_row) {
    Piece board[8][8] = {
        {__, WP, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };
    const Position pieceToMove = positionOfPiece(board, WP);

    bool validMoves[8][8] = {
        {0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_VALID_MOVES_MATCH(board, WHITE, pieceToMove, validMoves);
}

TEST(pawn, white_cannot_move_2_cells_front_when_piece_in_front_of_it) {
    Piece board[8][8] = {
        {__, WP, BP, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };
    const Position pieceToMove = positionOfPiece(board, WP);

    bool validMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_VALID_MOVES_MATCH(board, WHITE, pieceToMove, validMoves);
}

TEST(pawn, white_can_eat_at_front_left_or_front_right) {
    Piece board[8][8] = {
        {__, __, __, BP, __, __, __, __},
        {__, __, WP, BP, __, __, __, __},
        {__, __, __, BP, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };
    const Position pieceToMove = positionOfPiece(board, WP);

    bool validMoves[8][8] = {
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_VALID_MOVES_MATCH(board, WHITE, pieceToMove, validMoves);
}

TEST(pawn, black_can_move_1_cell_front_when_not_at_start_row) {
    Piece board[8][8] = {
        {__, __, __, __, __, BP, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };
    const Position pieceToMove = positionOfPiece(board, BP);

    bool validMoves[8][8] = {
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_VALID_MOVES_MATCH(board, BLACK, pieceToMove, validMoves);
}

TEST(pawn, black_can_move_1_or_2_cells_front_when_at_start_row) {
    Piece board[8][8] = {
        {__, __, __, __, __, __, BP, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };
    const Position pieceToMove = positionOfPiece(board, BP);

    bool validMoves[8][8] = {
        {0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_VALID_MOVES_MATCH(board, BLACK, pieceToMove, validMoves);
}

TEST(pawn, black_cannot_move_2_cells_front_when_piece_in_front_of_it) {
    Piece board[8][8] = {
        {__, __, __, __, __, WP, BP, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };
    const Position pieceToMove = positionOfPiece(board, BP);

    bool validMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_VALID_MOVES_MATCH(board, BLACK, pieceToMove, validMoves);
}

TEST(pawn, black_can_eat_at_front_left_or_front_right) {
    Piece board[8][8] = {
        {__, __, __, __, WP, __, __, __},
        {__, __, __, __, WP, BP, __, __},
        {__, __, __, __, WP, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };
    const Position pieceToMove = positionOfPiece(board, BP);

    bool validMoves[8][8] = {
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_VALID_MOVES_MATCH(board, BLACK, pieceToMove, validMoves);
}

TEST(knight, can_move_in_l_shape) {
    Piece board[8][8] = {
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, WN, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };
    const Position pieceToMove = positionOfPiece(board, WN);

    bool validMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_VALID_MOVES_MATCH(board, WHITE, pieceToMove, validMoves);
}

TEST(king, can_move_in_any_direction_at_distance_of_1) {
    Piece board[8][8] = {
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, WK, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };
    const Position pieceToMove = positionOfPiece(board, WK);

    bool validMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_VALID_MOVES_MATCH(board, WHITE, pieceToMove, validMoves);
}

TEST(rock, can_move_in_column_or_row_at_any_distance) {
    Piece board[8][8] = {
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, WR, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };
    const Position pieceToMove = positionOfPiece(board, WR);

    bool validMoves[8][8] = {
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {1, 1, 1, 0, 1, 1, 1, 1},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
    };

    ASSERT_VALID_MOVES_MATCH(board, WHITE, pieceToMove, validMoves);
}

TEST(rock, cannot_go_over_pieces) {
    Piece board[8][8] = {
        {__, __, __, __, __, __, __, __},
        {__, __, __, BP, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, BP, __, WR, __, BP, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, BP, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };
    const Position pieceToMove = positionOfPiece(board, WR);

    bool validMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_VALID_MOVES_MATCH(board, WHITE, pieceToMove, validMoves);
}

TEST(bishop, can_move_in_diagonal_at_any_distance) {
    Piece board[8][8] = {
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, WB, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };
    const Position pieceToMove = positionOfPiece(board, WB);

    bool validMoves[8][8] = {
        {1, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
    };

    ASSERT_VALID_MOVES_MATCH(board, WHITE, pieceToMove, validMoves);
}

TEST(bishop, cannot_go_over_pieces) {
    Piece board[8][8] = {
        {__, __, __, __, __, __, __, __},
        {__, BP, __, __, __, BP, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, WB, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, BP, __, __, __, BP, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };
    const Position pieceToMove = positionOfPiece(board, WB);

    bool validMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_VALID_MOVES_MATCH(board, WHITE, pieceToMove, validMoves);
}
