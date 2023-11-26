#ifndef TAB_MANAGER_H
#define TAB_MANAGER_H

#include <vector>
#include <cstddef>

#include "include/ncursespp.h"
#include "include/manager.h"
#include "include/renderable_box.h"
#include "lib/tab/tab.h"

class TabManager: private Manager<Tab>{
 public: 
  using Manager<Tab>::next;
  using Manager<Tab>::prev;
  using Manager<Tab>::size;
  // precondition: items is non-empty
  Tab& curr() {return items[ind];}
  const Tab& curr() const {return items[ind];}

  // add a Tab to manage
  template<typename... Args>
  void emplace_back(Args&&... args){
    Manager<Tab>::items.emplace_back(std::forward<Args>(args)...);
  }
};

#endif
