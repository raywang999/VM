#ifndef CTRL_RUNNER_H
#define CTRL_RUNNER_H

#include "lib/command/runner/movement_runner.h"
#include "lib/command/runner/command_runner.h"
#include "lib/window/window.h"

// takes a basic Ctrl mode Command and runs it
class CtrlRunner: public CommandRunner<Ctrl>{
  Window*& activeWindow;
  MovementRunner& movementRunner;

 public:
  // the movement must be a Ctrl + 
  void run(const Ctrl* movement); 
  CtrlRunner(Window*& activeWindow, MovementRunner& movementRunner): 
    activeWindow{activeWindow}, movementRunner{movementRunner} {}
};

#endif

