#ifndef INSERT_RUNNER_H
#define INSERT_RUNNER_H

#include <string>

#include "lib/command/runner/command_runner.h"
#include "lib/mode/mode_manager.h"
#include "lib/window/window.h"

// takes a completed Insert command and 
// - applies multiplier by repeatedly inserting text into the buffer
class InsertRunner: public CommandRunner<Insert>{
  Window*& activeWindow;
  ModeManager& modeManager;
 public:
  // handle insert command from user typing
  void notify(const CommandSource<Insert>& source) override {
    auto command = Insert{*source.getCommand()};
    if (command.count == -1) {
      command.count = 1;
    }
    // the user already typed a copy of the insert, so only need to run count-1
    --command.count;
    run(&command);
  }
  void run(const Insert*) override;
  InsertRunner(Window*& activeWindow, ModeManager& modeManager): 
    activeWindow{activeWindow}, modeManager{modeManager} {}
};

#endif

