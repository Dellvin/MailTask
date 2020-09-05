cmake_minimum_required(VERSION 3.10)
project(iz2)

find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -Wall -Wextra -Werror=pedantic")

enable_testing()

include_directories(project/include)
add_library(staticLib STATIC project/src/IZ2_STATIC.c)
add_library(dynamicLib SHARED project/src/libIZ2_dymamic.c)
target_link_libraries(dynamicLib -lpthread)

add_executable(iz2 project/src/main.c)

target_link_libraries(iz2 Threads::Threads)
target_link_libraries(iz2 staticLib dynamicLib)

add_subdirectory(project/tests)


