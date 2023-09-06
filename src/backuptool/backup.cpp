#include <backuptool.hpp>
#include <filesystem>
#include <fstream>

using namespace std;

#define OPTIONS                                                                \
  std::filesystem::copy_options::skip_existing |                               \
      std::filesystem::copy_options::recursive

std::tm *current_localtime();
filesystem::path destination_path(std::tm *time, target target,
                                  filesystem::path backup_root_path);

void backuptool::backup::local_backup(target target,
                                       filesystem::path backup_root_path) {
  auto time = current_localtime();
  auto dest_path = destination_path(time, target, backup_root_path);

  std::filesystem::create_directories(dest_path);
  std::filesystem::copy(target.root_path, dest_path, OPTIONS);
}

std::tm *current_localtime() {
  auto current_time = std::chrono::system_clock::now();
  std::time_t current_time_t =
      std::chrono::system_clock::to_time_t(current_time);

  auto localtime = std::localtime(&current_time_t);
  localtime->tm_year += 1900;
  localtime->tm_mon += 1;

  return localtime;
}

filesystem::path destination_path(std::tm *time, target target,
                                  filesystem::path backup_root_path) {
  int year = time->tm_year;
  int month = time->tm_mon;
  int day = time->tm_mday;

  return backup_root_path / std::to_string(year) / std::to_string(month) /
         std::to_string(day) / target.category / target.root_path.filename();
}
