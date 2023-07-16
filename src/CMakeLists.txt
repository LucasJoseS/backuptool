add_library(backup-tool STATIC
  config.cpp
  )

target_link_libraries(backup-tool yaml-cpp)
