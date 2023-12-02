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
  // sets cursor to a valid normal-mode position 
  void fixCursor();
  // adjusts topLine to fit the cursor
  void fitToCursor();
  void fitToTopLine();
  void doResize() override { fixCursor(); fitToCursor(); }
 public:
  Tab(LinedFilebuf<char>* filebuf): filebuf{filebuf} {}
  const LinedFilebuf<char>& getFilebuf() const noexcept {return *filebuf;}
  LinedFilebuf<char>& getFilebuf() noexcept {return *filebuf;}
  Cursor getCursor() const {return cursor;}
  // moves the cursor, moving topLine if required
  void setCursor(const Cursor& cursor) {this->cursor = cursor; fitToCursor(); }
  // moves the cursor, refitting the topLine if and only if fit == true
  void setCursor(const Cursor& cursor, bool fit) {
    this->cursor = cursor; 
    if (fit) fitToCursor(); 
  }
  // sets the topLine of the window pane, ignoring fit
  size_t getTopLine() const noexcept { return topLine; }
  void setTopLine(size_t topline) noexcept { this->topLine = topLine; fitToTopLine(); }; 
  void setTopLine(size_t topline, bool fit) { 
    this->topLine = topLine; 
    if (fit) fitToTopLine(); 
  }
  // number of rendered lines this line takes up
  int lineSize(size_t line) const noexcept {
    return std::max(1,cielDiv(filebuf->getLine(line).size()-1, getWidth()));
  }
};

inline void Tab::fitToCursor() {
  this->cursor = cursor;
  // largest row s.t. cursor is visible with topLine = maxTop
  auto maxTop = cursor.getRow(); 
  // smallest row such that cursor is visible when rendered with topLine = minTop
  auto minTop = maxTop;
  // # of lines required to render the line of the cursor
  // +1 for beginning of next line
  int lineCnt = 0;
  while (minTop > 0 && lineCnt <= getHeight()){
    --minTop;
    lineCnt += lineSize(minTop);
  }
  if (lineCnt > getHeight()) {++minTop;}
  topLine = fit(minTop, maxTop, topLine);
}

inline void Tab::fitToTopLine(){
  // smallest row the cursor can be and still show up in the render
  auto minCursorRow = topLine;
  // largest row the cursor can be and still show up in the render
  auto maxCursorRow = topLine;
  int cntlines = 0;
  while (maxCursorRow < filebuf->countLines() && cntlines <= getHeight()){
    cntlines += lineSize(maxCursorRow);
    ++maxCursorRow;
  }
  --maxCursorRow;

  // set cursor to a valid row, and fix it 
  cursor.setRow(fit(minCursorRow, maxCursorRow, cursor.getRow()));
  fixCursor();
}

inline void Tab::fixCursor(){
  // ensure 0 <= newrow < # of lines in file
  int newrow = fit(0, filebuf->countLines()-1, cursor.getRow());
  // ensure 0 <= newcol < # of characters in the file
  const auto lineSize = filebuf->getLine(newrow).size();
  int newcol = fit(0, lineSize > 0 ? lineSize - 1 : 0, cursor.getCol());
  cursor.translate(newrow, newcol);
}

#endif

