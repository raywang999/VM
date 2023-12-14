#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <vector>

#include "include/renderable_box.h"
#include "include/ncursespp.h"
#include "lib/window/window.h"
#include "textstyler.h"
#include "stylemanager.h"

// renders a box of text in ncurses
// applies styles given by its attached textstylers 
class Textbox: public RenderableBox{
  // reference to the parent window. I need its currTab() for rendering
  Window& window;
  // the StyleManager `main` created from which I get styles to apply 
  const StyleManager& styleManager;
  // helper methods 
  void printEmptylineStart(int row, int col);
 public:
  Textbox(Window& window, const StyleManager& styleM):
    window{window}, styleManager{styleM} {}
  // print all characters from LinedFilbuf of the currently active tab
  // apply any styles 
  void render() override;
};

#endif
