#ifndef UNDO_RUNNER_H
#define UNDO_RUNNER_H


#include "lib/command/runner/command_runner.h"
#include "lib/window/window.h"
#include "lib/mode/mode_manager.h"
#include "lib/history/history_manager.h"
#include "lib/statusbar/root_status.h"

// only runs u and Ctrl-R commands
class UndoRunner: 
  public CommandRunner<Normal>,
  public CommandRunner<Ctrl>
{
  Window*& activeWindow;
  ModeManager& modeManager;
  HistoryManager& historyManager;
  RootStatus& rootStatus;

 public:
  void run(const Normal* normal) override; 
  void run(const Ctrl* ctrl) override;
  UndoRunner(
    Window*& activeWindow, 
    ModeManager& modeManager, 
    HistoryManager& historyManager,
    RootStatus& rootStatus
  ): 
    activeWindow{activeWindow}, 
    modeManager{modeManager}, 
    historyManager{historyManager},
    rootStatus{rootStatus}
  {}
};

#endif

