cmake_minimum_required(VERSION 3.0)

project(BliLiveDanmaku)
option(BLI_EMB_JSONCPP "Embed jsoncpp" OFF)
if (NOT DEFINED BLI_EMB_JSONCPP)
    set(BLI_EMB_JSONCPP OFF)
endif()

aux_source_directory(jsoncpp/lib_json BLI_JSONCPP_SOURCE_DIR)
aux_source_directory(src BLI_DANMAKU_SRC_DIR)

include_directories(format)
include_directories(jsoncpp/include)
include_directories(zstr/src)

link_libraries(z)

# Library
if (BLI_EMB_JSONCPP STREQUAL "ON")
    add_library(
        BliLiveDanmaku
        ${BLI_DANMAKU_SRC_DIR}
        ${BLI_JSONCPP_SOURCE_DIR}
    )
else()
    add_library(
        BliLiveDanmaku
        ${BLI_DANMAKU_SRC_DIR}
    )
endif()


target_include_directories(
    BliLiveDanmaku
    PRIVATE
    include/libBliLiveDanmaku
)

set(CMAKE_INSTALL_PREFIX build)

install(TARGETS BliLiveDanmaku
    EXPORT BliLiveDanmaku-targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(
    DIRECTORY
        include/libBliLiveDanmaku
    DESTINATION
        include
)

install(EXPORT BliLiveDanmaku-targets
    NAMESPACE BliLiveDanmaku::
    FILE BliLiveDanmaku-config.cmake
    DESTINATION cmake
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
