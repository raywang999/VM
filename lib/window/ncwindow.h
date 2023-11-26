#ifndef NCWINDOW_H
#define NCWINDOW_H

#include "window.h"
#include "lib/textbox/textbox.h"
#include "lib/statusbar/status_bar.h"

class NCWindow: public Window {
  Textbox textbox;
  StatusBar statusBar;
 public: 
  NCWindow(const TabManager& tabManager, const StyleManager& styleManager): 
    Window(tabManager), 
    textbox(getTabManager(), styleManager) 
  {}
  void render() override;
};

inline void NCWindow::render(){
  const auto height = getHeight();
  const auto width = getWidth();
  const auto row = getRow();
  const auto col = getCol();
  textbox.resize(height-1, width);
  textbox.translate(row,col);
  statusBar.resize(1, width);
  statusBar.translate(row+height-1,col);
  textbox.render(); statusBar.render();
  const auto& cursor = getTabManager().curr().getCursor();
  ncurses::moveCursor(cursor.getRow(), cursor.getCol());
}

#endif