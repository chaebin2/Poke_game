cmake_minimum_required(VERSION 3.20)
project(PokeGame C)

set(CMAKE_C_STANDARD 99)

# ✅ 명확하게 경로 설정
set(MYSQL_ROOT "C:/Users/서민경/Desktop/MySQL/mysql-connector-c-6.1.11")
set(MYSQL_INCLUDE_DIR "${MYSQL_ROOT}/include")
set(MYSQL_LIB_DIR "${MYSQL_ROOT}/lib/vs14")

include_directories(${MYSQL_INCLUDE_DIR})
link_directories(${MYSQL_LIB_DIR})


# 프로젝트 헤더 경로
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/backend_c/include)

# DAO 라이브러리 정의
add_library(dao
    backend_c/src/dao_pokemon.c
    backend_c/src/dao_player.c
    backend_c/src/battle.c
    backend_c/src/shop.c
    backend_c/src/player.c
)

# poke_game 실행파일
add_executable(poke_game 
    backend_c/main.c
    backend_c/src/playerQueue.c
    backend_c/src/db.c
    backend_c/src/player.c
    backend_c/src/shop.c
    backend_c/src/battle.c
    backend_c/src/dao_player.c
    backend_c/src/dao_pokemon.c
)

# test용 실행파일
add_executable(test_dao test/test_dao.c)

# 라이브러리 링크 (mysqlclient 사용!)
target_link_libraries(dao PRIVATE mysqlclient)
target_link_libraries(poke_game PRIVATE dao mysqlclient)
target_link_libraries(test_dao PRIVATE dao mysqlclient)

# 실행파일 출력 디렉토리 설정
set_target_properties(poke_game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
