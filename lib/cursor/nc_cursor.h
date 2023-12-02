#ifndef NC_CURSOR_H
#define NC_CURSOR_H

#include "include/renderable.h"
#include "include/ncursespp.h"
#include "cursor.h"

class NCCursor: public Renderable, public Cursor {
 public: 
  void render() override {
    ncurses::moveCursor(getRow(), getCol());
  }
};

#endif