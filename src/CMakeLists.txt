cmake_minimum_required(VERSION 3.0)

aux_source_directory(. BLI_SRC_ROOT_DIR)

add_library(
    BliLiveDanmaku
    ${BLI_SRC_ROOT_DIR}
)


target_include_directories(
    BliLiveDanmaku
    PUBLIC
    ../include/libBliLiveDanmaku
)
