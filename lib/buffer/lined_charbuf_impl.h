#include "lined_charbuf.h"

#include <cstddef> 
#include <string_view>
#include <string>
#include <ranges> 
#include <iterator>
#include <compare> 
#include <deque> 

template<typename char_t>
template<typename Iter> 
inline void LinedCharbuf<char_t>::inc_helper(Iter &iter) noexcept{
  auto& col = iter.col;
  auto& position = iter.position;
  auto& theCharbuf = iter.theCharbuf;
  auto& line = iter.line;
  ++col; ++position;
  if (col >= theCharbuf->lines[line].size()){
    ++line; col=0;
  }
}

template<typename char_t>
template<typename Iter> 
inline void LinedCharbuf<char_t>::dec_helper(Iter &iter) noexcept{
  auto& col = iter.col;
  auto& position = iter.position;
  auto& theCharbuf = iter.theCharbuf;
  auto& line = iter.line;
  if (col == 0){
    --line; col = theCharbuf->lines[line].size();
  }
  --col; --position;
}

template<typename char_t> 
inline typename LinedCharbuf<char_t>::iterator& LinedCharbuf<char_t>::iterator::operator++() noexcept{
  inc_helper(*this);
  return *this;
}

template<typename char_t> 
inline typename LinedCharbuf<char_t>::iterator& LinedCharbuf<char_t>::iterator::operator--() noexcept{
  dec_helper(*this);
  return *this;
}

template<typename char_t> 
inline typename LinedCharbuf<char_t>::const_iterator& 
LinedCharbuf<char_t>::const_iterator::operator++() noexcept{
  inc_helper(*this);
  return *this;
}

template<typename char_t> 
inline typename LinedCharbuf<char_t>::const_iterator& 
LinedCharbuf<char_t>::const_iterator::operator--() noexcept{
  dec_helper(*this);
  return *this;
}

template<typename char_t> 
// erase `num` characters from line `line` starting at the `start` index (0 indexed)
// - default start is 0, default num is npos (i.e. +infty)
// - erasing more than number of chars available does nothing
inline void LinedCharbuf<char_t>::erase(size_t line, size_t start, size_t num){
  auto& curline = lines[line];
  num = min(num, curline.size()-start-1);
  curline = curline.substr(0,start) + curline.substr(start+num);
}
// insert all characters from `chars` into line `line` starting at index `start` (0 indexed) 
template<typename char_t>
inline void LinedCharbuf<char_t>::insert(size_t line, size_t start, std::basic_string<char_t> chars){
  auto& curline = lines[line];
  curline = curline.substr(0, start) + chars + curline.substr(start);
}
// append all characters from `chars` into end of line `line` (0 indexed) 
template<typename char_t>
inline void LinedCharbuf<char_t>::append(size_t line, std::basic_string<char_t> chars){
  auto& curline = lines[line];
  curline.pop_back();
  curline += chars + "\n";
}
template<typename char_t>
inline void LinedCharbuf<char_t>::append(size_t line, char_t ch){
  auto& curline = lines[line];
  curline.pop_back();
  curline.push_back(ch);
  curline.push_back('\n');
}
// insert `num` blank lines before line `line`
template<typename char_t>
inline void LinedCharbuf<char_t>::insert_lines(size_t line, size_t num){
  lines.insert(lines.begin()+line, num, "\n");
}
// erase `num` blank lines starting from `line`
template<typename char_t>
inline void LinedCharbuf<char_t>::erase_lines(size_t line, size_t num){
  lines.erase(lines.begin()+line, lines.begin()+line+num);
}

template<typename char_t>
inline size_t LinedCharbuf<char_t>::getPosition(size_t line, size_t col) const noexcept {
  size_t res = 0;
  for (size_t i = 0; i < line; ++i){
    res += lines[i].size();
  }
  return res + col;
}
