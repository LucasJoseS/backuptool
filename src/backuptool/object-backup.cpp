#include <backuptool.hpp>
#include <iostream>

vector<filesystem::path> targetTree(filesystem::path target) {
  vector<filesystem::path> tree;
  if(target.filename().string()[0] == '.') { return tree; }

  tree.push_back(target);
  for(auto actual: filesystem::directory_iterator(target)) {
    tree.push_back(actual);

    if(actual.is_directory()) {
      auto subtree = targetTree(actual);
      tree.insert(tree.end(), subtree.begin(), subtree.end());
    }
  }

  return tree;
}

int backuptool::backup::objectBackup(target target, filesystem::path backup_root_path) {
  auto objects_path = backup_root_path / "objects";
  filesystem::create_directories(objects_path);

  for(auto tree: targetTree(target.path)) {
    cout << tree << endl;
  }
  cout << endl;

  return true;
}
