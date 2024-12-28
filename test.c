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
    REQUIRE_NE(pieceToMove.col, -1);
    REQUIRE_NE(pieceToMove.row, -1);

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

TEST(isColumnEmptyOnRange, return_false_if_not_same_column) {
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

    CHECK_FALSE(isColumnEmptyOnRange(board, start, end));
}

TEST(isColumnEmptyOnRange, return_false_piece_in_the_range) {
    Piece board[8][8] = {
        {WP, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
        {__, __, __, __, __, __, __, __},
    };

    const Position start = {0, 0};
    const Position end = {0, 1};

    CHECK_FALSE(isColumnEmptyOnRange(board, start, end));
}

TEST(isColumnEmptyOnRange, return_true_if_no_piece_in_the_range) {
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
    const Position end = {0, 1};

    CHECK_TRUE(isColumnEmptyOnRange(board, start, end));
}

TEST(basic, cannot_move_other_player_piece) {
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

TEST(basic, cannot_move_piece_on_another_if_same_colour) {
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

TEST(basic, cannot_move_piece_out_of_board) {
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

TEST(pawn, white_pawn_can_move_1_cell_front_when_not_at_start_row) {
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

TEST(pawn, white_pawn_can_move_1_or_2_cells_front_when_at_start_row) {
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

TEST(pawn, white_pawn_cannot_move_2_cells_front_when_piece_in_front_of_it) {
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

TEST(pawn, white_pawn_can_eat_at_front_left_or_front_right) {
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

TEST(pawn, black_pawn_can_move_1_cell_front_when_not_at_start_row) {
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

TEST(pawn, black_pawn_can_move_1_or_2_cells_front_when_at_start_row) {
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

TEST(pawn, black_pawn_cannot_move_2_cells_front_when_piece_in_front_of_it) {
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

TEST(pawn, black_pawn_can_eat_at_front_left_or_front_right) {
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

TEST(knight, knight_can_move_in_l_shape) {
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
