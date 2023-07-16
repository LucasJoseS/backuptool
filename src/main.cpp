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

#include "./config.cpp"

int main() {
  auto config = backuptool::config();

  auto targets = config.targets();
  for(auto target: targets) {
    BackupTarget btarget(target.path, target.category);

    btarget.backup(config.backup_root_path() / "test");
  }
}
