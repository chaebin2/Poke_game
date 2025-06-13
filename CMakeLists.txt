cmake_minimum_required(VERSION 3.20)
project(PokeGame C)

# 헤더 경로
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/backend_c/include)

# src/ 아래 모든 .c 자동 수집  ← 한 줄이면 끝
file(GLOB_RECURSE SRC_FILES backend_c/src/*.c)

add_executable(poke_game backend_c/main.c ${SRC_FILES})

set_target_properties(poke_game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)