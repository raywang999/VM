#include <string>

#include "insert_runner.h"

void InsertRunner::run(const Insert* insert){
  std::string theInsert;
  for (int i=0; i < insert->count; ++i) {
    theInsert += insert->sentence;
  }
  auto& tab = activeWindow->getTabManager().curr();
  auto& filebuf = tab.getFilebuf();
  auto& cursor = tab.getCursor();
  filebuf.insert(cursor.getRow(), cursor.getCol(), theInsert);
  cursor.setCol(cursor.getCol() + theInsert.size());
  activeWindow->render();
}

