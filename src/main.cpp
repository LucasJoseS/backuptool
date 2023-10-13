#include <CLI/CLI.hpp>
#include <backuptool.hpp>
#include <filesystem>
#include <iostream>
#include <string>

using namespace std;

static backuptool::config CONFIG;

void backup(target t) {
  cout << "Using backup-root-path: " << CONFIG.backup_root_path << endl << endl;

  cout << "saving:  " << t.category << endl;
  cout << "in path: " << t.root_path << endl;

  backuptool::backup::local_backup(t, CONFIG.backup_root_path);
}

void backup(string categoty, filesystem::path t_path) {
  backup(target(categoty, t_path));
}

void backup() {
  for (target t : CONFIG.targets) {
    backup(t);
  }
}

void commands(CLI::App *app) {
  auto sbackup = app->add_subcommand("backup", "Execute a backup");
  auto sconfig = app->add_subcommand("config", "Config manipulation");

  sbackup->callback([&]() { backup(); });

  auto sctarget = sconfig->add_subcommand("target", "Target manipulation");

  string target_path;
  sctarget->add_option("--add", target_path, "Add a target")->type_name("path");
}

int main(int argc, char **argv) {
  CLI::App app{"A backup toolkit"};
  app.require_subcommand(true);

  commands(&app);

  CLI11_PARSE(app, argc, argv);
}
