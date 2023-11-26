#include "textstylergroup.h"

using iterator = TextStylerGroup::iterator;

bool iterator::operator==(const iterator& other) const {
  if (!other.textstyles){
    // other is end() sentinel
    return !textstyles || currind >= textstyles->size();
  }
  if (!textstyles) return false;
  return textstyles == other.textstyles && *subiter == *other.subiter;
}

iterator& iterator::operator++(){
  if (++(*subiter) == *subrange->end()){
    ++currind;
    if (currind < textstyles->size()){
      subrange = (*textstyles)[currind]->getStyles(start, num);
      subiter = subrange->begin();
    }
  }
  return *this;
};
