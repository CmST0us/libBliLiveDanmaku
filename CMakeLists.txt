cmake_minimum_required(VERSION 3.0)

project(BliLiveDanmaku)

aux_source_directory(jsoncpp/lib_json BLI_JSONCPP_SOURCE_DIR)

include_directories(format PRIVATE)
include_directories(jsoncpp/include PRIVATE)
add_subdirectory(src)


# Test
add_executable(
    test_blidanmaku
    test/test_blidanmaku.cpp
    ${BLI_JSONCPP_SOURCE_DIR}
)
