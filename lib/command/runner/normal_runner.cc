#include <unordered_map>
#include <functional>

#include "include/utility.h"
#include "normal_runner.h"

void NormalRunner::run(const Normal* cmd){
  // runner functions 
  using Func = std::function<void(NormalRunner*)>;

  // functions to handle commands that go to insert mode
  // i.e. i,o,O,a,A,s,S,cc,I
  static const std::unordered_map<char,Func> insertDispatch {
    {'i', [](NormalRunner*){}}, // just set mode to insert
    {'a', [](NormalRunner* obj){ // move cursor right, then insert. Unless empty line
      auto& tab = obj->activeWindow->getTabManager().curr();
      auto cursor = tab.getCursor();
      if (tab.getFilebuf().getLine(cursor.getRow()).size() > 1){
        // not empty line, move cursor right
        cursor.setCol(cursor.getCol()+1);
        tab.setCursor(cursor);
      }
    }},
    {'o', [](NormalRunner* obj){ // insert new line, move cursor down
      auto& tab = obj->activeWindow->getTabManager().curr();
      auto cursor = tab.getCursor();
      tab.getFilebuf().insertLines(cursor.getRow()+1,1);
      cursor.translate(cursor.getRow()+1, 0);
      tab.setCursor(cursor);
    }},
    {'O', [](NormalRunner* obj){ // insert new line above, move cursor up
      auto& tab = obj->activeWindow->getTabManager().curr();
      auto cursor = tab.getCursor();
      tab.getFilebuf().insertLines(cursor.getRow(),1);
      cursor.setCol(0);
      tab.setCursor(cursor);
    }},
    {'A', [](NormalRunner* obj){ // turns into running a $ movement, then a
      Movement toEnd{1,'$'};
      obj->movementRunner.run(&toEnd);
      auto& tab = obj->activeWindow->getTabManager().curr();
      auto cursor = tab.getCursor();
      cursor.setCol(tab.getFilebuf().getLine(cursor.getRow()).size()-1);
      tab.setCursor(cursor);
    }}, 
    {'S', [](NormalRunner* obj){ // same as cc
      auto& tab = obj->activeWindow->getTabManager().curr();
      auto cursor = tab.getCursor();
      cursor.setCol(tab.getFilebuf().getLine(cursor.getRow()).size()-1);
      tab.setCursor(cursor);
    }}
  };
  auto& tab = activeWindow->getTabManager().curr();
  auto& filebuf = tab.getFilebuf();
  auto cursor = tab.getCursor();
  auto curRow = cursor.getRow();
  auto curCol = cursor.getCol();
  int count = normalizeCount(cmd->count);

  if (insertDispatch.count(cmd->type)){ 
    // switch to insert mode
    insertDispatch.at(cmd->type)(this); 
    insertParser.reset();
    insertParser.setCount(count);
    insertParser.setMode(cmd->type);
    modeManager.setMode(ModeType::Insert);
    activeWindow->render();
    rootStatus.reset();
  } else if (cmd->type == ':'){
    exParser.reset();
    modeManager.setMode(ModeType::Ex);
  } else if (cmd->type == 'x'){
    filebuf.erase(curRow,curCol,count);
    tab.fixCursor();
  } else if (cmd->type == 'X'){
    auto delCnt = min(count,curCol);
    filebuf.erase(curRow,curCol - delCnt, delCnt);
    cursor.setCol(curCol-delCnt);
    tab.setCursor(cursor);
  } else if (cmd->type == 'd'){
    // run dd command
  } else {

  }
}
