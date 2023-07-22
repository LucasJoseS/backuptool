cmake_minimum_required(VERSION 3.20)

project(Backup-Toolkit CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external)
add_subdirectory(src)

add_executable(backuptool src/main.cpp)

target_link_libraries(backuptool
  yaml-cpp
  backup
  )
