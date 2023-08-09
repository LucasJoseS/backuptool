#ifndef BACKUPTOOL
#define BACKUPTOOL
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <map>
#include <vector>
#include <yaml-cpp/yaml.h>

class target {
private:
  std::vector<target> childs_cache;

public:
  std::filesystem::path root_path;
  std::string category;

  target(const std::string category, const std::filesystem::path root_path) {
    this->category = category;
    this->root_path = root_path;
  }

  std::size_t hash();
  std::vector<target> childs();
};

typedef struct {
  std::filesystem::path backup_root_path;
  std::vector<target> targets;
} config_t;

namespace backuptool::config {
config_t get_user_config();
}

namespace backuptool::backup {
int simple_backup(target target, std::filesystem::path backup_root_path);
int object_backup(target target, std::filesystem::path backup_root_path);
} // namespace backuptool::backup
#endif
