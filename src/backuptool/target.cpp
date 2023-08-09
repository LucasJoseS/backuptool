#include <backuptool.hpp>
#include <filesystem>
#include <fstream>

using namespace std;

string get_data(filesystem::path file_path) {
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

size_t target::hash() {
  if (filesystem::is_directory(this->root_path)) {
    return std::hash<string>{}(this->root_path.string());
  }

  return std::hash<string>{}(get_data(this->root_path));
};

vector<target> target::childs() {
  if (this->childs_cache.empty()) {
    vector<filesystem::path> dirs = { this->root_path };

    while (!dirs.empty()) {
      auto childs = filesystem::directory_iterator(dirs.back());
      dirs.pop_back();

      for (auto child : childs) {
        if (filesystem::is_directory(child)) {
          dirs.push_back(child);
        }

        this->childs_cache.push_back(target(this->category, child));
      }
    }
  }

  return this->childs_cache;
}
