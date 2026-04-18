project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
# adding the Google_Tests_run target
add_executable(Google_Tests_run test_main.cpp ${CubeChess_SOURCE_DIR}/src  ${CubeChess_SOURCE_DIR}/include  ${CubeChess_SOURCE_DIR}/lib)
# linking Google_Tests_run with DateConverter_lib which will be tested
include_directories(Google_Tests_run ${CubeChess_SOURCE_DIR}/src)
include_directories(Google_Tests_run ${CubeChess_SOURCE_DIR}/include)
include_directories(Google_Tests_run ${CubeChess_SOURCE_DIR}/lib)

target_link_libraries(Google_Tests_run gtest gtest_main)
