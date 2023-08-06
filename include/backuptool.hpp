#ifndef BACKUPTOOL
#define BACKUPTOOL
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <map>
#include <vector>
#include <yaml-cpp/yaml.h>

typedef struct target_t {
  std::string category;
  std::filesystem::path root_path;
  std::vector<std::filesystem::path> childs;

  static std::vector<std::filesystem::path> get_childs(target_t &);
  static std::size_t get_hash(target_t &);
  static std::size_t get_hash(std::filesystem::path);
  static std::string get_data(std::filesystem::path);
} target_t;

typedef struct {
  std::filesystem::path root_path;
  std::vector<target_t> targets;
} config_t;

namespace backuptool::config {
config_t get_user_config();
}
namespace backuptool::backup {
int simple_backup(target_t target, std::filesystem::path backup_root_path);
int object_backup(target_t target, std::filesystem::path backup_root_path);
} // namespace backuptool::backup
#endif
