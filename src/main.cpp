#include <backuptool.hpp>

int main() {
  auto config = backuptool::config();

  auto targets = config.targets();
  for (target actual : targets) {
    backuptool::backup::simpleBackup(actual, config.backup_root_path());
  }
}
