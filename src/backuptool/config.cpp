#include <backuptool.hpp>
#include <fstream>

using namespace std;

int backuptool::config::get_user_config(backuptool::config *config) noexcept {
  string home = getenv("HOME");
  ifstream config_stream(home + "/.config/backuptool.conf");

  if (config_stream.is_open()) {
    auto yaml = YAML::Load(config_stream);

    try {
      config->backup_root_path =
          yaml["general"]["backup-root-path"].as<string>();
    } catch (YAML::BadConversion) {
      return backuptool::config::BACKUP_ROOT_PATH_IS_NOT_DEFINED;
    }

    try {
      auto targets = yaml["backup"];

      for (auto target : targets) {
        string category = target.first.as<string>();
        filesystem::path target_root_path = target.second.as<string>();

        config->targets.push_back(::target(category, target_root_path));
      }
    } catch (YAML::BadConversion) {
      return backuptool::config::BACKUP_HAS_NO_TARGETS;
    }
  }

  return 0;
}
