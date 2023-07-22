#ifndef BACKUPTOOL
#define BACKUPTOOL
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

using namespace std;

typedef struct {
  string category;
  filesystem::path path;
} target;

namespace backuptool {
class config {
private:
  YAML::Node yaml;

public:
  config();
  filesystem::path backup_root_path();
  vector<target> targets();
};

namespace backup {
int simpleBackup(target target, filesystem::path backup_root_path);
} // namespace backup
} // namespace backuptool
#endif // !BACKUPTOOL
