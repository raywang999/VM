#ifndef WINDOW_H
#define WINDOW_H

#include "include/renderable_box.h"
#include "include/resizeable.h"
#include "lib/tab/tabmanager.h"

enum class WindowType{
  VertSplit, HoriSplit, NoSplit
};

class Window: public RenderableBox {
  WindowType type = WindowType::NoSplit;
  // the parent window. nullptr if this is the root window
  Window *parent = nullptr;
  TabManager tabManager;
 public: 
  Window(const TabManager& tabManager): tabManager{tabManager} {}
  Window(Window *parent): parent{parent} {}
  Window(Window *parent, const TabManager& tabManager): parent{parent}, tabManager{tabManager} {}
  TabManager& getTabManager() noexcept {return tabManager; }
  const TabManager& getTabManager() const noexcept {return tabManager; }
};

#endif