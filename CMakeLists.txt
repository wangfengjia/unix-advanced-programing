cmake_minimum_required(VERSION 3.17)
project(unix_advanced_programing C)

set(CMAKE_C_STANDARD 99)

add_executable(unix_advanced_programing main.c)

##第一章
add_executable(first_chapter_test first-chapter/first_chapter_test.c)
add_executable(non_cache_io first-chapter/non_cache_io.c include/apue.h lib/error.c)
add_executable(cache_io first-chapter/cache_io.c include/apue.h lib/error.c)
add_executable(process first-chapter/process.c include/apue.h lib/error.c)
add_executable(signal_s first-chapter/signal.c include/apue.h lib/error.c)

##第三章
add_executable(file third-chapter/file.c include/apue.h lib/error.c)
add_executable(copy_file third-chapter/copy_file.c include/apue.h lib/error.c)