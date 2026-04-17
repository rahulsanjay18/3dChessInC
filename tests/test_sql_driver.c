#include <CUnit/Basic.h>
#include <stdio.h>
#include <sqlite3.h>
#include "../src/sql_driver.c"
#include "../src/coordinates.c"

void test_is_move_valid_with_valid_move(){
	open_db();
	Coordinates* start = Coordinates__create(0, 0, 0);
	Coordinates* end = Coordinates__create(1,0,0);
	bool result = is_move_valid('r', start, end);

	CU_ASSERT(result);
}
