#include <string>
#include <algorithm>

#include "include/utility.h"
#include "insert_runner.h"

void InsertRunner::run(const Insert* insert){
  int count = normalizeCount(insert->count);
  std::string theInsert = insert->sentence;
  auto& tab = activeWindow->getTabManager().curr();
  auto& filebuf = tab.getFilebuf();
  auto cursor = tab.getCursor();
  if (count > 0 ){
    if (insert->mode == 'o' || insert->mode == 'O') {
      // play inserts with newlines
      if (insert->mode == 'o'){
        cursor.setRow(cursor.getRow()+1);
      }
      filebuf.insertLines(cursor.getRow(),count);
      for (int i=0; i < count; ++i){
        filebuf.insert(cursor.getRow()+i, 0, theInsert);
      }
      // calculate cursor row from 'o' and 'O' commands
      cursor.setRow(cursor.getRow()+count-1);
    } else {
      // play the inserts without newlines
      for (int i=1; i < count; ++i) {
        theInsert += insert->sentence;
      }
      filebuf.insert(cursor.getRow(), cursor.getCol(), theInsert);
    } 
    // calculate final cursor position
    cursor.setRow(cursor.getRow()+count*std::ranges::count(theInsert,'\n'));
    cursor.setCol(fit(0,filebuf.getLine(cursor.getRow()).size()-1,
      cursor.getCol()+theInsert.size()));
  }
  // move cursor left one col 
  cursor.setCol(std::max(0,cursor.getCol()-1));
  tab.setCursor(cursor);
  modeManager.setMode(ModeType::Normal);
}

