#include "status_bar.h"
#include "include/ncursespp.h"
#include "include/ncolors.h"

void StatusBar::render(){
  // calculate mid message for cursor 
  const auto& tab = window.getTabManager().curr();
  const auto& filebuf = tab.getFilebuf();
  auto cursor = tab.getCursor();
  mid = std::to_string(cursor.getRow()+1) + ",";
  if (filebuf.getLine(cursor.getRow()).size() == 1){
    mid += "0-1";
  } else {
    mid += std::to_string(cursor.getCol()+1);
  }

  // row and col to print the statusbar on
  const auto printRow = getRow();
  const auto printCol = getCol();
  // width of statusbar
  const auto width = getWidth();
  ncurses::clearLine(printRow, printCol, width);

  // rightmost Column
  const auto rightCol = printCol + width;

  // offset calculations for mid and right
  constexpr int rightOffset = 3; // 3 chars for TOP, BOT, ALL, __%
  
  // 5 digits for line, 1 comma, 4 for column, 4 spaces
  constexpr int midOffset = 5+1+4+4+rightOffset; 

  // print middle
  ncurses::print(printRow, rightCol-midOffset, mid);

  // print right
  ncurses::print(printRow, rightCol-rightOffset, right);
}
