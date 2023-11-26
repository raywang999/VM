#include "textbox.h"
#include "include/ncolors.h"
#include "include/ncursespp.h"

void printEmptylineStart(int row, int col){
  attron(ncurses::attribute::ColorPair(ncurses::colorset::PairLineStart));
  ncurses::print(row, col, '~');
  attroff(ncurses::attribute::ColorPair(ncurses::colorset::PairLineStart));
}

void Textbox::render() {
  const auto& currTab = tabManager.curr();
  const auto& currFilebuf = currTab.getFilebuf();
  const auto topLine = currTab.getTopLine();
  const auto height = getHeight();
  const auto width = getWidth();
  const auto botLine = topLine + height;
  auto iter = currFilebuf.begin(topLine,0);
  auto styles = styleManager.getStyles(
    currFilebuf.filename, iter.getPosition(), height*width);
  // top row of the area we should render to
  const auto anchorRow = getRow();
  // left col of the area we should render to 
  const auto anchorCol = getCol();
  for (int i = 0, j = 0; i < height;){
    const auto printRow = anchorRow + i;
    const auto printCol = anchorCol + j;
    if (iter == currFilebuf.end()){ // emptyline
      printEmptylineStart(printRow, anchorCol);
      ++i;
    } else {
      if (*iter == '\n'){
        ++iter; ++i; j=0;
      } else {
        ncurses::print(printRow, printCol, *iter);
        ++iter; ++j;
        if (j == width){
          j=0; ++i;
        }
      }
    }
  }
  // apply the styles
}

