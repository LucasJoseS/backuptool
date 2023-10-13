#include <backuptool.hpp>
#include <filesystem>
#include <fstream>
#include <map>

using namespace std;

class ConfigError {
public:
  ConfigError(const string &msg) : msg_(msg) {}
  ~ConfigError() {}

  string getMessage() const { return msg_; }

private:
  string msg_;
};

backuptool::config::config() {
  filesystem::path config_root_path = getenv("HOME");
  config_root_path += "/.config/backuptool.conf";

  ifstream config_stream(config_root_path);

  node = YAML::Load(config_stream);
  backup_root_path = node["general"]["backup-root-path"].as<string>();

  auto targets = node["backup"];
  for (auto current : targets) {
    string category = current.first.as<string>();
    filesystem::path target_root_path = current.second.as<string>();

    this->targets.push_back(target(category, target_root_path));
  }
}

backuptool::config::~config() {
  ofstream config_stream(config_root_path);

  string yaml_text = YAML::Dump(node);
  config_stream.write(yaml_text.c_str(), yaml_text.size());
}
