#ifndef TAB_H
#define TAB_H

#include "include/resizeable.h"
#include "include/translateable.h"
#include "include/renderable.h"
#include "lib/buffer/lined_filebuf.h"
#include "lib/cursor/cursor.h"

// stores a filebuf, cursor, window pane that should be rendered together
class Tab: 
  virtual public Resizeable, 
  virtual public Translateable 
{ 
  LinedFilebuf<char>* filebuf;
  Cursor cursor;
  size_t topLine=0; // line representing top of the window pane
 public:
  Tab(LinedFilebuf<char>* filebuf): filebuf{filebuf} {}
  const LinedFilebuf<char>& getFilebuf() const noexcept {return *filebuf;}
  LinedFilebuf<char>& getFilebuf() noexcept {return *filebuf;}
  const Cursor& getCursor() const noexcept {return cursor;}
  Cursor& getCursor() noexcept {return cursor;}
  size_t getTopLine() const noexcept { return topLine; }
  void setTopLine(size_t topline) noexcept { topLine = topline; }
};

#endif

