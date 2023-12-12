#ifndef ROOT_STATUS_RENDER_H
#define ROOT_STATUS_RENDER_H

#include "include/renderable_box.h"
#include "include/ncursespp.h"
#include "root_status.h"

// renders the root status message 
class RootStatusRender: public RenderableBox{
 public: 
  bool showerror = false;
  std::string content;
  void render() override { 
    // row and col to print the statusbar on
    const auto printRow = getRow();
    const auto printCol = getCol();
    // width of statusbar
    const auto width = getWidth();
    ncurses::clearLine(printRow, printCol, width);
    ncurses::print(printRow, printCol, content);
    if (showerror){  // highlight error 
      ncurses::setAttributes(printRow, printCol, width, 
      ncurses::attribute::Void, 
      ncurses::colorset::PairStatusError); 
    }
  }
};

#endif