#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include <unordered_map>
#include <unordered_set>

#include "history_tree.h"

// pushes commands onto the history tree of the currently edited file
class HistoryManager{
  std::unordered_map<std::string, HistoryTree> trees;
  // number of the edit which was last written 
  std::unordered_map<std::string, int> savedEdit; 

 public:
  // save changes into the tree of the given tab
  void save(const Tab& tab, const Cursor& beg) {
    const auto& filename = tab.getFilebuf().filename;
    if (trees.count(filename)){
      trees.at(filename).push(tab, beg);
    } else {
      trees.insert({filename, HistoryTree{tab}});
      savedEdit[filename] = 0;
    }
  }

  // redo in a file. Returns true iff successful
  bool redo(const std::string& filename) {
    auto& tree = trees.at(filename);
    if (tree.redo()){
      return true;
    }
    return false;
  }
  
  // undo in a file. Returns true iff successful
  bool undo(const std::string& filename) {
    auto& tree = trees.at(filename);
    if (tree.undo()){
      return true;
    }
    return false;
  }

  // copies history from source file to `to` file, assuming `to` isn't opened 
  void copy(const std::string& from, const std::string& to) {
    trees.insert({to,trees.at(from)});
    savedEdit[from] = savedEdit[to];
  }

  const HistoryTree& getTree(const std::string& file) const {
    return trees.at(file);
  }

  int getSavedEdit(const std::string& file) {return savedEdit[file];}
  void persist(const std::string& file) {savedEdit[file] = trees.at(file).getCurr();}

};

#endif