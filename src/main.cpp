#define OBX_CPP_FILE

#include <iostream>
#include <backuptool.hpp>
#include <objectbox.h>
#include <objectbox-model.h>
#include <object.obx.hpp>

using namespace std;

int main() {
  backuptool::config config;
  backuptool::config::get_user_config(&config);

  cout << "Using backup-root-path: " << config.backup_root_path << endl << endl;

  for (target actual_target : config.targets) {
    cout << "saving:  " << actual_target.category << endl;
    cout << "in path: " << actual_target.root_path << endl;

    backuptool::backup::local_backup(actual_target, config.backup_root_path);
  }
}
