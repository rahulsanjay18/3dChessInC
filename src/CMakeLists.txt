file(GLOB C_FILES CONFIGURE_DEPENDS "*.c")
add_library(CubeChess ${C_FILES})
target_include_directories(CubeChess PUBLIC ${CubeChess_SOURCE_DIR}/include)
