#ifndef NORMAL_RUNNER_H
#define NORMAL_RUNNER_H


#include "lib/command/parser/normal_parser.h"
#include "lib/command/runner/command_runner.h"
#include "lib/window/window.h"
#include "lib/command/parser/insert_parser.h"
#include "lib/mode/mode_manager.h"
#include "lib/command/runner/movement_runner.h"
#include "lib/command/parser/ex_parser.h"

// takes a basic Normal mode Command and runs it
class NormalRunner: public CommandRunner<Normal>{
  Window*& activeWindow;
  // helps with e.g. 
  //MovementRunner movementRunner{activeWindow};

 public:
  // the command must be one of dd,p,r,x,yy,J,P,X
  // note: '.' is handled by DotRepeater
  void run(const Normal* normal); 
  NormalRunner(
    Window*& activeWindow
  ): 
    activeWindow{activeWindow}
  {}
};

#endif

