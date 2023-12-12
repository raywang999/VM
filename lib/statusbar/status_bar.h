#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include <string>

#include "include/ncursespp.h"
#include "include/ncolors.h"
#include "include/renderable_box.h"
#include "lib/window/window.h"

// status bar on bottom of a window 
// comprises of 2 sentences on one row 
// - mid (slightly to the right) : shows cursor locatino 
// - right : shows window location in file (i.e. TOP, BOT, ALL)
class StatusBar: public RenderableBox{
  const Window& window; // parent window
  std::string mid, right;
 public:
  StatusBar(const Window& window): window{window} {}
  bool showerror = false;
  void render() override;
};

#endif