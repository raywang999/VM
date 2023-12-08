#ifndef LINED_CHARBUF_H
#define LINED_CHARBUF_H

#include <cstddef> 
#include <string>
#include <compare> 
#include <deque> 

// Manages an in-memory buffer to simplify line-based operations 
// template over type of the character to allow extension to e.g. Unicode
template<typename char_t> 
class LinedCharbuf {
  std::deque<std::basic_string<char_t>> lines; 
  // helper functions for iterator implementations
  template<typename Iter> 
  static void inc_helper(Iter &it) noexcept;
  template<typename Iter> 
  static void dec_helper(Iter &it) noexcept;
 public:
  class iterator {
    size_t line;
    size_t col; 
    size_t position; // number of characaters from beginning of file
    // LinedCharbuf from which I was created
    LinedCharbuf* const theCharbuf=nullptr; 
    iterator(size_t line, size_t col, size_t position, LinedCharbuf* const cb):
      line{line}, col{col}, position{position}, theCharbuf{cb} {}
   public: 
    size_t getLine() const noexcept {return line;}
    size_t getCol() const noexcept {return col;}
    size_t getPosition() const noexcept {return position;}
    iterator& operator++() noexcept;
    iterator& operator--() noexcept;
    auto operator<=>(const iterator& other) const =default;
    char_t operator*() const {return theCharbuf->lines[line][col];}
    char_t& operator*() {return theCharbuf->lines[line][col];}
    friend class LinedCharbuf;
  };
  class const_iterator {
    size_t line;
    size_t col; 
    size_t position; // number of characaters from beginning of file
    // LinedCharbuf from which I was created
    const LinedCharbuf* const theCharbuf=nullptr; 
    const_iterator(size_t line, size_t col, size_t position, const LinedCharbuf* const cb):
      line{line}, col{col}, position{position}, theCharbuf{cb} {}
   public: 
    size_t getLine() const noexcept {return line;}
    size_t getCol() const noexcept {return col;}
    size_t getPosition() const noexcept {return position;}
    const_iterator& operator++() noexcept;
    const_iterator& operator--() noexcept;
    auto operator<=>(const const_iterator& other) const =default;
    char_t operator*() const {return theCharbuf->lines[line][col];}
    friend class LinedCharbuf;
  };

  LinedCharbuf() =default;

  // erase `num` characters from line `line` starting at the `start` index (0 indexed)
  // - default start is 0, default num is npos (i.e. +infty)
  // - erasing more than number of chars available does nothing
  void erase(size_t line, size_t start=0, size_t num = std::string::npos);
  // insert all characters from `chars` into line `line` starting at index `start` (0 indexed) 
  // - adds newlines wherever newline characters occur in chars
  void insert(size_t line, size_t start, std::basic_string<char_t> chars);
  void insert(size_t line, size_t start, char_t ch);
  // append all characters from `chars` into end of line `line` (0 indexed) 
  void append(size_t line, char_t ch);
  // insert `num` blank lines before line `line`
  void insertLines(size_t line, size_t num);
  // erase `num` blank lines starting from `line`
  void eraseLines(size_t line, size_t num);

  size_t countLines() const noexcept { return lines.size(); }
  size_t countBytes() const noexcept { 
    size_t res = 0;
    for (auto line: lines){ res += line.size(); }
    return res*sizeof(char_t);
  }
  const std::basic_string<char_t>& getLine(size_t line) const noexcept { return lines[line]; }

  size_t getPosition(size_t line, size_t num) const noexcept; 

  // LinedFilebuf should be a bidirectional range over all characters in the file
  // LinedFilebuf should also return iterators starting from valid line,col positions
  iterator begin(size_t line = 0, size_t col = 0){
    return iterator{line,col,getPosition(line,col),this};
  }
  iterator end(){return iterator{lines.size(),0,getPosition(lines.size(),0),this};}
  const_iterator begin(size_t line = 0, size_t col = 0) const {
    return const_iterator{line,col,getPosition(line, col),this};
  }
  const_iterator end() const {
    return const_iterator{lines.size(),0,getPosition(lines.size(),0),this};
  }
  virtual ~LinedCharbuf(){};
};

#include "lined_charbuf_impl.h"

#endif
