#ifndef NORMAL_RUNNER_H
#define NORMAL_RUNNER_H

#include <unordered_map>
#include <functional>

#include "lib/command/parser/normal_parser.h"
#include "lib/command/runner/command_runner.h"
#include "lib/window/window.h"
#include "lib/command/parser/insert_parser.h"
#include "lib/mode/mode_manager.h"

// takes a basic Normal mode Command and runs it
class NormalRunner: public CommandRunner<Normal>{
  Window*& activeWindow;
  ModeManager& modeManager;
  InsertParser& insertParser;

  // runner functions 
  using Func = std::function<void(NormalRunner*)>;

  // functions to handle commands that go to insert mode
  // i.e. i,o,O,a,A,s,S,cc,I
  inline static const std::unordered_map<char,Func> insertDispatch {
    {'i', [](NormalRunner*){}}, // just set mode to insert
    {'a', [](NormalRunner* obj){ // move cursor right, then insert. Unless empty line
      auto& tab = obj->activeWindow->getTabManager().curr();
      auto& cursor = tab.getCursor();
      if (tab.getFilebuf().getLine(cursor.getRow()).size() > 1){
        cursor.setCol(cursor.getCol()+1);
      }
    }},
    {'o', [](NormalRunner* obj){ // insert new line, move cursor down
      auto& tab = obj->activeWindow->getTabManager().curr();
      auto& cursor = tab.getCursor();
      tab.getFilebuf().insertLines(cursor.getRow()+1,1);
      cursor.translate(cursor.getRow()+1, 0);
    }},
    {'O', [](NormalRunner* obj){ // insert new line above, move cursor up
      auto& tab = obj->activeWindow->getTabManager().curr();
      auto& cursor = tab.getCursor();
      tab.getFilebuf().insertLines(cursor.getRow(),1);
      cursor.setCol(0);
    }} 
  };

 public:
  // the command must be one of a,cc,dd,i,o,p,r,s,u,x,yy,A,I,J,O,P,R,S,X,.
  void run(const Normal* normal); 
  NormalRunner(Window*& activeWindow, ModeManager& modeManager, InsertParser& insertParser): 
    activeWindow{activeWindow}, modeManager{modeManager}, insertParser{insertParser} {}
};

#endif

