#include <backuptool.hpp>
#include <iostream>

using namespace std;

int main() {
  auto config = backuptool::config::get_user_config();
  cout << "Using backup-root-path: " << config.root_path << endl << endl;

  for (target_t actual_target : config.targets) {
    cout << "saving:  " << actual_target.category << endl;
    cout << "in path: " << actual_target.root_path << endl;

    backuptool::backup::simple_backup(actual_target, config.root_path);
  }
}
