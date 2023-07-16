#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

#include "yaml-cpp/yaml.h"

using namespace std;

struct target{
  string            category;
  filesystem::path  path;
};

namespace backuptool {
  class config {
  private:
  YAML::Node yaml;

  public:
  config() {
    string home = getenv("HOME");
    ifstream config_stream(home + "/.config/backuptool.conf");

    this->yaml = YAML::Load(config_stream);
  }

  filesystem::path backup_root_path() {
    string spath = this->yaml["general"]["backup-root-path"].as<string>();
    return filesystem::path(spath);
  }

  vector<struct target> targets() {
    vector<struct target> targets;

    for(auto target: this->yaml["backup"]) {
      std::stringstream paths(target.second.as<std::string>());
      std::string path_s;

      while(paths >> path_s) {
        std::filesystem::path path(path_s);

        targets.push_back({target.first.as<string>(), path});
      }
    }

    return targets;
  }
  };
}
