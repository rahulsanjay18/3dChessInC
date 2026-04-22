//
// Created by rahul on 4/20/2026.
//
extern "C" {
#include "board.h"
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

constexpr uint64_t ONE = 1;

// test board creation
TEST(BoardTestSuite, test_board_creation_initializes_elements_correctly)
{
    // Arrange.
    const auto board_repr = static_cast<char*>(calloc(BOARD_SIZE * BOARD_SIZE * BOARD_SIZE, sizeof(char)));

    constexpr int offset1 = TEST_X_COORD * X_DIM_OFFSET + TEST_Y_COORD * Y_DIM_OFFSET + TEST_Z_COORD;
    constexpr int offset2 = TEST_X2_COORD * X_DIM_OFFSET + TEST_Y2_COORD * Y_DIM_OFFSET + TEST_Z2_COORD;
    board_repr[offset1] = REPRESENTING_CHARACTER;
    board_repr[offset2] = REPRESENTING_CHARACTER;

    constexpr uint64_t bit_in_plane_to_examine = TEST_Y_COORD * Y_DIM_OFFSET + TEST_Z_COORD;
    constexpr uint64_t bit_in_plane_to_examine2 = TEST_Y2_COORD * Y_DIM_OFFSET + TEST_Z2_COORD;

    // Act.
    const Board* board = Board__create(REPRESENTING_CHARACTER, board_repr);

    const uint64_t first_coord = (board->bitboard[TEST_X_COORD] & (ONE << bit_in_plane_to_examine)) >> bit_in_plane_to_examine;
    const uint64_t second_coord = (board->bitboard[TEST_X2_COORD] & (ONE << bit_in_plane_to_examine2)) >> bit_in_plane_to_examine2;

    uint64_t value=0;
    unsigned int bit_counter=0; // c accumulates the total bits set in v
    for (const uint64_t i : board->bitboard)
    {
        value = i;
        int c = 0;
        for (c=0; value; c++)
        {
            value &= value - 1; // clear the least significant bit set
        }
        bit_counter += c;
    }

    // Assert.
    EXPECT_EQ(board->representing_character, REPRESENTING_CHARACTER);
    EXPECT_EQ(first_coord, 1);
    EXPECT_EQ(second_coord, 1);
    EXPECT_EQ(bit_counter, 2);

}

// test board deletion
TEST(BoardTestSuite, test_board_destruction_makes_every_element_null)
{
    // Arrange.
    const auto board_repr = static_cast<char*>(calloc(BOARD_SIZE * BOARD_SIZE * BOARD_SIZE, sizeof(char)));
    Board* board = Board__create(REPRESENTING_CHARACTER, board_repr);
    EXPECT_EQ(board->representing_character, REPRESENTING_CHARACTER);
    EXPECT_NE(board->bitboard, nullptr);

    // Act.
    Board__destroy(&board);

    // Assert.
    EXPECT_EQ(board, nullptr);

}

// test set value in board
TEST(BoardTestSuite, test_board_set_value_sets_correct_bit)
{
    // Arrange.
    const auto board_repr = static_cast<char*>(calloc(BOARD_SIZE * BOARD_SIZE * BOARD_SIZE, sizeof(char)));

    constexpr int offset1 = TEST_X_COORD * X_DIM_OFFSET + TEST_Y_COORD * Y_DIM_OFFSET + TEST_Z_COORD;
    board_repr[offset1] = REPRESENTING_CHARACTER;

    constexpr uint64_t bit_in_plane_to_examine = TEST_Y_COORD * Y_DIM_OFFSET + TEST_Z_COORD;
    constexpr uint64_t bit_in_plane_to_examine2 = TEST_Y2_COORD * Y_DIM_OFFSET + TEST_Z2_COORD;
    Board* board = Board__create(REPRESENTING_CHARACTER, board_repr);
    // Act.
    Board__set(board, Coordinates__create(TEST_X2_COORD, TEST_Y2_COORD, TEST_Z2_COORD));

    const uint64_t first_coord = (board->bitboard[TEST_X_COORD] & (ONE << bit_in_plane_to_examine)) >> bit_in_plane_to_examine;
    const uint64_t second_coord = (board->bitboard[TEST_X2_COORD] & (ONE << bit_in_plane_to_examine2)) >> bit_in_plane_to_examine2;

    uint64_t value=0;
    unsigned int bit_counter=0; // c accumulates the total bits set in v
    for (const uint64_t i : board->bitboard)
    {
        value = i;
        int c = 0;
        for (c=0; value; c++)
        {
            value &= value - 1; // clear the least significant bit set
        }
        bit_counter += c;
    }

    // Assert.
    EXPECT_EQ(board->representing_character, REPRESENTING_CHARACTER);
    EXPECT_EQ(first_coord, 1);
    EXPECT_EQ(second_coord, 1);
    EXPECT_EQ(bit_counter, 2);
}
// test unset value in board
TEST(BoardTestSuite, test_board_unset_sets_correct_bit_to_zero)
{
    // Arrange.
    const auto board_repr = static_cast<char*>(calloc(BOARD_SIZE * BOARD_SIZE * BOARD_SIZE, sizeof(char)));

    constexpr int offset1 = TEST_X_COORD * X_DIM_OFFSET + TEST_Y_COORD * Y_DIM_OFFSET + TEST_Z_COORD;
    constexpr int offset2 = TEST_X2_COORD * X_DIM_OFFSET + TEST_Y2_COORD * Y_DIM_OFFSET + TEST_Z2_COORD;
    board_repr[offset1] = REPRESENTING_CHARACTER;
    board_repr[offset2] = REPRESENTING_CHARACTER;

    constexpr uint64_t bit_in_plane_to_examine = TEST_Y_COORD * Y_DIM_OFFSET + TEST_Z_COORD;
    constexpr uint64_t bit_in_plane_to_examine2 = TEST_Y2_COORD * Y_DIM_OFFSET + TEST_Z2_COORD;
    Board* board = Board__create(REPRESENTING_CHARACTER, board_repr);

    // Act.
    Board__unset(board, Coordinates__create(TEST_X2_COORD, TEST_Y2_COORD, TEST_Z2_COORD));

    const uint64_t first_coord = (board->bitboard[TEST_X_COORD] & (ONE << bit_in_plane_to_examine)) >> bit_in_plane_to_examine;
    const uint64_t second_coord = (board->bitboard[TEST_X2_COORD] & (ONE << bit_in_plane_to_examine2)) >> bit_in_plane_to_examine2;

    uint64_t value=0;
    unsigned int bit_counter=0; // c accumulates the total bits set in v
    for (const uint64_t i : board->bitboard)
    {
        value = i;
        int c = 0;
        for (c=0; value; c++)
        {
            value &= value - 1; // clear the least significant bit set
        }
        bit_counter += c;
    }

    // Assert.
    EXPECT_EQ(board->representing_character, REPRESENTING_CHARACTER);
    EXPECT_EQ(first_coord, 1);
    EXPECT_EQ(second_coord, 0);
    EXPECT_EQ(bit_counter, 1);

}

// test retrieve value from board
TEST(BoardTestSuite, test_board_retrieval_gets_true_and_false_depending_on_location)
{
    // Arrange.
    const auto board_repr = static_cast<char*>(calloc(BOARD_SIZE * BOARD_SIZE * BOARD_SIZE, sizeof(char)));

    constexpr int offset1 = TEST_X_COORD * X_DIM_OFFSET + TEST_Y_COORD * Y_DIM_OFFSET + TEST_Z_COORD;
    constexpr int offset2 = TEST_X2_COORD * X_DIM_OFFSET + TEST_Y2_COORD * Y_DIM_OFFSET + TEST_Z2_COORD;

    board_repr[offset1] = REPRESENTING_CHARACTER;
    board_repr[offset2] = REPRESENTING_CHARACTER;

    Board* board = Board__create(REPRESENTING_CHARACTER, board_repr);
    Board__unset(board, Coordinates__create(TEST_X2_COORD, TEST_Y2_COORD, TEST_Z2_COORD));

    // Act.
    bool exists1 = Board__get(board, Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD));
    bool exists2 = Board__get(board, Coordinates__create(TEST_X2_COORD, TEST_Y2_COORD, TEST_Z2_COORD));


    // Assert.
    ASSERT_TRUE(exists1);
    ASSERT_FALSE(exists2);

}