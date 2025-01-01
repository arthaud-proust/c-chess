#include "tau/tau.h"
#include "core.h"

TAU_MAIN()

void ASSERT_PLAYABLE_MOVES_MATCH(GameSnapshot *gameSnapshot, const Position pieceToMove, bool playableMoves[COLS][ROWS]) {
    REQUIRE_TRUE(pieceToMove.col > -1 && pieceToMove.row > -1, "Piece not found");

    for (int col = 0; col < COLS; col++) {
        for (int row = 0; row < ROWS; row++) {
            const bool expectedCanMove = playableMoves[col][row];
            const Position destination = {col, row};
            CHECK_EQ(
                canPlay(gameSnapshot, pieceToMove, destination),
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
        {WK, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, BK, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };

    const Position start = positionOfPiece(board, WK);
    const Position end = positionOfPiece(board, BK);

    CHECK_FALSE(isDiagonalEmptyBetween(board, start, end));
    CHECK_FALSE(isDiagonalEmptyBetween(board, end, start));
}

TEST(isDiagonalEmptyBetween, return_true_if_no_piece_between_start_and_end) {
    Piece board1[8][8] = {
        {WK, WP, WP, WP, __, __, __, __},
        {WP, __, WP, WP, __, __, __, __},
        {WP, WP, __, WP, __, __, __, __},
        {WP, WP, WP, BQ, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };
    Piece board2[8][8] = {
        {WP, WP, WP, BQ, __, __, __, __},
        {WP, WP, __, WP, __, __, __, __},
        {WP, __, WP, WP, __, __, __, __},
        {WK, WP, WP, WP, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };

    CHECK_TRUE(isDiagonalEmptyBetween(board1, positionOfPiece(board1, WK), positionOfPiece(board1, BQ)));
    CHECK_TRUE(isDiagonalEmptyBetween(board1, positionOfPiece(board1, BQ), positionOfPiece(board1, WK)));

    CHECK_TRUE(isDiagonalEmptyBetween(board2, positionOfPiece(board2, WK), positionOfPiece(board2, BQ)));
    CHECK_TRUE(isDiagonalEmptyBetween(board2, positionOfPiece(board2, BQ), positionOfPiece(board2, WK)));
}

TEST(isDiagonalEmptyBetween, return_false_if_piece_between_start_and_end) {
    Piece board1[8][8] = {
        {WK, WP, WP, WP, __, __, __, __},
        {WP, WP, WP, WP, __, __, __, __},
        {WP, WP, WP, WP, __, __, __, __},
        {WP, WP, WP, BQ, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };
    Piece board2[8][8] = {
        {WP, WP, WP, BQ, __, __, __, __},
        {WP, WP, WP, WP, __, __, __, __},
        {WP, WP, WP, WP, __, __, __, __},
        {WK, WP, WP, WP, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };

    CHECK_FALSE(isDiagonalEmptyBetween(board1, positionOfPiece(board1, WK), positionOfPiece(board1, BQ)));
    CHECK_FALSE(isDiagonalEmptyBetween(board1, positionOfPiece(board1, BQ), positionOfPiece(board1, WK)));

    CHECK_FALSE(isDiagonalEmptyBetween(board2, positionOfPiece(board2, WK), positionOfPiece(board2, BQ)));
    CHECK_FALSE(isDiagonalEmptyBetween(board2, positionOfPiece(board2, BQ), positionOfPiece(board2, WK)));
}

TEST(all, cannot_move_other_color) {
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

    bool playableMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);
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

    bool playableMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);
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

    bool playableMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };
    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);

    const Position outOfBoard = {3, 8};
    REQUIRE_EQ(
        isMoveValid(&gameSnapshot, pieceToMove, outOfBoard),
        false
    );
}

TEST(all, cannot_move_if_it_put_king_in_check) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, BQ, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, WP, __, __, __, __, __},
            {__, WK, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, WP);

    bool playableMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };
    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);
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

    bool playableMoves[8][8] = {
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);
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

    bool playableMoves[8][8] = {
        {0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);
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

    bool playableMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);
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

    bool playableMoves[8][8] = {
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);
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
        BLACK,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, BP);

    bool playableMoves[8][8] = {
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);
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
        BLACK,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, BP);

    bool playableMoves[8][8] = {
        {0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);
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
        BLACK,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, BP);

    bool playableMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);
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
        BLACK,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, BP);

    bool playableMoves[8][8] = {
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);
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

    bool playableMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);
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

    bool playableMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);
}

TEST(king, cannot_move_where_it_will_be_in_check) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, WK, __, __, __, __},
            {__, __, __, __, __, BQ, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    const Position pieceToMove = positionOfPiece(gameSnapshot.board, WK);

    bool playableMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);
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

    bool playableMoves[8][8] = {
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {1, 1, 1, 0, 1, 1, 1, 1},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
    };

    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);
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

    bool playableMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);
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

    bool playableMoves[8][8] = {
        {1, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
    };

    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);
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

    bool playableMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);
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

    bool playableMoves[8][8] = {
        {1, 0, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {1, 1, 1, 0, 1, 1, 1, 1},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 0},
        {1, 0, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 1},
    };

    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);
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

    bool playableMoves[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 1, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_PLAYABLE_MOVES_MATCH(&gameSnapshot, pieceToMove, playableMoves);
}

TEST(isPlayerInCheck, should_return_true_when_a_piece_can_eat_king) {
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

    REQUIRE_TRUE(isPlayerInCheck(&gameSnapshot, WHITE));
}

TEST(isPlayerInCheck, should_return_false_when_none_piece_can_eat_king) {
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

    REQUIRE_FALSE(isPlayerInCheck(&gameSnapshot, WHITE));
}

TEST(play, mark_castling_at_lost_if_king_moved) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {WK, BR, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        WHITE,
        false,
        false,
    };
    Position origin = positionOfPiece(gameSnapshot.board, WK);
    Position destination = positionOfPiece(gameSnapshot.board, BR);

    ActionResult result = play(&gameSnapshot, origin, destination);
    REQUIRE_TRUE(result.gameSnapshot.hasWhiteLostCastling);
}

TEST(play, mark_castling_at_lost_if_rook_moved) {
    GameSnapshot gameSnapshot = {
        {
            {WR, BR, __, __, __, __, __, __},
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
    Position origin = positionOfPiece(gameSnapshot.board, WR);
    Position destination = positionOfPiece(gameSnapshot.board, BR);

    ActionResult result = play(&gameSnapshot, origin, destination);
    REQUIRE_TRUE(result.gameSnapshot.hasWhiteLostCastling);
}

TEST(play, do_not_change_lost_castling_if_king_and_rook_unmoved) {
    GameSnapshot gameSnapshot = {
        {
            {__, WP, __, __, __, __, __, __},
            {__, __, BP, __, __, __, __, __},
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
    Position origin = positionOfPiece(gameSnapshot.board, WP);
    Position destination = positionOfPiece(gameSnapshot.board, BP);

    ActionResult result = play(&gameSnapshot, origin, destination);
    REQUIRE_FALSE(result.gameSnapshot.hasWhiteLostCastling);
}

TEST(play, move_king_and_rook_when_castling_king_side) {
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
    Position origin = positionOfPiece(gameSnapshot.board, WK);
    Position destination = {2, 0};

    ActionResult result = play(&gameSnapshot, origin, destination);
    REQUIRE_TRUE(result.success);
    REQUIRE_EQ(pieceAtColRow(result.gameSnapshot.board, 2, 0), WK);
    REQUIRE_EQ(pieceAtColRow(result.gameSnapshot.board, 3, 0), WR);
}

TEST(play, move_king_and_rook_when_castling_queen_side) {
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
    Position origin = positionOfPiece(gameSnapshot.board, WK);
    Position destination = {6, 0};

    ActionResult result = play(&gameSnapshot, origin, destination);
    REQUIRE_TRUE(result.success);
    REQUIRE_EQ(pieceAtColRow(result.gameSnapshot.board, 6, 0), WK);
    REQUIRE_EQ(pieceAtColRow(result.gameSnapshot.board, 5, 0), WR);
}

TEST(canPromote, return_true_when_white_pawn_is_at_end_of_board) {
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
    Position origin = positionOfPiece(gameSnapshot.board, WP);

    REQUIRE_TRUE(canPromote(&gameSnapshot, origin));
}

TEST(canPromote, return_true_when_black_pawn_is_at_end_of_board) {
    GameSnapshot gameSnapshot = {
        {
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {BP, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
            {__, __, __, __, __, __, __, __},
        },
        BLACK,
        false,
        false,
    };
    Position origin = positionOfPiece(gameSnapshot.board, BP);

    REQUIRE_TRUE(canPromote(&gameSnapshot, origin));
}

TEST(canPromoteTo, return_false_if_promoting_other_color) {
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
    Position origin = positionOfPiece(gameSnapshot.board, WP);

    REQUIRE_TRUE(canPromoteTo(&gameSnapshot, origin, WQ));
}

TEST(promote, replace_pawn_by_promotion_piece) {
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
    Position origin = positionOfPiece(gameSnapshot.board, WP);

    ActionResult result = promoteTo(&gameSnapshot, origin, WQ);
    REQUIRE_TRUE(result.success);
}
