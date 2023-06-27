#include <filesystem>
#include <fstream>

#include <yaml-cpp/yaml.h>

class BackupTarget {
  public:
    std::filesystem::path path;
    std::string category;

  BackupTarget(std::filesystem::path path, std::string category) {
    this->path     = path;
    this->category = category;
  }

  void backup(std::filesystem::path backup_root) {
    auto current_time             = std::chrono::system_clock::now();
    std::time_t current_time_t    = std::chrono::system_clock::to_time_t(current_time);

    std::tm* current_tm = std::localtime(&current_time_t);
    int year  = current_tm->tm_year + 1900;
    int month = current_tm->tm_mon;

    auto destination_path = backup_root / std::to_string(year)
      / std::to_string(month)
      / category
      / path.filename();

    std::filesystem::create_directories(destination_path);
    std::filesystem::copy(path, destination_path, std::filesystem::copy_options::recursive);
  }
};

int main() {
  std::string home = std::getenv("HOME");

  std::ifstream fin(home + "/.config/backuptool.conf");
  auto config = YAML::Load(fin);

  auto general          = config["general"];
  auto target_categorys = config["backup"];

  std::string backup_root_path_string     = general["backup-root-path"].as<std::string>();
  std::filesystem::path backup_root_path  = std::filesystem::path(backup_root_path_string);
  for (const auto target : target_categorys) {
    std::string category       = target.first.as<std::string>();
    std::string path_string    = target.second.as<std::string>();

    std::filesystem::path path = std::filesystem::path(path_string);

    BackupTarget backupTarget(path, category);
    backupTarget.backup(backup_root_path);
  }
}
