#include "tab.h"

void Tab::fitToCursor() {
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

void Tab::fitToTopLine(){
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

void Tab::fixCursor(){
  // ensure 0 <= newrow < # of lines in file
  int newrow = fit(0, filebuf->countLines()-1, cursor.getRow());
  // ensure 0 <= newcol < # of characters in the file
  const auto lineSize = filebuf->getLine(newrow).size()-1;
  int newcol = fit(0, lineSize > 0 ? lineSize - 1 : 0, cursor.getCol());
  cursor.translate(newrow, newcol);
}
