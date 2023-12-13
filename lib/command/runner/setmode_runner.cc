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
    modeManager.setMode(ModeType::Ex);
  } else if (cmd->type == 'R') { // enter Replace mode
    replaceParser.reset();
    replaceParser.setCount(count);
    modeManager.setMode(ModeType::Replace);
  } else if (cmd->type == '?' || cmd->type == '/'){
    modeManager.setMode(ModeType::Search);
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
    } else if (cmd->type == 'I'){
      const auto& line = filebuf.getLine(cursor.getRow());
      size_t col = 0;
      while (col+1 < line.size() && isspace(line[col])){ 
        ++col;
      }
      cursor.setCol(col);
      tab.setCursor(cursor);
    } else if (cmd->type == 'A'){ // turns into running a $ movement, then a
      cursor.setCol(filebuf.getLine(cursor.getRow()).size()-1);
      tab.setCursor(cursor);
    } else if (cmd->type == 'S' || cmd->type == 'c' || cmd->type == 's'){ 
      // run ComboNM command to delete into clipboard, then enter insert
      ComboNM tmp;
      tmp.normal = {1,'d'};
      if (cmd->type == 'S'){ // for S, delete count lines
        tmp.movement = {count,'d'};
      } else if (cmd->type == 's') { // for s, delete count to right
        tmp.movement = {count,'l'};
      } else { // for c_Movement, run the movement
        tmp.movement = dynamic_cast<const CM&>(*cmd).movement;
        tmp.normal.count = count;
      }
      comboNMRunner.run(&tmp);
      count = 1; // don't duplicate inserts
    } 
    // enter insert mode
    insertParser.reset();
    insertParser.setCount(count);
    insertParser.setMode(cmd->type);
    modeManager.setMode(ModeType::Insert);
  }
  // clear the rootStatus message 
  rootStatus.reset();
}
