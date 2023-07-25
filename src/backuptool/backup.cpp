#include <backuptool.hpp>

#define OPTIONS                                                                \
  std::filesystem::copy_options::skip_existing |                               \
      std::filesystem::copy_options::recursive

std::tm *currentLocaltime() {
  auto current_time = std::chrono::system_clock::now();
  std::time_t current_time_t =
      std::chrono::system_clock::to_time_t(current_time);

  return std::localtime(&current_time_t);
}

std::filesystem::path destinationPath(std::tm *time, target target,
                                      filesystem::path backup_root_path) {
  int year = time->tm_year + 1900;
  int month = time->tm_mon + 1;
  int day = time->tm_mday;

  return backup_root_path / std::to_string(year) / std::to_string(month) /
         std::to_string(day) / target.category / target.path.filename();
}

int backuptool::backup::simpleBackup(target target,
                                     filesystem::path backup_root_path) {
  auto time = currentLocaltime();
  auto destination_path = destinationPath(time, target, backup_root_path);

  std::filesystem::create_directories(destination_path);
  std::filesystem::copy(target.path, destination_path, OPTIONS);
  return true;
}
