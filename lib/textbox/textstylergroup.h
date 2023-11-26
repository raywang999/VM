#ifndef TEXT_STYLER_GROUP_H
#define TEXT_STYLER_GROUP_H

#include <vector>
#include <memory> 
#include "textstyler.h"

// a collection TextStyler applied at once
class TextStylerGroup {
  using vector_t = std::vector<std::unique_ptr<TextStyler>>;
  vector_t textstyles;
 public: 
  class iterator {
    size_t start, num;
    // the textstyle ranges of the group used to generate this iterator
    // nullptr for end sentinel
    const vector_t* textstyles = nullptr;
    // current index in the textstyles
    size_t currind = 0; 
    // the range returned by textstyles[currind].getStyles():w
    std::unique_ptr<TextStyler::range_t> subrange;
    // the iterator into textstyles[currind]
    std::unique_ptr<TextStyler::iterator_t> subiter;
   public: 
    // create end sentinel
    iterator() = default;
    // create begin() using textsyles
    iterator(size_t start, size_t num, const vector_t* textstyles): 
      start{start}, num{num},
      textstyles{textstyles}, 
      subrange{(*textstyles)[0]->getStyles(start, num)},
      subiter{subrange->begin()} {}
    bool operator==(const iterator& other) const;
    const Style& operator*() const { return **subiter;}
    iterator& operator++();
  };
  class range {
    size_t start, num;
    const vector_t* textstyles;
   public: 
    range(size_t start, size_t num, const vector_t* ts):
      start{start}, num{num}, textstyles{ts} {} 
    iterator begin() const noexcept { return iterator{start, num, textstyles}; }
    iterator end() const noexcept {return iterator{};}
  };
  // joins all styles into one range
  const range getStyles(size_t start, size_t num) const { 
    return range{start, num, &textstyles};
  }
};


#endif
