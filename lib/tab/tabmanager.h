#ifndef TAB_MANAGER_H
#define TAB_MANAGER_H

#include <vector>
#include <cstddef>

#include "include/ncursespp.h"
#include "include/renderable_box.h"
#include "lib/tab/tab.h"

class TabManager{
  std::vector<Tab> items;
 public: 
  // index of current item
  size_t ind=0;
  // return true iff succesfully set to next element
  bool next() noexcept {
    if (ind+1 >= items.size()) return false;
    ++ind; return true;
  }
  // return true iff there is a prev element
  bool prev() noexcept {
    if (ind == 0) return false;
    --ind; return true;
  }
  size_t size() const noexcept {return items.size(); }
  // precondition: items is non-empty
  Tab& curr() {return items[ind];}
  const Tab& curr() const {return items[ind];}

  // add a Tab to manage
  template<typename... Args>
  void emplace_back(Args&&... args){
    items.emplace_back(std::forward<Args>(args)...);
  }

  const std::vector<Tab>& getItems() const noexcept {return items;}
};

#endif
