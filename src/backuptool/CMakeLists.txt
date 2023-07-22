add_library(backup STATIC
  config.cpp
  backup.cpp
  )

target_include_directories(backup PUBLIC
  ../../include/
  )

target_link_libraries(backup yaml-cpp)
