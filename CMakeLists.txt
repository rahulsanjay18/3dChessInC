cmake_minimum_required(VERSION 3.28)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(PROJECT_NAME CubeChess)
include(include/CMakeLists.txt)
include(src/CMakeLists.txt)
file(GLOB C_FILES CONFIGURE_DEPENDS "src/*.c")
file(GLOB H_FILES CONFIGURE_DEPENDS "include/*.h")
project(${PROJECT_NAME})
add_subdirectory(Google_tests)
add_library(${PROJECT_NAME}_lib STATIC ${C_FILES} ${H_FILES})
add_executable(exec ${C_FILES})
target_include_directories(exec PRIVATE include)
option(BUILD_TESTS "Build the tests" ON)
if(BUILD_TESTS)

    add_subdirectory(Google_tests/lib/googletest)

    enable_testing()

    set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)

    include_directories(${GTEST_INCLUDE_DIRS})

    file(GLOB TEST_SRC_FILES "${${PROJECT_NAME}_SOURCE_DIR}/Google_tests/tests/*.cpp")
    add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})

    add_dependencies(${PROJECT_TEST_NAME} googletest)

    target_link_libraries(${PROJECT_TEST_NAME}
            ${GTEST_LIBS_DIR}/libgtest.a
            ${GTEST_LIBS_DIR}/libgtest_main.a
    )

    target_link_libraries(${PROJECT_TEST_NAME} ${PROJECT_NAME}_lib)

    target_link_libraries(${PROJECT_TEST_NAME} ${CMAKE_THREAD_LIBS_INIT})

    add_test(NAME project_test COMMAND ${PROJECT_TEST_NAME})

endif()