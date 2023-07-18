#include <backuptool.hpp>

#include "./config.cpp"
#include "./backup.cpp"

int main() {
  auto config = backuptool::config();

  auto targets = config.targets();
  for(auto target: targets) {
    struct target btarget {target.category, target.path};

    backuptool::backup::simpleBackup(btarget, config.backup_root_path() / "test");
  }
}
