#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

#include "yaml-cpp/yaml.h"

using namespace std;

namespace backuptool {
  class config {
  private:
  YAML::Node yaml;

  public:
  config() {
    string home = getenv("HOME");
    filesystem::path config_path(home + "/.config/backuptool.conf");
    ifstream config_stream(config_path);

    this->yaml = YAML::Load(config_stream);
  }

  filesystem::path backup_root_path() {
    string spath = this->yaml["general"]["backup-root-path"].as<string>();
    return filesystem::path(spath);
  }
  };
}

int main() {
  cout << backuptool::config().backup_root_path() << endl;
}
