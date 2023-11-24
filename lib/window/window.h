#ifndef WINDOW_H
#define WINDOW_H

#include "include/renderable_box.h"
#include "include/resizeable.h"

enum class WindowType{
  VertSplit, HoriSplit, NoSplit
};

class Window: virtual public Resizeable {
  WindowType type = WindowType::NoSplit;
  // the parent window. nullptr if this is the root window
  Window *parent = nullptr;

};

#endif