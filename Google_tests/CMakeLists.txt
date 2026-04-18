project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
file(GLOB C_FILES CONFIGURE_DEPENDS "${CubeChess_SOURCE_DIR}/src/*.c")
message(${C_FILES})
message(${gtest_SOURCE_DIR})
# adding the Google_Tests_run target
add_executable(Google_Tests_run tests/test_main.cpp ${C_FILES})
# linking Google_Tests_run with DateConverter_lib which will be tested
target_include_directories(Google_Tests_run PRIVATE ${CubeChess_SOURCE_DIR}/include)
target_link_libraries(Google_Tests_run gtest gtest_main)
