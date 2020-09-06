cmake_minimum_required(VERSION 3.10)
project(iz2)

find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -Wall -Wextra -Werror=pedantic")

enable_testing()

add_executable(iz2 project/src/client/main.cpp project/src/client/ui.cpp)

target_link_libraries(iz2 Threads::Threads)

add_subdirectory(project/tests)


