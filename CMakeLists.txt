cmake_minimum_required(VERSION 3.24)
project(persistentQueue)

set(CMAKE_CXX_STANDARD 17)

add_executable(persistentQueue main.cpp Node.h PersistentStack.h PersistentQueue.h)
