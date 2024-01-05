cmake_minimum_required(VERSION 3.27)
project(ReadXml)

set(CMAKE_CXX_STANDARD 17)

add_executable(ReadXml main.cpp
        lib/pugiconfig.hpp)
