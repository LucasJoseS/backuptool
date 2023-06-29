cmake_minimum_required(VERSION 3.20)

project(BackupTool CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS=true)

add_subdirectory(external)

add_executable(BackupTool backuptool.cpp)
target_link_libraries(BackupTool yaml-cpp)
