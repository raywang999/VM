#ifndef UTILITY_H
#define UTILITY_H

inline int min(int a, size_t b){
  return a < static_cast<int>(b) ? a : b;
}

inline int fit(int l, auto r, auto i) {
  auto sl = static_cast<size_t>(l);
  auto sr = static_cast<size_t>(r);
  auto si = static_cast<size_t>(i);
  if (si > sr) return r;
  if (si < sl) return l;
  return i;
}

// cieling of i/d
inline int cielDiv(int i, int d){
  return (i+d-1)/d;
}

#endif