add_library(backup-lib
  backuptool/backup.cpp
  backuptool/config.cpp
  backuptool/target.cpp

  object/object.obx.cpp
  )

target_link_libraries(backup-lib
  yaml-cpp
  objectbox
  )
