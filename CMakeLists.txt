cmake_minimum_required(VERSION 3.20)
project(PokeGame C)

# MySQL 헤더 먼저 추가!
include_directories("C:/mysql/mysql-connector-c-6.1.11/include")
link_directories("C:/mysql/mysql-connector-c-6.1.11/lib/vs14")

# 프로젝트 헤더 경로
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/backend_c/include)

# DAO 라이브러리
add_library(dao
    backend_c/src/dao_pokemon.c
    backend_c/src/dao_player.c
    backend_c/src/battle.c
    backend_c/src/shop.c
    backend_c/src/player.c
)
# 여기 중요! → dao 타겟에 MySQL 포함 경로 명시
target_include_directories(dao PRIVATE ${MYSQL_INCLUDE_DIR})
target_include_directories(dao PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/backend_c/include)
target_link_libraries(dao PRIVATE mysqlclient)
# poke_game 실행파일
add_executable(poke_game 
    backend_c/main.c
    backend_c/src/playerQueue.c
    backend_c/src/db.c
)
target_link_libraries(poke_game PRIVATE dao mysqlclient)

# test_dao 실행파일
add_executable(test_dao test/test_dao.c)
target_link_libraries(test_dao PRIVATE dao mysqlclient)

# 실행 파일 출력 디렉터리 통일
set_target_properties(poke_game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set_target_properties(test_dao PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
