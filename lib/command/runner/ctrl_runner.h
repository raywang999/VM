#ifndef CTRL_RUNNER_H
#define CTRL_RUNNER_H

#include <math.h>

#include "lib/command/runner/movement_runner.h"
#include "lib/command/runner/command_runner.h"
#include "lib/window/window.h"
#include "lib/statusbar/root_status.h"
#include "lib/history/history_manager.h"

// takes a basic Ctrl mode Command and runs it
class CtrlRunner: public CommandRunner<Ctrl>{
  Window*& activeWindow;
  RootStatus& rootStatus;
  HistoryManager& historyManager;

  // initial amount to scroll in Ctrl u, Ctrl d to half screen height
  int scroll = activeWindow->getHeight() / 2;

  // helpers

  std::string printFilename() const;
  std::string printCursor() const;
  std::string printLineCount() const;
  std::string printFileStatus();

 public:
  // the movement must be a Ctrl with letter f,d,u,g,b
  void run(const Ctrl* cmd); 
  CtrlRunner(Window*& activeWindow, RootStatus& rootStatus, HistoryManager& historyManager): 
    activeWindow{activeWindow}, rootStatus{rootStatus}, historyManager{historyManager} { }
};

#endif

