#ifndef CURSOR_H
#define CURSOR_H

#include "include/translateable.h"

class Cursor: public Translateable {
 public: 
  Cursor(): Translateable(0,0) {}
  void setLine(int line) noexcept { setRow(line); }
  int getLine() const noexcept { return getRow(); }
};

#endif