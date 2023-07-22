#include <backuptool.hpp>

std::tm *currentLocaltime() {
  auto current_time = std::chrono::system_clock::now();
  std::time_t current_time_t =
      std::chrono::system_clock::to_time_t(current_time);

  return std::localtime(&current_time_t);
}

int backuptool::backup::simpleBackup(target target,
                                     filesystem::path backup_root_path) {
  auto current_tm = currentLocaltime();

  int year = current_tm->tm_year + 1900;
  int month = current_tm->tm_mon + 1;
  int day = current_tm->tm_mday;

  auto destination_path = backup_root_path / std::to_string(year) /
                          std::to_string(month) / std::to_string(day) /
                          target.category / target.path.filename();

  std::filesystem::create_directories(destination_path);

  const auto options = std::filesystem::copy_options::skip_existing |
                       std::filesystem::copy_options::recursive;

  std::filesystem::copy(target.path, destination_path, options);
  return true;
}
