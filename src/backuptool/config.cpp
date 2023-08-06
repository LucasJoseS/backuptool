#include <backuptool.hpp>
#include <fstream>

using namespace std;

config_t backuptool::config::get_user_config() {
  config_t config;
  string home = getenv("HOME");
  ifstream config_stream(home + "/.config/backuptool.conf");

  if (config_stream.is_open()) {
    auto yaml = YAML::Load(config_stream);

    config.root_path = yaml["general"]["backup-root-path"].as<string>();
    for (auto target: yaml["backup"]) {
      string category   = target.first.as<string>();
      filesystem::path target_root_path = target.second.as<string>();

      config.targets.push_back(target_t{ category, target_root_path });
    }

    return config;
  }

  exit(1);
}
