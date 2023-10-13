add_library(backup
  backuptool/backup.cpp
  backuptool/config.cpp
  backuptool/target.cpp

  object/object.obx.cpp
  )

target_link_libraries(backup
  yaml-cpp
  objectbox
  CLI11
  )
