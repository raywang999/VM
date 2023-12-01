#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <vector>

#include "include/renderable_box.h"
#include "include/ncursespp.h"
#include "lib/tab/tabmanager.h"
#include "textstyler.h"
#include "stylemanager.h"

// renders a box of text in ncurses
// applies styles given by its attached textstylers 
class Textbox: public RenderableBox{
  // tabManager of the parent window. I need its currTab() for rendering
  const TabManager& tabManager;
  // the StyleManager `main` created from which I get styles to apply 
  const StyleManager& styleManager;
  // helper methods 
  void printEmptylineStart(int row, int col);
  void fillRestLine(int row, int col);
 public:
  Textbox(const TabManager& tabM, const StyleManager& styleM):
    tabManager{tabM}, styleManager{styleM} {}
  // print all characters from LinedFilbuf of the currently active tab
  // apply any styles 
  void render() override;
};

#endif
