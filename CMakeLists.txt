cmake_minimum_required(VERSION 3.0)

project(BliLiveDanmaku)

aux_source_directory(jsoncpp/lib_json BLI_JSONCPP_SOURCE_DIR)
aux_source_directory(zlib/src BLI_ZLIB_SOURCE_DIR)
aux_source_directory(src BLI_DANMAKU_SRC_DIR)

include_directories(PUBLIC format)
include_directories(PUBLIC jsoncpp/include)
include_directories(PUBLIC zlib/include)

# Library
add_library(
    BliLiveDanmaku
    ${BLI_DANMAKU_SRC_DIR}
    ${BLI_JSONCPP_SOURCE_DIR}
)


target_include_directories(
    BliLiveDanmaku
    PRIVATE
    include/libBliLiveDanmaku
)


# Test
add_executable(
    test_blidanmaku
    test/test_blidanmaku.cpp
    ${BLI_JSONCPP_SOURCE_DIR}
    ${BLI_DANMAKU_SRC_DIR}
)

target_include_directories(
    test_blidanmaku
    PUBLIC
    include/libBliLiveDanmaku
)
