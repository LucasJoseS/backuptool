#include <backuptool.hpp>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


string target_t::get_data(filesystem::path file_path) {
  fstream fs(file_path);
  stringstream sstream;

  if (fs) {
    sstream << fs.rdbuf();
    fs.close();

    return sstream.str();
  }

  throw runtime_error("root path not exists or is a directory. ( " +
                      std::string(file_path) + " )");
}

size_t target_t::get_hash(filesystem::path file_path) {
  string data = target_t::get_data(file_path);

  return std::hash<string>{}(data);
};

size_t target_t::get_hash(target_t &target) {
  return get_hash(target.root_path);
}

vector<filesystem::path> get_childs_r(filesystem::path root_path) {
  vector<filesystem::path> childs;

  for (auto child: filesystem::directory_iterator(root_path)) {
    childs.push_back(child);

    if (child.is_directory()) {
      auto aux = get_childs_r(child);

      childs.insert(childs.end(), aux.begin(), aux.end());
    }
  }

  return childs;
}

vector<filesystem::path> target_t::get_childs(target_t &target) {
  if (target.childs.empty()) {
    target.childs = get_childs_r(target.root_path);
  }

  return target.childs;
}
