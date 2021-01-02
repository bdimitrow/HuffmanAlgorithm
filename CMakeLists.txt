cmake_minimum_required(VERSION 3.17)
project(HuffmanAlgorithm)

set(CMAKE_CXX_STANDARD 20)

add_executable(HuffmanAlgorithm main.cpp tree.cpp tree.h fileUtils.h stringUtils.h menu.h)