#ifndef HISTORY_RECORDER_H
#define HISTORY_RECORDER_H

#include <unordered_map>
#include <unordered_set>

#include "lib/statusbar/root_status.h"
#include "lib/window/window.h"
#include "lib/history/history_manager.h"
#include "lib/command/runner/command_runner.h"
#include "lib/cursor/cursor_recorder.h"

// pushes commands onto the history tree of the currently edited file
class HistoryRecorder: 
  public CommandRunner<Ex>,
  public CommandRunner<Insert>,
  public CommandRunner<Replace>,
  public CommandRunner<ComboNM>,
  public CommandRunner<Macro>,
  public CommandRunner<Normal>
{
  Window*& activeWindow;
  HistoryManager& historyManager;
  CursorRecorder& cursorRecorder;
  std::unordered_map<std::string, HistoryTree> trees;
  // number of modifications from last persist
  std::unordered_map<std::string, int> diffCnt; 

 public:
  HistoryRecorder(Window*& activeWindow, HistoryManager& historyManager, CursorRecorder& cursorRecorder): 
    activeWindow{activeWindow}, historyManager{historyManager}, cursorRecorder{cursorRecorder} {}
  // save change into tree of currently active file
  void save() { 
    historyManager.save(activeWindow->getTabManager().curr(), cursorRecorder.getCursor()); 
  }
  void run(const Insert* ) override { save(); }
  void run(const Replace* ) override { save(); }
  void run(const ComboNM* cmd) override {
    if (cmd->normal.type != 'y') save();
  }
  void run(const Macro* cmd) override { 
    if (cmd->type == '@') save();
  }
  void run(const Normal* cmd) override { 
    // note, we don't consider undo and redo as modifications 
    if (cmd->type != 'u') save();
  }
  void run(const Ex* ex) override { 
    if (ex->args[0] == "r") {save();}
  }
};

#endif