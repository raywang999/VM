#ifndef LOC_H
#define LOC_H

// line and column pair
struct Loc {
  int line, col;
  auto operator<=>(const Loc&) const = default;
};
#endif