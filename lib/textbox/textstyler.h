#ifndef TEXT_STYLER_H
#define TEXT_STYLER_H

#include <vector>
#include <compare>

#include "include/loc.h"
#include "include/ncursespp.h"
#include "include/renderable_box.h"

struct Style{
  Loc first, last;
  ncurses::Attribute attribute;
  // use filedwise compare for ordering
  auto operator<=>(const Style& other) const = default;
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
  
  // returns a view of all styles applying to [beg, end]
  virtual std::unique_ptr<range_t> getStyles(Loc beg, Loc end) const =0;
  virtual ~TextStyler(){};
};

#endif
