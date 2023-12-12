#ifndef INIT_CURSOR_H
#define INIT_CURSOR_H

#include "init_windows.h"
#include "init_modes/init_modes.h"
#include "lib/cursor/nc_cursor.h"

struct CursorClosure {
  WindowsClosure& windowsClosure;
  ModesClosure& modesClosure;
  NCCursor ncCursor;

  // calculates the location of a cursor on the screen from the activeWindow
  void getActiveLocation (){
    const auto& tab = windowsClosure.activeWindow->getTabManager().curr();
    auto cursor = tab.getCursor();
    // calculate which row on the screen our cursor corresponds to
    auto printRow = tab.getRow();
    for (int i = tab.getTopLine(); i < cursor.getRow(); ++i){
      printRow += tab.lineSize(i);
    }
    printRow += cursor.getCol()/tab.getWidth();
    // calculate which column on screen is our cursor
    auto printCol = tab.getCol() + cursor.getCol()%tab.getWidth();
    ncCursor.translate(printRow, printCol);
  }

  CursorClosure(WindowsClosure& windowsClosure, ModesClosure& modesClosure): 
    windowsClosure{windowsClosure}, modesClosure{modesClosure} {}
  
  // sets location of the cursor based on whether we are Ex mode, or not
  void calculateLocation() {
    if (modesClosure.rootModeManager.getMode() == ModeType::Ex){
      ncCursor.translate(
        windowsClosure.rootStatusRender.getRow(), 
        modesClosure.exParser.getCol()+1
      );
    } else {
      getActiveLocation();
    } 
  }

  // calculate location and render
  void renderCursor(){ calculateLocation(); ncCursor.render(); }
};

#endif