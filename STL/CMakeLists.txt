cmake_minimum_required(VERSION 2.8)

project(STL)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -g -Wall -O0 -Wno-unused-variable -pthread")

set(forward_list
forward_list.cc
)

set(list
list.cc
)

set(lambdaState
lambdaState.cc
)

add_executable(forward_lisd ${forward_list})

add_executable(list ${list})

add_executable(lambdaState ${lambdaState})

