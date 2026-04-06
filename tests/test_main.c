#include <CUnit/Basic.h>

int main() {
    CU_initialize_registry();
    CU_pSuite pSuite = CU_add_suite("MathSuite", 0, 0);
    
    // Add tests to the suite
    CU_add_test(pSuite, "test_add", test_add);
    
    // Run tests
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
