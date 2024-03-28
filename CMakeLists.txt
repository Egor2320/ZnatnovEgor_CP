cmake_minimum_required(VERSION 3.24)
project(persistentQueue)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(persistentQueue main.cpp Except.cpp)
