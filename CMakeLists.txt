cmake_minimum_required(VERSION 3.16)
project(huffman_coding_tree)

set(CMAKE_CXX_STANDARD 17)

add_executable(huffman_coding_tree main.cpp main.h minHeap.h Request.h)
