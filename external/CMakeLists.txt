add_subdirectory(yaml-cpp)
include_directories(yaml-cpp/include)
find_library(yaml-cpp STATIC yaml-cpp)
