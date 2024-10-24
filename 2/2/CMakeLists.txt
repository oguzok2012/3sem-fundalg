cmake_minimum_required(VERSION 3.10)

project(app)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(app src/responses.c src/utils.c src/repo.c src/main.c)

target_link_libraries(app m)
