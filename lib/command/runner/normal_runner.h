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
  ModeManager& modeManager;
  InsertParser& insertParser;
  ExParser& exParser;
  MovementRunner movementRunner{activeWindow};

 public:
  // the command must be one of a,cc,dd,i,o,p,r,s,u,x,yy,A,I,J,O,P,R,S,X,.
  void run(const Normal* normal); 
  NormalRunner(
    Window*& activeWindow, 
    ModeManager& modeManager, 
    InsertParser& insertParser,
    ExParser& exParser
  ): 
    activeWindow{activeWindow}, 
    modeManager{modeManager}, 
    insertParser{insertParser}, 
    exParser{exParser} 
  {}
};

#endif

