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
    int month = current_tm->tm_mon  + 1;

    auto destination_path = backup_root / std::to_string(year)
      / std::to_string(month)
      / category
      / path.filename();

    std::filesystem::create_directories(destination_path);

    const auto options = std::filesystem::copy_options::skip_existing
                       | std::filesystem::copy_options::recursive
                       ;

    std::filesystem::copy(path, destination_path, options);
  }
};

int main() {
  std::string home = std::getenv("HOME");

  std::ifstream fin(home + "/.config/backuptool.conf");
  auto config = YAML::Load(fin);

  auto general          = config["general"];
  auto target_categorys = config["backup"];

  std::filesystem::path backup_root_path(general["backup-root-path"].as<std::string>());
  for(auto target: target_categorys) {
    std::stringstream paths(target.second.as<std::string>());
    std::string path_s;

    while(paths >> path_s) {
      std::filesystem::path path(path_s);

      BackupTarget backup(path, target.first.as<std::string>());
      backup.backup(backup_root_path);
    }
  }
}
