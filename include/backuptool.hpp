#ifndef BACKUPTOOL
#define BACKUPTOOL
#include <cstdint>
#include <filesystem>
#include <yaml-cpp/yaml.h>

class target {
public:
  std::filesystem::path root_path;
  std::string category;

  target(const std::string category, const std::filesystem::path root_path) {
    this->category = category;
    this->root_path = root_path;
  }

  std::vector<std::filesystem::path> childs();
};

namespace backuptool {
class config {
public:
  const static int8_t BACKUP_ROOT_PATH_IS_NOT_DEFINED = 1;
  const static int8_t BACKUP_HAS_NO_TARGETS = 2;

  std::filesystem::path backup_root_path;
  std::vector<target> targets;

  int static get_user_config(config *) noexcept;
};
} // namespace backuptool

namespace backuptool::backup {
void local_backup(target target, std::filesystem::path backup_root_path);
} // namespace backuptool::backup
#endif
