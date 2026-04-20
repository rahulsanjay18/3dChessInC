cmake_minimum_required(VERSION 3.28)
project(CubeChess C CXX) # Specify languages

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 1. Collect Sources
file(GLOB C_FILES CONFIGURE_DEPENDS "src/*.c")
file(GLOB H_FILES CONFIGURE_DEPENDS "include/*.h")

# 2. Build the Static Library (Fixed name to match project)
add_library(${PROJECT_NAME} STATIC ${C_FILES} ${H_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC include)

# 3. Build the Executable
add_executable(${PROJECT_NAME}_exec "main.c" ${C_FILES})
target_include_directories(${PROJECT_NAME}_exec PRIVATE include)

# 4. Build GoogleTest Executable
option(BUILD_TESTS "Build the tests" ON)
if(BUILD_TESTS)
    # Assumes lib/ contains GoogleTest source (via add_subdirectory)
    add_subdirectory(lib)
    enable_testing()

    # Only grab the test files here
    file(GLOB TEST_SRC_FILES CONFIGURE_DEPENDS "tests/*.cpp") # Fixed folder name 'test'

    add_executable(${PROJECT_NAME}_test ${TEST_SRC_FILES})

    # Link to your library and GTest
    # This prevents re-compiling src/*.c and ensures proper C linkage
    target_link_libraries(${PROJECT_NAME}_test PRIVATE
            ${PROJECT_NAME}
            gtest
            gtest_main
    )

    # Add test to CTest runner
    add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)
endif()