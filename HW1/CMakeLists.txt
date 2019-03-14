#
# rpn/CMakeLists.txt --
#

cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(rpn VERSION 0.4.0 LANGUAGES C)

set(CMAKE_CXX_FLAGS "-g -O0 -Wall -lpthread -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-g -O0 -Wall -lpthread -W -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

find_package(Threads)
find_package(PkgConfig)

if(CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-Wall -Werror)
endif(CMAKE_COMPILER_IS_GNUCC)

add_executable(main main.c)

target_link_libraries(main rpn rpn-stack
        ${CHECK_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT})

add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME misc COMMAND check-rpn)
