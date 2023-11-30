cmake_minimum_required(VERSION 3.5)

project(peer-review-second LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(peer-review-second main.cpp)

install(TARGETS peer-review-second
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
