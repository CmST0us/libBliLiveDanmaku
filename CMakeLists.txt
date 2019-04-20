cmake_minimum_required(VERSION 3.0)

project(BliLiveDanmaku)

aux_source_directory(jsoncpp/lib_json BLI_JSONCPP_SOURCE_DIR)
aux_source_directory(src BLI_DANMAKU_SRC_DIR)

include_directories(format)
include_directories(jsoncpp/include)
include_directories(zstr/src)
link_libraries(z)

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
