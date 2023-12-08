#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <memory>

#include "include/renderable_box.h"
#include "include/resizeable.h"
#include "lib/tab/tabmanager.h"

enum class WindowType{
  VertSplit, HoriSplit, NoSplit, Closed 
};

class Window: public RenderableBox {
 public:
  using Window_p  = std::unique_ptr<Window>;
 private:
  WindowType type = WindowType::NoSplit;
  // the parent window. nullptr if this is the root window owned by Main
  Window *parent = nullptr;
  TabManager tabManager;
  std::vector<Window_p> children;
  // split helper 
  void split();
  // close a child window.
  // if that unsplits the current window, reflect that in our state
  void closeChild(Window* child);
  // subclasses override this to correctly clone themselves
  virtual Window_p doClone() =0;
 public: 
  Window(const TabManager& tabManager): tabManager{tabManager} {}
  Window(Window *parent): parent{parent} {}
  Window(Window *parent, const TabManager& tabManager): parent{parent}, tabManager{tabManager} {}

  TabManager& getTabManager() noexcept {return tabManager; }
  const TabManager& getTabManager() const noexcept {return tabManager; }
  const std::vector<Window_p>& getChildren() noexcept {return children;};
  WindowType getType() const noexcept {return type;}
  // close the current window, and close ourself in our parent
  void close();
  // split screen vertically (i.e. Ctrl+W, V)
  // precondition: current window hasn't been split 
  void splitVert();
  // split screen vertically (i.e. Ctrl+W, S)
  // precondition: current window hasn't been split 
  void splitHori();
  // calls doClone, then ensures we 
  // - create a copy of TabManager, type, 
  // - set cloned parent to this
  Window_p clone(); 
};

#endif