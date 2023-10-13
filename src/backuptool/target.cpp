#include <algorithm>
#include <backuptool.hpp>
#include <cstdlib>
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

/*
vector<filesystem::path> target::childs() {
  vector<filesystem::path> buff;
  vector<filesystem::path> dirs = {this->root_path};

  while (!dirs.empty()) {
    auto childs = filesystem::directory_iterator(dirs.back());
    dirs.pop_back();

    for (auto child : childs) {
      if (filesystem::is_directory(child)) {
        dirs.push_back(child);
      }

      buff.push_back(child);
    }
  }

  sort(buff.begin(), buff.end());
  return buff;
}
*/
