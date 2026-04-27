#include <list>
//
// Created by rahul on 4/16/2026.
//
extern "C" {
#include "sql_driver.h"
#include "coordinates.h"
#include <stdio.h>
}


#include "gtest/gtest.h"


TEST(SQLDriverTestSuite, test_is_move_valid_with_valid_move)
{
    open_db(true);
    Coordinates* start = Coordinates__create(0, 0, 0);
    Coordinates* end = Coordinates__create(1, 0, 0);
    const bool res = is_move_valid('r', start, end);

    EXPECT_EQ(res, true);
}


TEST(SQLDriverTestSuite, test_is_move_valid_with_invalid_move)
{
    open_db(true);
    Coordinates* start = Coordinates__create(0, 0, 0);
    Coordinates* end = Coordinates__create(1, 1, 0);
    const bool res = is_move_valid('r', start, end);

    EXPECT_EQ(res, false);
}

TEST(SQLDriverTestSuite, test_get_valid_moves)
{
    open_db(true);
    Coordinates* xyz = Coordinates__create(0, 0, 0);
    const CoordinateList* list = get_possible_moves('r', xyz);

    for (int i = 0; i < res->len; i++)
    {
        auto [x, y, z] = CoordinateList__retrieve_node_from_index(list, i)->coordinates;
        EXPECT_EQ((x != 0) + (y != 0) + (z != 0), 1);
    }

}