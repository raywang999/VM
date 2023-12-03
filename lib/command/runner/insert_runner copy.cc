#include <string>

#include "include/utility.h"
#include "insert_runner.h"

void InsertRunner::run(const Insert* insert){
  std::string theInsert = insert->sentence;
  auto& tab = activeWindow->getTabManager().curr();
  auto& filebuf = tab.getFilebuf();
  auto cursor = tab.getCursor();
  if (insert->count > 0 ){
    if (insert->mode == 'o' || insert->mode == 'O') {
      // play inserts with newlines
      if (insert->mode == 'o'){
        cursor.setRow(cursor.getRow()+1);
      }
      filebuf.insertLines(cursor.getRow(),insert->count);
      for (int i=0; i < insert->count; ++i){
        filebuf.insert(cursor.getRow()+i, 0, theInsert);
      }
      cursor.translate(cursor.getRow()+insert->count-1, theInsert.size());
    } else {
      // play the inserts without newlines
      for (int i=1; i < insert->count; ++i) {
        theInsert += insert->sentence;
      }
      filebuf.insert(cursor.getRow(), cursor.getCol(), theInsert);
      cursor.setCol(cursor.getCol() + theInsert.size());
    } 
  }
  // move cursor left one col, if not at col 0
  cursor.setCol(std::max(0,cursor.getCol()-1));
  tab.setCursor(cursor);
}

