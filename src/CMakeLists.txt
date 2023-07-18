add_library(backup-tool STATIC
  config.cpp
  backup.cpp
  )

target_include_directories(backup-tool PUBLIC
  ../include
  )

target_link_libraries(backup-tool yaml-cpp)
