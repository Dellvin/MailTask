cmake_minimum_required(VERSION 3.10)
project(MailTask)

find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -Wall -Wextra -Werror=pedantic")

enable_testing()

add_executable(MailTask project/src/client/main.cpp project/src/client/ui.cpp
        project/src/server/main.cpp project/src/server/server.cpp project/src/server/room/room.cpp project/src/server/session/session.cpp)

target_link_libraries(MailTask Threads::Threads)

add_subdirectory(project/tests)
add_subdirectory(project/src/server)
add_subdirectory(project/src/client)
