#ifndef MOVEMENT_RUNNER_H
#define MOVEMENT_RUNNER_H

#include "lib/command/runner/command_runner.h"
#include "lib/window/window.h"

// takes a basic Movement mode Command and runs it
class MovementRunner: public CommandRunner<Movement>{
  Window*& activeWindow;
  // the previous position of the cursor's column 
  // used when jumping lines with different column sizes
  // only changed when a non-Ctrl command, and non j,k command is run 
  int prevCursorCol=0;
  bool usePrev = true;

 public:
  // tell next movement not to use the previous cursor col
  void unsetPrev() noexcept {usePrev = false;}
  // the movement must be one of bfhjklnwFN^$0%;
  void run(const Movement* movement); 
  MovementRunner(Window*& activeWindow): 
    activeWindow{activeWindow}{}
};

#endif

