
#include "window.h"

void Window::close() {
  if (parent){
    parent->closeChild(this);
  } 
}

void Window::closeChild(Window* child) {
  auto is_same = [child](const Window_p& other){return other.get() == child;};
  auto it = std::find_if(children.begin(), children.end(), is_same);
  if (it != children.end()){
    children.erase(it);
    if (children.size() == 1){
      // merge the single child into ourself 
      type = WindowType::NoSplit;
      tabManager = std::move(children[0]->tabManager);
      children.clear();
    }
  }
}

// first split = create 2 children. other splits = create 1 more child
void Window::split() {
  children.push_back(clone());
  if (type == WindowType::NoSplit) {
    children.push_back(clone());
  }
}
void Window::splitHori() {
  split();
  type = WindowType::HoriSplit;
}

void Window::splitVert() {
  split();
  type = WindowType::VertSplit;
}

Window::Window_p Window::clone() {
  auto res = doClone();
  res->parent = this;
  res->tabManager = tabManager;
  res->type = type;
  return res;
}
