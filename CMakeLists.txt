cmake_minimum_required(VERSION 3.8)
project(RMLIB)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Servers/ServerActive.cpp Servers/ServerPasive.cpp Servers/list.cpp Servers/list.h Servers/node.cpp Servers/node.h)
add_executable(RMLIB ${SOURCE_FILES})
