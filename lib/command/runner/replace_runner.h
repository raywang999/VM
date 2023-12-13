#ifndef REPLACE_RUNNER_H
#define REPLACE_RUNNER_H

#include <string>

#include "lib/command/runner/command_runner.h"
#include "lib/mode/mode_manager.h"
#include "lib/window/window.h"

// takes a completed Replace command and 
// - applies multiplier by repeatedly inserting text into the buffer
class ReplaceRunner: public CommandRunner<Replace>{
  Window*& activeWindow;
  ModeManager& modeManager;
 public:
  // handle insert command from user typing
  void notify(const CommandSource<Replace>& source) override {
    auto command = Replace{*source.getCommand()};
    if (command.count == -1) {
      command.count = 1;
    }
    // the user already typed a copy of the replace, so only need to run count-1
    --command.count;
    run(&command);
  }
  void run(const Replace*) override;
  ReplaceRunner(Window*& activeWindow, ModeManager& modeManager): 
    activeWindow{activeWindow}, modeManager{modeManager} {}
};

#endif

