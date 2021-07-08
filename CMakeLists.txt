cmake_minimum_required(VERSION 3.19)
project(W12Lab)

set(CMAKE_CXX_STANDARD 14)

add_executable(W12Lab main.cpp message.h messages.h control.h interact.h message.cpp messages.cpp interact.cpp lab12.cpp)