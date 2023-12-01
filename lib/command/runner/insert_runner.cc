#include <string>

#include "insert_runner.h"

void InsertRunner::run(const Insert* insert){
  if (insert->count == 0) return; // do nothing for no count
  std::string theInsert;
  auto& tab = activeWindow->getTabManager().curr();
  auto& filebuf = tab.getFilebuf();
  auto& cursor = tab.getCursor();
  if (insert->mode == 'i'){  // play the inserts without newlines
    for (int i=0; i < insert->count; ++i) {
      theInsert += insert->sentence;
    }
    filebuf.insert(cursor.getRow(), cursor.getCol(), theInsert);
    cursor.setCol(cursor.getCol() + theInsert.size());
  } else {
    // otherwise, play inserts with newlines
    if (insert->mode == 'o'){
      cursor.setRow(cursor.getRow()+1);
    }
    filebuf.insertLines(cursor.getRow(),insert->count);
    for (int i=0; i < insert->count; ++i){
      filebuf.insert(cursor.getRow()+i, 0, theInsert);
    }
    cursor.translate(cursor.getRow()+insert->count-1, theInsert.size()-1);
  }
  activeWindow->render();
}

