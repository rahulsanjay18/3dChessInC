cmake_minimum_required(VERSION 3.28)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
project(CubeChess)
add_subdirectory(Google_tests)
add_subdirectory(src)
add_subdirectory(include)
add_executable(exec src/main.c)
target_link_libraries(CubeChess LINK_PUBLIC ${CubeChess_SOURCE_DIR}/lib/sqlite/sqlite3.h)
target_link_libraries(exec PUBLIC CubeChess)
#TESTS
project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
file(GLOB C_FILES CONFIGURE_DEPENDS "${CubeChess_SOURCE_DIR}/src/*.c")
message(${C_FILES})
message(${gtest_SOURCE_DIR})
# adding the Google_Tests_run target
add_executable(Google_Tests_run tests/test_main.cpp)
# linking Google_Tests_run with DateConverter_lib which will be tested
target_link_libraries(Google_Tests_run CubeChess_lib)
target_include_directories(Google_Tests_run PUBLIC ${CubeChess_SOURCE_DIR}/include)
target_link_libraries(Google_Tests_run gtest gtest_main)
#googletest
cmake_minimum_required(VERSION 3.28)
project(gtest_builder C CXX)
#add_subdirectory(lib)
include(ExternalProject)

set(GTEST_FORCE_SHARED_CRT ON)

ExternalProject_Add(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        CMAKE_ARGS
        -DCMAKE_CXX_FLAGS=${MSVC_COMPILER_DEFS}
        -Dgtest_force_shared_crt=${GTEST_FORCE_SHARED_CRT}
        -Dgtest_disable_pthreads=${GTEST_DISABLE_PTHREADS}
        -DBUILD_GTEST=ON
        PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
        INSTALL_COMMAND ""
)

ExternalProject_Get_Property(googletest source_dir)

set(GTEST_INCLUDE_DIRS ${source_dir}/googletest/include PARENT_SCOPE)

ExternalProject_Get_Property(googletest binary_dir)
set(GTEST_LIBS_DIR ${binary_dir}/googlemock/gtest PARENT_SCOPE)