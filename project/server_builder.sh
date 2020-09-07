#!/bin/bash

g++ -Wall -g -c -std=c++17 ./src/server/main.cpp
g++ -Wall -g -c -std=c++17 ./src/server/server.cpp
g++ -Wall -g -c -std=c++17 ./src/server/session/session.cpp
g++ -Wall -g -c -std=c++17 ./src/server/room/room.cpp

g++ main.o server.o session.o room.o -lpthread -o server

rm *.o
