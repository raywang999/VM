#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <cstddef>

// helper class to implement TabManager and FilebufManager
template<typename T> 
struct Manager{
  std::vector<T> items;
  // index of current item
  size_t ind=0;
  // return true iff there is a next element
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
};

#endif
