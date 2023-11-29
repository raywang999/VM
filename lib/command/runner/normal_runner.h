#ifndef NORMAL_RUNNER_H
#define NORMAL_RUNNER_H

#include <string>

#include "lib/command/parser/normal_parser.h"
#include "lib/command/runner/command_runner.h"
#include "lib/window/window.h"
#include "lib/mode/normal_mode.h"
#include "lib/command/parser/insert_parser.h"

// takes a basic Normal mode Command and runs it
class NormalRunner: public CommandRunner<Normal>{
  Window*& activeWindow;
  NormalMode& theNormalMode;
  InsertParser& insertParser;
 public:
  // the command must be one of a,cc,dd,i,o,p,r,s,u,x,yy,A,I,J,O,P,R,S,X,.
  void run(const Normal* normal); 
  NormalRunner(Window*& activeWindow, NormalMode& normalMode, InsertParser& insertParser): 
    activeWindow{activeWindow}, theNormalMode{normalMode}, insertParser{insertParser} {}
};

#endif

