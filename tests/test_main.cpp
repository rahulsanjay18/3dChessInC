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
    open_db();
    Coordinates* start = Coordinates__create(0, 0, 0);
    Coordinates* end = Coordinates__create(1, 0, 0);
    const bool res = is_move_valid('r', start, end);

    EXPECT_EQ(res, true);
}


// TEST(AbsoluteDateTestSuite, IncorrectDate){ // 12/0/2020 -> 0
//     GregorianDate gregDate;
//     gregDate.SetMonth(12);
//     gregDate.SetDay(0);
//     gregDate.SetYear(2020);
//
//     ASSERT_EQ(gregDate.getAbsoluteDate(),0);
// }
