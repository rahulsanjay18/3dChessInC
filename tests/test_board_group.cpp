//
// Created by rahul on 4/20/2026.
//
extern "C" {
#include "board.h"
#include "board_group.h"
#include "constants.h"
#include <stdlib.h>
}
#include "gtest/gtest.h"

constexpr int TEST_X_COORD = 3;
constexpr int TEST_Y_COORD = 4;
constexpr int TEST_Z_COORD = 2;

constexpr int TEST_X2_COORD = 4;
constexpr int TEST_Y2_COORD = 5;
constexpr int TEST_Z2_COORD = 6;
constexpr char REPRESENTING_CHARACTER = 'r';

constexpr int X_DIM_OFFSET = BOARD_SIZE * BOARD_SIZE;
constexpr int Y_DIM_OFFSET = BOARD_SIZE;

// test Boards creation
TEST(BoardGroupTestSuite, test_create_board_group_initializes_elements)
{
    // Arrange.
    const auto board_repr = static_cast<char*>(calloc(BOARD_SIZE * BOARD_SIZE * BOARD_SIZE, sizeof(char)));
    constexpr int offset1 = TEST_X_COORD * X_DIM_OFFSET + TEST_Y_COORD * Y_DIM_OFFSET + TEST_Z_COORD;
    constexpr int offset2 = TEST_X2_COORD * X_DIM_OFFSET + TEST_Y2_COORD * Y_DIM_OFFSET + TEST_Z2_COORD;
    board_repr[offset1] = REPRESENTING_CHARACTER;
    board_repr[offset2] = REPRESENTING_CHARACTER;

    // Act.
    Boards * boards = Boards__create(board_repr);

    // Assert.
    EXPECT_NE(boards, nullptr);
    EXPECT_NE(boards->full_board, nullptr);

}

// test Boards Destroy
TEST(BoardGroupTestSuite, test_delete_board_group_frees_elements)
{
    // Arrange.
    const auto board_repr = static_cast<char*>(calloc(BOARD_SIZE * BOARD_SIZE * BOARD_SIZE, sizeof(char)));
    constexpr int offset1 = TEST_X_COORD * X_DIM_OFFSET + TEST_Y_COORD * Y_DIM_OFFSET + TEST_Z_COORD;
    constexpr int offset2 = TEST_X2_COORD * X_DIM_OFFSET + TEST_Y2_COORD * Y_DIM_OFFSET + TEST_Z2_COORD;
    board_repr[offset1] = REPRESENTING_CHARACTER;
    board_repr[offset2] = REPRESENTING_CHARACTER;
    Boards * boards = Boards__create(board_repr);

    // Act.
    Boards__destroy(&boards);

    // Assert.
    EXPECT_EQ(boards, nullptr);

}

// test Boards set
TEST(BoardGroupTestSuite, test_board_group_set_writes_bit)
{
    // Arrange.
    const auto board_repr = static_cast<char*>(calloc(BOARD_SIZE * BOARD_SIZE * BOARD_SIZE, sizeof(char)));
    Boards * boards = Boards__create(board_repr);
    Coordinates* coordinates = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    int piece_index = char_to_int(REPRESENTING_CHARACTER);

    // Act.
    Boards__set_piece(boards, REPRESENTING_CHARACTER,coordinates);

    // Assert.
    bool is_piece_set = Board__get(boards->full_board[piece_index], coordinates);
    EXPECT_TRUE(is_piece_set);

}

// test Boards unset
TEST(BoardGroupTestSuite, test_unset_specific_piece_board_in_group_sets_value_to_zero)
{
    // Arrange.
    const auto board_repr = static_cast<char*>(calloc(BOARD_SIZE * BOARD_SIZE * BOARD_SIZE, sizeof(char)));
    constexpr int offset1 = TEST_X_COORD * X_DIM_OFFSET + TEST_Y_COORD * Y_DIM_OFFSET + TEST_Z_COORD;
    constexpr int offset2 = TEST_X2_COORD * X_DIM_OFFSET + TEST_Y2_COORD * Y_DIM_OFFSET + TEST_Z2_COORD;
    board_repr[offset1] = REPRESENTING_CHARACTER;
    board_repr[offset2] = REPRESENTING_CHARACTER;
    Boards * boards = Boards__create(board_repr);
    Coordinates* coordinates = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    int piece_index = char_to_int(REPRESENTING_CHARACTER);
    bool is_piece_set = Board__get(boards->full_board[piece_index], coordinates);
    EXPECT_TRUE(is_piece_set);

    // Act.
    Boards__unset_piece(boards, REPRESENTING_CHARACTER, coordinates);

    // Assert.
    bool is_piece_unset = Board__get(boards->full_board[piece_index], coordinates);
    EXPECT_FALSE(is_piece_unset);

}

TEST(BoardGroupTestSuite, test_unset_piece_board_in_group_sets_value_to_zero)
{
    // Arrange.
    const auto board_repr = static_cast<char*>(calloc(BOARD_SIZE * BOARD_SIZE * BOARD_SIZE, sizeof(char)));
    constexpr int offset1 = TEST_X_COORD * X_DIM_OFFSET + TEST_Y_COORD * Y_DIM_OFFSET + TEST_Z_COORD;
    constexpr int offset2 = TEST_X2_COORD * X_DIM_OFFSET + TEST_Y2_COORD * Y_DIM_OFFSET + TEST_Z2_COORD;
    board_repr[offset1] = REPRESENTING_CHARACTER;
    board_repr[offset2] = REPRESENTING_CHARACTER;
    Boards * boards = Boards__create(board_repr);
    Coordinates* coordinates = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    int piece_index = char_to_int(REPRESENTING_CHARACTER);
    bool is_piece_set = Board__get(boards->full_board[piece_index], coordinates);
    EXPECT_TRUE(is_piece_set);

    // Act.
    Boards__unset(boards, coordinates);

    // Assert.
    bool is_piece_unset = Board__get(boards->full_board[piece_index], coordinates);
    EXPECT_FALSE(is_piece_unset);

}

// test Boards read
TEST(BoardGroupTestSuite, test_read_from_board_group_returns_correct_char)
{
    // Arrange.
    const auto board_repr = static_cast<char*>(calloc(BOARD_SIZE * BOARD_SIZE * BOARD_SIZE, sizeof(char)));
    constexpr int offset1 = TEST_X_COORD * X_DIM_OFFSET + TEST_Y_COORD * Y_DIM_OFFSET + TEST_Z_COORD;
    board_repr[offset1] = REPRESENTING_CHARACTER;
    Boards * boards = Boards__create(board_repr);

    // Act.
    char piece = Boards__get_piece(boards, Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD));
    char piece2 = Boards__get_piece(boards, Coordinates__create(TEST_X2_COORD, TEST_Y2_COORD, TEST_Z2_COORD));

    // Assert.
    EXPECT_EQ(piece, REPRESENTING_CHARACTER);
    EXPECT_EQ(piece2, '\0');

}