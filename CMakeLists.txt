cmake_minimum_required(VERSION 3.17)
project(unix_advanced_programing C)

set(CMAKE_C_STANDARD 99)

add_executable(unix_advanced_programing main.c)

##第一章
add_executable(first_chapter_test first-chapter/first_chapter_test.c)
add_executable(non_cache_io first-chapter/non_cache_io.c include/apue.h lib/error.c)
add_executable(cache_io first-chapter/cache_io.c include/apue.h lib/error.c)