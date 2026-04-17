#include <CUnit/Basic.h>
#include <sqlite3.h>
#include "test_sql_driver.c"

int main() {
    CU_initialize_registry();
    CU_pSuite pSuite = CU_add_suite("sql_drivers", 0, 0);
    
    // Add tests to the suite
    CU_add_test(pSuite, "test_is_move_valid_with_valid_move", test_is_move_valid_with_valid_move);
    
    // Run tests
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
