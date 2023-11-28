#ifndef NORMAL_RUNNER_H
#define NORMAL_RUNNER_H

#include <string>

#include "lib/command/parser/normal_parser.h"
#include "lib/command/runner/command_runner.h"
#include "lib/window/window.h"
#include "lib/mode/normal_mode.h"

// takes a basic Normal mode Command and runs it
class NormalRunner: public CommandRunner{
  Window*& activeWindow;
  NormalParser& theParser;
  NormalMode& theNormalMode;
  // we got a basic normal command parsed to run 
  // the command must be one of a,cc,dd,i,o,p,r,s,u,x,yy,A,I,J,O,P,R,S,X,.
  void notify(const Subject<Command*>&) override {
    Normal normal = *theParser.getCommand();
    auto& tab = activeWindow->getTabManager().curr();
    auto& filebuf = tab.getFilebuf();
    auto& cursor = tab.getCursor();
    if (normal.type == 'i') { // entery insert mode
      theNormalMode.setMode(ModeType::Insert);
      return theNormalMode.notifyAll();
    }
  }
 public:
  NormalRunner(Window*& activeWindow, NormalParser& parser, NormalMode& normalMode): 
    activeWindow{activeWindow}, theParser{parser}, theNormalMode{normalMode} {}
};

#endif

