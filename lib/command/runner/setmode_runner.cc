#include "setmode_runner.h"
#include "include/utility.h"

void SetModeRunner::run(const SetMode* cmd){
  auto& tab = activeWindow->getTabManager().curr();
  auto& filebuf = tab.getFilebuf();
  auto cursor = tab.getCursor();
  int count = normalizeCount(cmd->count);
  // if file is empty, add a first line 
  if (filebuf.countLines() == 0) {
    filebuf.insertLines(0,1);
  } 
  if (cmd->type == ':'){ // enter ex mode
    exParser.reset();
    modeManager.setMode(ModeType::Ex);
  } else if (cmd->type == 'R') { // enter Replace mode
  } else { // enter insert mode
    if (cmd->type == 'i'){ /*enter insert mode without doing anything*/ }
    else if (cmd->type == 'a'){
      // if not empty line, move cursor right
      if (filebuf.getLine(cursor.getRow()).size() > 1){
        cursor.setCol(cursor.getCol()+1);
        tab.setCursor(cursor);
      }
    } else if (cmd->type == 'o'){ // insert new line, move cursor down
      filebuf.insertLines(cursor.getRow()+1,1);
      cursor.translate(cursor.getRow()+1, 0);
      tab.setCursor(cursor);
    } else if (cmd->type == 'O'){ // insert new line above, move cursor up
      filebuf.insertLines(cursor.getRow(),1);
      cursor.setCol(0);
      tab.setCursor(cursor);
    } else if (cmd->type == 'A'){ // turns into running a $ movement, then a
      Movement toEnd{1,'$'};
      movementRunner.run(&toEnd);
      cursor.setCol(filebuf.getLine(cursor.getRow()).size()-1);
      tab.setCursor(cursor);
    } else if (cmd->type == 'S'){ // delete line, then i
      filebuf.eraseLines(cursor.getRow(),1);
      filebuf.insertLines(cursor.getRow(), 1);
      cursor.setCol(0);
      tab.setCursor(cursor);
    } else if (cmd->type == 'c'){ // CM command. Run DM(M) then enter insert
      auto cm = dynamic_cast<const CM*>(cmd);
      movementRunner.run(&cm->movement);
    }
    // enter insert mode
    insertParser.reset();
    insertParser.setCount(cmd->count);
    insertParser.setMode(cmd->type);
    modeManager.setMode(ModeType::Insert);
  }
  // clear the rootStatus message 
  rootStatus.reset();
}
