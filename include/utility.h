#ifndef UTILITY_H
#define UTILITY_H

#include <compare>
#include <string>
#include <cstddef>

inline int min(int a, size_t b){
  return a < static_cast<int>(b) ? a : b;
}

inline int fit(auto l, auto r, auto i) {
  auto sl = static_cast<int>(l);
  auto sr = static_cast<int>(r);
  auto si = static_cast<int>(i);
  if (si > sr) return r;
  if (si < sl) return l;
  return i;
}

// cieling of i/d
inline int cielDiv(int i, int d){
  return (i+d-1)/d;
}

// returns default if prev == -1, prev otherwise
inline int normalizeCount(int prev, int def = 1){
  return prev == -1 ? def : prev;
}

template<typename Iter, typename Pred> 
// finds the nth occurrence of an element s.t. p == element
inline Iter findNth(size_t n, Iter beg, Iter end, Pred&& p) {
  for (size_t i = 0; i < n && beg != end; ){
    if (p == *beg) {
      ++i;
      if (i >= n) return beg;
      ++beg; 
    } else {
      ++beg; 
    }
  }
  return end;
}

// appends s to unit if abs(count) != 1
inline std::string pluralize(int count, const std::string& unit){
  std::string res = std::to_string(count);
  res.push_back(' ');
  res.append(unit); 
  if (count != 1 && count != -1) res.push_back('s');
  return res;
}

#endif