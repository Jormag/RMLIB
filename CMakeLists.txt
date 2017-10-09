cmake_minimum_required(VERSION 3.8)
project(RMLIB)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Servers/Servers.cpp Servers/linkedList.cpp Servers/linkedList.h Servers/node.cpp Servers/node.h Servers/Memory.cpp Servers/Memory.h RMLIB.h Servers/rmRef_h.cpp Servers/rmRef_h.h)
add_executable(RMLIB ${SOURCE_FILES} main.cpp)
