#include <backuptool.hpp>

backuptool::config::config() {
    string home = getenv("HOME");
    ifstream possible_streams[] {
      ifstream(home + "/.config/backuptool.conf"),
      ifstream(home + ".backuptool.conf")
    };
    
    if(possible_streams[0].is_open()) {
      this->yaml = YAML::Load(possible_streams[0]);
    } else if(possible_streams[1].is_open()) {
      this->yaml = YAML::Load(possible_streams[1]);
    }
  }

filesystem::path backuptool::config::backup_root_path() {
    string spath = this->yaml["general"]["backup-root-path"].as<string>();
    return filesystem::path(spath);
  }

vector<target> backuptool::config::targets() {
  vector<target> targets;

  for(auto target: this->yaml["backup"]) {
    std::stringstream paths(target.second.as<std::string>());
    std::string path_s;

    while(paths >> path_s) {
      std::filesystem::path path(path_s);

      targets.push_back({target.first.as<string>(), path});
    }
  }

  return targets;
}
