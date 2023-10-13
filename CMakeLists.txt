cmake_minimum_required(VERSION 3.5)

project(Backup-Toolkit CXX)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

add_subdirectory(src)
add_executable(backuptool src/main.cpp)

FetchContent_Declare (
  objectbox
  GIT_REPOSITORY  https://github.com/objectbox/objectbox-c.git
  GIT_TAG         v0.18.0
)

FetchContent_Declare (
  yaml-cpp
  GIT_REPOSITORY  https://github.com/jbeder/yaml-cpp.git
  GIT_TAG         0.8.0
)

FetchContent_Declare (
  cli11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_TAG        v2.3.2 
)

FetchContent_MakeAvailable(objectbox)
FetchContent_MakeAvailable(yaml-cpp)
FetchContent_MakeAvailable(cli11)

target_include_directories(backup
  PUBLIC include
  PUBLIC src/object
  )

target_link_libraries(backuptool
  backup
)
