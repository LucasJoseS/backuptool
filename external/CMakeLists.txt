add_subdirectory(yaml-cpp)

include_directories(yaml-cpp)
find_library(yaml-cpp STATIC ./yaml-cpp)
