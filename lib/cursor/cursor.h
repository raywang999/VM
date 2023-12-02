#ifndef CURSOR_H
#define CURSOR_H

#include "include/translateable.h"

class Cursor: public Translateable {
 public: 
  Cursor(int row=0, int col=0): Translateable(row,col) {}
  void setLine(int line) noexcept { setRow(line); }
  int getLine() const noexcept { return getRow(); }
};

#endif