#ifndef EX_RUNNER_H
#define EX_RUNNER_H

#include "lib/command/runner/command_runner.h"
#include "lib/mode/mode_manager.h"
#include "lib/buffer/file_manager.h"
#include "lib/window/window.h"
#include "lib/statusbar/root_status.h"
#include "lib/history/history_manager.h"

// takes a completed Ex command and 
// - applies multiplier by repeatedly inserting text into the buffer
class ExRunner: public CommandRunner<Ex>{
  Window*& activeWindow;
  ModeManager& modeManager;
  RootStatus& rootStatus;
  FileManager& fileManager;
  HistoryManager& historyManager;

  bool write(const std::vector<std::string>& args);

  // whether to enable or disable multifile
  bool multifile = false;

 public:
  void run(const Ex*) override;
  ExRunner(Window*& activeWindow, ModeManager& modeManager, 
    RootStatus& rootStatus, FileManager& fileManager, 
    HistoryManager& historyManager): 
    activeWindow{activeWindow}, modeManager{modeManager}, 
    rootStatus{rootStatus}, fileManager{fileManager}, 
    historyManager{historyManager}
  {}
};

#endif

