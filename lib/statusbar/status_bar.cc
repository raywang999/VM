#include "status_bar.h"
#include "include/ncursespp.h"
#include "include/ncolors.h"

void StatusBar::render(){
  ncurses::setAttributes(ncurses::attribute::ColorPair(ncurses::colorset::PairStatusBar));
  // row and col to print the statusbar on
  const auto printRow = getRow();
  const auto printCol = getCol();
  // width of statusbar
  const auto width = getWidth();
  const auto rightCol = printCol + width;

  // offset calculations for mid and right
  constexpr int rightOffset = 3; // 3 chars for TOP, BOT, ALL, __%
  
  // 4 digits for line, 1 comma, 4 for column, 4 spaces
  constexpr int midOffset = 4+1+4+4+rightOffset; 

  // print left
  ncurses::print(printRow, printCol, left);
  if (showerror){  // highlight error 
    ncurses::setAttributes(printRow, printCol, left.size(), 
    ncurses::attribute::Void, 
    ncurses::colorset::PairStatusError); 
  }
  
  // print middle
  ncurses::print(printRow, rightCol-midOffset, mid);

  // print right
  ncurses::print(printRow, rightCol-rightOffset, right);
}
