#ifndef STYLE_MANAGER_H
#define STYLE_MANAGER_H

#include <unordered_map>
#include <vector>
#include <memory>
#include <string> 

#include "textstylergroup.h"

// manages which filebufs are associated with which `TextStyler`s
class StyleManager {
  using map_t = std::unordered_map<std::string, TextStylerGroup>;
  map_t filenameStyleMap;
 public: 
  const TextStylerGroup::range getStyles(
    const std::string& filename, Loc start, Loc num) const
  {
    if (filenameStyleMap.count(filename))
      return filenameStyleMap.at(filename).getStyles(start, num);
    // return empty range if file doesnt have any stylers
    return TextStylerGroup::range{{0,0},{0,0}};
  }
};

#endif
