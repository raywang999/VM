#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include <string>

#include "include/ncursespp.h"
#include "include/ncolors.h"
#include "include/renderable_box.h"

// status bar on bottom of a window 
// comprises of 3 sentences on one row 
// -left, mid (slightly to the right), right 
class StatusBar: public RenderableBox{
 public:
  std::string left, mid, right;
  bool showerror = false;
  void render() override;
};

#endif