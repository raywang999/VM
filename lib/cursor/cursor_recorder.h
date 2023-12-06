#ifndef CURSOR_RECORDER_H
#define CURSOR_RECORDER_H

#include "lib/window/window.h"
#include "lib/history/history_manager.h"
#include "lib/command/runner/command_runner.h"
#include "lib/command/runner/normal_runner.h"

class CursorRecorder: 
  public CommandRunner<Insert>,
  public CommandRunner<Normal>,
  public CommandRunner<Command>
{
  Window*& activeWindow;
  HistoryManager& historyManager;
  Cursor cursor;
  void update() { cursor = activeWindow->getTabManager().curr().getCursor(); }
 public:
  CursorRecorder(Window*& activeWindow, HistoryManager& historyManager): 
    activeWindow{activeWindow}, historyManager{historyManager} {}
  
  // if Insert, the cursor should return to how it was before the insert
  void run(const Insert* cmd) override { }
  // save cursor
  void run(const Normal* cmd) override { 
    switch(cmd->type){
      case 'a': break;
      case 'i': break;
      case 'A': break;
      default: update();
    }
  }
  // if Insert, the cursor should return to how it was before the insert
  void run(const Command* cmd) override { update(); }
  const Cursor& getCursor() const noexcept {return cursor; }
};

#endif