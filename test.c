#include "tau/tau.h"
#include "core.h"

TAU_MAIN()

void ASSERT_VALID_MOVES_MATCH(GameSnapshot *gameSnapshot, const Position pieceToMove, bool validMoves[COLS][ROWS]) {
    REQUIRE_TRUE(pieceToMove.col > -1 && pieceToMove.row > -1, "Piece not found");

    for (int col = 0; col < COLS; col++) {
        for (int row = 0; row < ROWS; row++) {
            const bool expectedCanMove = validMoves[col][row];
            const Position destination = {col, row};
            CHECK_EQ(
                isMoveValid(gameSnapshot, pieceToMove, destination),
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

TEST(all, cannot_move_piece_on_another_if_same_colour) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, WP, WP, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
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

    ASSERT_VALID_MOVES_MATCH(&gameSnapshot, pieceToMove, validMoves);
}

TEST(all, cannot_move_piece_out_of_board) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, WP},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, WP);

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
    ASSERT_VALID_MOVES_MATCH(&gameSnapshot, pieceToMove, validMoves);

    const Position outOfBoard = {3, 8};
    REQUIRE_EQ(
        isMoveValid(&gameSnapshot, pieceToMove, outOfBoard),
        false
    );
}

TEST(pawn, white_can_move_1_cell_front_when_not_at_start_row) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, WP, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, WP);

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

    ASSERT_VALID_MOVES_MATCH(&gameSnapshot, pieceToMove, validMoves);
}

TEST(pawn, white_can_move_1_or_2_cells_front_when_at_start_row) {
    GameSnapshot gameSnapshot = {
        {
            {__, WP, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, WP);

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

    ASSERT_VALID_MOVES_MATCH(&gameSnapshot, pieceToMove, validMoves);
}

TEST(pawn, white_cannot_move_2_cells_front_when_piece_in_front_of_it) {
    GameSnapshot gameSnapshot = {
        {
            {__, WP, BP, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, WP);

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

    ASSERT_VALID_MOVES_MATCH(&gameSnapshot, pieceToMove, validMoves);
}

TEST(pawn, white_can_eat_at_front_left_or_front_right) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, BP, __, __, __, __},
            {__, __, WP, BP, __, __, __, __},
            {__, __, __, BP, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, WP);

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

    ASSERT_VALID_MOVES_MATCH(&gameSnapshot, pieceToMove, validMoves);
}

TEST(pawn, black_can_move_1_cell_front_when_not_at_start_row) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, BP, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, BP);

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

    ASSERT_VALID_MOVES_MATCH(&gameSnapshot, pieceToMove, validMoves);
}

TEST(pawn, black_can_move_1_or_2_cells_front_when_at_start_row) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, __, BP, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, BP);

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

    ASSERT_VALID_MOVES_MATCH(&gameSnapshot, pieceToMove, validMoves);
}

TEST(pawn, black_cannot_move_2_cells_front_when_piece_in_front_of_it) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, WP, BP, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, BP);

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

    ASSERT_VALID_MOVES_MATCH(&gameSnapshot, pieceToMove, validMoves);
}

TEST(pawn, black_can_eat_at_front_left_or_front_right) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, WP, __, __, __},
            {__, __, __, __, WP, BP, __, __},
            {__, __, __, __, WP, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, BP);

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

    ASSERT_VALID_MOVES_MATCH(&gameSnapshot, pieceToMove, validMoves);
}

TEST(knight, can_move_in_l_shape) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, WN, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, WN);

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

    ASSERT_VALID_MOVES_MATCH(&gameSnapshot, pieceToMove, validMoves);
}

TEST(king, can_move_in_any_direction_at_distance_of_1) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, WK, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, WK);

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

    ASSERT_VALID_MOVES_MATCH(&gameSnapshot, pieceToMove, validMoves);
}

TEST(king, can_castle_kingside) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {WK, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {WR, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, WK);
    const Position destination = {6, 0};

    REQUIRE_TRUE(isMoveValid(&gameSnapshot, pieceToMove, destination));
}

TEST(king, cannot_castle_kingside_when_piece_between) {
    GameSnapshot gameSnapshot1 = {
        {
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {WK, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {WN, __, __, __, __, __, __, __},
            {WR, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    GameSnapshot gameSnapshot2 = {
        {
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {WK, __, __, __, __, __, __, __},
            {WB, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {WR, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot1.board, WK);
    const Position destination = {6, 0};

    REQUIRE_FALSE(isMoveValid(&gameSnapshot1, pieceToMove, destination));
    REQUIRE_FALSE(isMoveValid(&gameSnapshot2, pieceToMove, destination));
}

TEST(king, cannot_castle_kingside_when_lost_castling) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {WK, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {WR, __, __, __, __, __, __, __},
        },
        WHITE,
        true,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, WK);
    const Position destination = {6, 0};

    REQUIRE_FALSE(isMoveValid(&gameSnapshot, pieceToMove, destination));
}

TEST(king, can_castle_queenside) {
    GameSnapshot gameSnapshot = {
        {
            {WR, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {WK, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, WK);
    const Position destination = {2, 0};

    REQUIRE_TRUE(isMoveValid(&gameSnapshot, pieceToMove, destination));
}

TEST(king, cannot_castle_queenside_when_piece_between) {
    GameSnapshot gameSnapshot1 = {
        {
            {WR, __, __, __, __, __, __, __},
            {WN, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {WK, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    GameSnapshot gameSnapshot2 = {
        {
            {WR, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {WB, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {WK, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    GameSnapshot gameSnapshot3 = {
        {
            {WR, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {WQ, __, __, __, __, __, __, __},
            {WK, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot1.board, WK);
    const Position destination = {2, 0};

    REQUIRE_FALSE(isMoveValid(&gameSnapshot1, pieceToMove, destination));
    REQUIRE_FALSE(isMoveValid(&gameSnapshot2, pieceToMove, destination));
    REQUIRE_FALSE(isMoveValid(&gameSnapshot3, pieceToMove, destination));
}

TEST(king, cannot_castle_queenside_when_lost_castling) {
    GameSnapshot gameSnapshot = {
        {
            {WR, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {WK, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        true,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, WK);
    const Position destination = {2, 0};

    REQUIRE_FALSE(isMoveValid(&gameSnapshot, pieceToMove, destination));
}

TEST(rook, can_move_in_column_or_row_at_any_distance) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, WR, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, WR);

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

    ASSERT_VALID_MOVES_MATCH(&gameSnapshot, pieceToMove, validMoves);
}

TEST(rook, cannot_go_over_pieces) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, __, __, __},
            {__, __, __, BP, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, BP, __, WR, __, BP, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, BP, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, WR);

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

    ASSERT_VALID_MOVES_MATCH(&gameSnapshot, pieceToMove, validMoves);
}

TEST(bishop, can_move_in_diagonal_at_any_distance) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, WB, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, WB);

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

    ASSERT_VALID_MOVES_MATCH(&gameSnapshot, pieceToMove, validMoves);
}

TEST(bishop, cannot_go_over_pieces) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, __, __, __},
            {__, BP, __, __, __, BP, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, WB, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, BP, __, __, __, BP, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, WB);

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

    ASSERT_VALID_MOVES_MATCH(&gameSnapshot, pieceToMove, validMoves);
}

TEST(queen, can_move_in_column_or_row_or_diagonal_at_any_distance) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, WQ, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, WQ);

    bool validMoves[8][8] = {
        {1, 0, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {1, 1, 1, 0, 1, 1, 1, 1},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 0},
        {1, 0, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 1},
    };

    ASSERT_VALID_MOVES_MATCH(&gameSnapshot, pieceToMove, validMoves);
}

TEST(queen, cannot_go_over_pieces) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, __, __, __},
            {__, BP, __, BP, __, BP, __, __},
            {__, __, __, __, __, __, __, __},
            {__, BP, __, WQ, __, BP, __, __},
            {__, __, __, __, __, __, __, __},
            {__, BP, __, BP, __, BP, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, WQ);

    bool validMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 1, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_VALID_MOVES_MATCH(&gameSnapshot, pieceToMove, validMoves);
}

TEST(isKingInCheck, should_return_true_when_piece_can_eat_king) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, WK, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, BQ, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        BLACK,
        false,
        false,
    };

    REQUIRE_TRUE(isKingInCheck(&gameSnapshot));
}

TEST(isKingInCheck, should_return_false_when_none_piece_can_eat_king) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, WK, __, __, __, __},
            {__, __, __, __, WP, __, __, __},
            {__, __, __, __, __, BQ, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        BLACK,
        false,
        false,
    };

    REQUIRE_FALSE(isKingInCheck(&gameSnapshot));
}
