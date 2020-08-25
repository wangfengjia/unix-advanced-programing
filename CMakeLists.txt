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

##第四章
add_executable(stat forth-chapter/stat.c include/apue.h lib/error.c)
add_executable(chmod forth-chapter/chmod.c include/apue.h lib/error.c)
add_executable(link forth-chapter/link.c include/apue.h lib/error.c)
add_executable(unlink forth-chapter/unlink.c include/apue.h lib/error.c)
add_executable(rename forth-chapter/rename.c include/apue.h lib/error.c)
add_executable(symlink forth-chapter/symlink.c include/apue.h lib/error.c)
add_executable(file_time forth-chapter/file_time.c include/apue.h lib/error.c)
add_executable(futimens forth-chapter/futimens.c include/apue.h lib/error.c)
add_executable(mkdir forth-chapter/make_dir.c include/apue.h lib/error.c)
add_executable(chdir forth-chapter/chdir.c include/apue.h lib/error.c)
add_executable(getcwd forth-chapter/getcwd.c include/apue.h lib/error.c lib/pathalloc.c)

##第五章
add_executable(buffer fifth-chapter/buffer.c include/apue.h lib/error.c)
add_executable(fopen fifth-chapter/fopen.c include/apue.h lib/error.c)
add_executable(byte_io fifth-chapter/byte_io.c include/apue.h lib/error.c)
add_executable(line_io fifth-chapter/line_io.c include/apue.h lib/error.c)
add_executable(binary_io fifth-chapter/binary_io.c include/apue.h lib/error.c)
add_executable(stream_pos fifth-chapter/stream_position.c include/apue.h lib/error.c)
add_executable(format_io fifth-chapter/format_io.c include/apue.h lib/error.c)
add_executable(stream_info fifth-chapter/stream_info.c include/apue.h lib/error.c)
add_executable(tmpfile fifth-chapter/tmpfile.c include/apue.h lib/error.c)
add_executable(mkstemp fifth-chapter/mkstemp.c include/apue.h lib/error.c)
add_executable(memory_stream fifth-chapter/memory_stream.c include/apue.h lib/error.c)

##第六章
add_executable(getpwuid sixth-chapter/getpwuid.c include/apue.h lib/error.c)
add_executable(group sixth-chapter/group.c include/apue.h lib/error.c)
add_executable(supplement_group sixth-chapter/supplement_group.c include/apue.h lib/error.c)
add_executable(system_identity sixth-chapter/system_identity.c include/apue.h lib/error.c)
add_executable(time sixth-chapter/time.c include/apue.h lib/error.c)
add_executable(time_format sixth-chapter/time_format.c include/apue.h lib/error.c)

##第七章
add_executable(exit_handler seventh-chapter/exit_handler.c include/apue.h lib/error.c)
add_executable(env_table seventh-chapter/env_table.c include/apue.h lib/error.c)
add_executable(resource_limit seventh-chapter/process_resource_limit.c include/apue.h lib/error.c)

##第八章
add_executable(processid eighth-chapter/processid.c include/apue.h lib/error.c)
add_executable(fork eighth-chapter/fork.c include/apue.h lib/error.c)
add_executable(exit eighth-chapter/exit.c include/apue.h lib/error.c)
add_executable(wait eighth-chapter/wait.c include/apue.h lib/error.c eighth-chapter/pr_exit.h eighth-chapter/pr_exit.c)
add_executable(waitpid eighth-chapter/waitpid.c include/apue.h lib/error.c eighth-chapter/pr_exit.h eighth-chapter/pr_exit.c)
add_executable(zombie_process eighth-chapter/zombie_process.c include/apue.h lib/error.c)
add_executable(waitid eighth-chapter/waitid.c include/apue.h lib/error.c eighth-chapter/pr_exit.h eighth-chapter/pr_exit.c)
add_executable(competition eighth-chapter/competition.c include/apue.h lib/error.c)
add_executable(exec eighth-chapter/exec.c include/apue.h lib/error.c)
add_executable(process_user eighth-chapter/process_user.c include/apue.h lib/error.c)
add_executable(intepre eighth-chapter/interpreter_file.c include/apue.h lib/error.c)
add_executable(system eighth-chapter/system.c include/my_apue.h lib/print_exit.c lib/system_implement.c include/apue.h lib/error.c)
add_executable(process_accounting_test eighth-chapter/process_accounting_test.c include/apue.h lib/error.c)
add_executable(login_name eighth-chapter/login_name.c include/apue.h lib/error.c)
add_executable(dispatch eighth-chapter/process_dispatch.c include/apue.h lib/error.c)
add_executable(process_time eighth-chapter/process_time.c include/apue.h lib/error.c)

##第九章
add_executable(process_group ninth-chapter/process_group.c include/apue.h lib/error.c)
add_executable(process_session ninth-chapter/process_session.c include/apue.h lib/error.c)
add_executable(front_process_group ninth-chapter/front_process_group.c include/apue.h lib/error.c)
add_executable(orphan_process ninth-chapter/orphan_process.c include/apue.h lib/error.c)













