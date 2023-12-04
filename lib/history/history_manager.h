#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include <unordered_map>
#include <unordered_set>

#include "lib/statusbar/root_status.h"
#include "history_tree.h"
#include "lib/command/runner/command_runner.h"

// pushes commands onto the history tree of the currently edited file
class HistoryManager: 
  public CommandRunner<Ex>,
  public CommandRunner<Insert>,
  public CommandRunner<Replace>,
  public CommandRunner<Macro>,
  public CommandRunner<Normal>
{
  Window*& activeWindow;
  RootStatus& rootStatus;
  std::unordered_map<std::string, HistoryTree> trees;
  // number of modifications from last persist
  std::unordered_map<std::string, int> diffCnt; 

 public:
  HistoryManager(Window*& activeWindow, RootStatus& rootStatus): 
    activeWindow{activeWindow}, rootStatus{rootStatus} {}
  // save changes into the tree of the currently active file
  void save() {
    auto& tab = activeWindow->getTabManager().curr();
    const auto& filename = tab.getFilebuf().filename;
    if (trees.count(filename)){
      trees.at(filename).push(tab);
      ++diffCnt[filename];
    } else {
      trees.insert({filename, HistoryTree{tab}});
    }
  }
  void run(const Insert* cmd) override { save(); }
  void run(const Replace* cmd) override { save(); }
  void run(const Macro* cmd) override { 
    if (cmd->type == '@') save();
  }
  void run(const Normal* cmd) override { 
    // note, we don't consider undo and redo as modifications 
    // since nromalRunner should handle them
    static const std::unordered_set<char> modifiers{'x','X','d','.','J','p','P'};
    if (modifiers.count(cmd->type)) save();
  }
  void run(const Ex* ex) override { 
    if (ex->args[0] == "r") {save();}
  }
  // get the diff cnt of a file from its last persist
  void setDiffCnt(const std::string& filename, int cnt=0) { 
    diffCnt[filename] = cnt; 
  }
  // get the diff cnt of a file from its last persist
  int getDiffCnt(const std::string& filename) { 
    return diffCnt[filename];
  }

  // redo in currently active window
  void redo() {
    auto& tab = activeWindow->getTabManager().curr();
    const auto& filename = tab.getFilebuf().getFilename();
    auto& tree = trees.at(filename);
    ++diffCnt[filename];
    if (tree.redo()){
      tree.sync(tab);
    }
  }
  
  // undo last change in currently active window
  void undo() {
    auto& tab = activeWindow->getTabManager().curr();
    const auto& filename = tab.getFilebuf().getFilename();
    auto& tree = trees.at(filename);
    --diffCnt[filename];
    if (tree.undo()){
      tree.sync(tab);
    }
  }

  // copies history from source file to `to` file, assuming `to` isn't opened 
  void copy(const std::string& from, const std::string& to) {
    trees.insert({to,trees.at(from)});
    diffCnt[to]=diffCnt[from];
  }

};

#endif