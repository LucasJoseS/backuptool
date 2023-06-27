cmake_minimum_required(VERSION 3.20)

project(backuptool)

find_package(yaml-cpp REQUIRED)

add_executable(backuptool backuptool.cpp)
target_link_libraries(backuptool PUBLIC yaml-cpp)
