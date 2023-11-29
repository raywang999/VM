#ifndef MACRO_RUNNER_H
#define MACRO_RUNNER_H

#include "lib/command/runner/command_runner.h"
#include "lib/window/window.h"

// takes a basic Macro mode Command and runs it
class MacroRunner: public CommandRunner<Macro>{
  Window*& activeWindow;

 public:
  // the movement must be a Macro + 
  void run(const Macro* macro); 
  MacroRunner(Window*& activeWindow): 
    activeWindow{activeWindow}{}
};

#endif

