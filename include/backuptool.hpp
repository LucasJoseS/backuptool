#ifndef BACKUPTOOL
#define BACKUPTOOL
#include <cstdint>
#include <filesystem>
#include <yaml-cpp/yaml.h>

class target {
public:
  target *childs;
  std::string category;
  std::filesystem::path root_path;

  target(std::string category, std::filesystem::path root_path) {
    this->category = category;
    this->root_path = root_path;
  }
};

namespace backuptool {
class config {
private:
  YAML::Node node;

public:
  std::filesystem::path config_root_path;
  std::filesystem::path backup_root_path;
  std::vector<target> targets;

  config();
  ~config();
  void add_target(std::string category, std::filesystem::path root_path);
  int static get_user_config(config *) noexcept;
};
} // namespace backuptool

namespace backuptool::backup {
void local_backup(target target, std::filesystem::path backup_root_path);
} // namespace backuptool::backup
#endif
