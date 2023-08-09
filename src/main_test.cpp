#include <backuptool.hpp>
#include <filesystem>
#include <iostream>

using namespace std;

int main() {
  auto config = backuptool::config::get_user_config();
  cout << "Using backup-root-path: " << config.backup_root_path << endl << endl;

  for (target actual_target : config.targets) {
    cout << "saving:  " << actual_target.category << endl;
    cout << "in path: " << actual_target.root_path << endl;

    backuptool::backup::object_backup(actual_target, config.backup_root_path);
  }
}
