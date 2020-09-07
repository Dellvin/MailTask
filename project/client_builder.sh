#!/bin/bash

g++ -Wall -g -c -std=c++17 ./src/client/main.cpp
g++ -Wall -g -c -std=c++17 ./src/client/ui.cpp

g++ main.o ui.o -o client

rm *.o
