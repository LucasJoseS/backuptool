#include <backuptool.hpp>
#include <filesystem>
#include <fstream>

using namespace std;

#define OPTIONS                                                                \
  std::filesystem::copy_options::skip_existing |                               \
      std::filesystem::copy_options::recursive

std::tm *current_localtime();
vector<filesystem::path> list_childrens_files(filesystem::path root_path);
filesystem::path destination_path(std::tm *time, target target,
                                  filesystem::path backup_root_path);


int backuptool::backup::simple_backup(target target,
                                      filesystem::path backup_root_path) {
  auto time = current_localtime();
  auto dest_path = destination_path(time, target, backup_root_path);

  std::filesystem::create_directories(dest_path);
  std::filesystem::copy(target.root_path, dest_path, OPTIONS);
  return true;
}

int backuptool::backup::object_backup(target target,
                                      std::filesystem::path backup_root_path) {
  auto objects_path = backup_root_path / ".backup" / "objects";
  ofstream category_map = objects_path / to_string((size_t) 0);

  string category_hash = to_string(hash<string>{}(target.category));
  category_map << category_hash;

  ofstream category_object_file = objects_path / category_hash;
  category_object_file << target.hash();

  ofstream target_map = objects_path / to_string(target.hash());

  return true;
}

std::tm *current_localtime() {
  auto current_time = std::chrono::system_clock::now();
  std::time_t current_time_t =
      std::chrono::system_clock::to_time_t(current_time);

  return std::localtime(&current_time_t);
}

filesystem::path destination_path(std::tm *time, target target,
                                  filesystem::path backup_root_path) {
  int year = time->tm_year + 1900;
  int month = time->tm_mon + 1;
  int day = time->tm_mday;

  return backup_root_path / std::to_string(year) / std::to_string(month) /
         std::to_string(day) / target.category / target.root_path.filename();
}

vector<filesystem::path> list_childrens_files(filesystem::path parrent) {
  vector<filesystem::path> childrens;

  for (auto children : filesystem::directory_iterator(parrent)) {
    if (children.is_directory()) {
      auto sub = list_childrens_files(children);
      childrens.insert(childrens.end(), sub.begin(), sub.end());
      continue;
    }

    childrens.push_back(children);
  }

  return childrens;
}
