#ifndef LINED_CHARBUF_H
#define LINED_CHARBUF_H

#include <cstddef> 
#include <string_view>
#include <string>
#include <ranges> 
#include <iterator>
#include <compare> 
#include <deque> 

// Manages an in-memory buffer to simplify line-based operations 
// template over type of the character to allow extension to e.g. Unicode
template<typename char_t> 
class LinedCharbuf {
  std::deque<std::basic_string<char_t>> lines; 
 public:
  class iterator: public std::bidirectional_iterator_tag {
    size_t line;
    size_t col; 
    // LinedCharbuf from which I was created
    LinedCharbuf* const theCharbuf=nullptr; 
   public: 
    size_t getLine() const noexcept {return line;}
    size_t getCol() const noexcept {return col;}
    iterator& operator++();
    iterator& operator++(int);
    iterator& operator--();
    iterator& operator--(int);
    auto operator<=>(const iterator& other) const =default;
    char_t operator*() const {return (*theCharbuf)[line][col];}
    char_t& operator*() {return *(*this);}
    friend class LinedCharbuf;
  };
  class const_iterator: public std::bidirectional_iterator_tag {
    size_t line;
    size_t col; 
    // LinedCharbuf from which I was created
    const LinedCharbuf* const theCharbuf=nullptr; 
   public: 
    size_t getLine() const noexcept {return line;}
    size_t getCol() const noexcept {return col;}
    const_iterator& operator++();
    const_iterator& operator--();
    auto operator<=>(const const_iterator& other) const =default;
    char_t operator*() const {return (*theCharbuf)[line][col];}
    friend class LinedCharbuf;
  };

  // erase `num` characters from line `line` starting at the `start` index (0 indexed)
  // - default start is 0, default num is npos (i.e. +infty)
  void erase(size_t line, size_t start=0, size_t num = std::string::npos);
  // insert all characters from `chars` into line `line` starting at index `start` (0 indexed) 
  void insert(size_t line, size_t start, std::basic_string<char_t> chars);
  // append all characters from `chars` into end of line `line` (0 indexed) 
  void append(size_t line, std::basic_string<char_t> chars);
  // insert `num` blank lines before line `line`
  void insert_lines(size_t line, size_t num);
  // erase `num` blank lines starting from `line`
  void erase_lines(size_t line, size_t num);

  // LinedFilebuf should be a bidirectional range over all characters in the file
  // LinedFilebuf should also return iterators starting from valid line,col positions
  iterator begin(size_t line = 0, size_t col = 0){return iterator{line,col,this};}
  iterator end(){return iterator{lines.size(),0,this};}
};

#endif