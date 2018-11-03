cmake_minimum_required(VERSION 3.12)
project(LexLab)

set(CMAKE_CXX_STANDARD 14)

add_executable(LexLab main.cpp include/Global.h source/RECompiler.cpp include/RECompiler.h source/NFA.cpp include/NFA.h source/DFA.cpp include/DFA.h)