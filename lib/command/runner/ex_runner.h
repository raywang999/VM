#ifndef EX_RUNNER_H
#define EX_RUNNER_H

#include "lib/command/runner/command_runner.h"
#include "lib/window/window.h"

// takes a completed Ex command and 
// - applies multiplier by repeatedly inserting text into the buffer
class ExRunner: public CommandRunner<Ex>{
  Window*& activeWindow;
  
 public:
  void run(const Ex*) override;
  ExRunner(Window*& activeWindow): activeWindow{activeWindow} {}
};

#endif

