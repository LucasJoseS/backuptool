#ifndef BACKUPTOOL
#define BACKUPTOOL
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>

#include <yaml-cpp/yaml.h>

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
  config();
  filesystem::path backup_root_path();
  vector<struct target> targets();
  };

  namespace backup {
      int simpleBackup(struct target target, filesystem::path backup_root_path);
  }
}
#endif // !BACKUPTOOL
