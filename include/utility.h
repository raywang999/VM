#ifndef UTILITY_H
#define UTILITY_H

#include <unordered_set>
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

#endif