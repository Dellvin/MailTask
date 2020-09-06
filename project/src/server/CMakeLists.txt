cmake_minimum_required(VERSION 3.10)
project(SERVER)

enable_testing()

add_executable(SERVER main.cpp server.cpp room/room.cpp session/session.cpp)

target_link_libraries(SERVER Threads::Threads)
