#ifndef TAB_H
#define TAB_H

#include "include/utility.h"
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
  void doResize() override { fixCursor(); fitToCursor(); }
 public:
  // sets cursor to a valid normal-mode position 
  void fixCursor();
  // adjusts topLine to fit the cursor
  void fitToCursor();
  void fitToTopLine();
  Tab(LinedFilebuf<char>* filebuf): filebuf{filebuf} {}
  const LinedFilebuf<char>& getFilebuf() const noexcept {return *filebuf;}
  LinedFilebuf<char>& getFilebuf() noexcept {return *filebuf;}
  Cursor getCursor() const {return cursor;}
  // moves the cursor, moving topLine if required
  void setCursor(const Cursor& cursor) {this->cursor = cursor; }
  // moves the cursor, refitting the topLine if and only if fit == true
  void setCursor(const Cursor& cursor, bool fit) {
    this->cursor = cursor; 
    if (fit) fitToCursor(); 
  }
  // sets the topLine of the window pane, ignoring fit
  // fits input line to a valid line between 0 <= topLine < # of lines in filebuf
  size_t getTopLine() const noexcept { return topLine; }
  void setTopLine(int topLine, bool fitCursor = true) noexcept;
  
  // number of rendered lines this line takes up
  int lineSize(size_t line) const noexcept {
    return std::max(1,cielDiv(filebuf->getLine(line).size()-1, getWidth()));
  }
};
#endif

