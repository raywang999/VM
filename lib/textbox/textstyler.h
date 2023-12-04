#ifndef TEXT_STYLER_H
#define TEXT_STYLER_H

#include <vector>

#include "include/ncursespp.h"
#include "include/renderable_box.h"

struct Style{
  size_t first, last;
  ncurses::Attribute attribute;
};

class TextStyler{
 public: 
  // the polymorphic "forward iterator" that subclasses will implement
  struct iterator_t{
    virtual iterator_t& operator++() =0;
    virtual bool operator==(const iterator_t&) const =0;
    bool operator!=(const iterator_t& other){return !(other == *this); }
    virtual const Style& operator*() const =0;
    virtual ~iterator_t(){}
  };

  // the polymorphic "forward range" that subclasses will implement
  struct range_t {
    virtual std::unique_ptr<iterator_t> begin() const =0;
    virtual std::unique_ptr<iterator_t> end() const =0;
    virtual ~range_t(){}
  };
  
  // returns a view of all styles applying to `num` characters starting from `start`
  virtual std::unique_ptr<range_t> getStyles(size_t start, size_t num) const =0;
  virtual ~TextStyler(){};
};

#endif
