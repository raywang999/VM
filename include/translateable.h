#ifndef TRANSLATEABLE_H
#define TRANSLATEABLE_H

#include "loc.h"

class Translateable{
  // anchor point is the top left corner of the object
  int toprow; // row of the anchor point
  int leftcol; // col of the anchor point
 public: 
  Translateable(int row=0, int col=0): toprow{row}, leftcol{col} {}
  void translate(int newrow, int newcol) noexcept { toprow = newrow; leftcol = newcol; }
  void setRow(int newrow) noexcept { toprow = newrow; }
  void setCol(int newcol) noexcept { leftcol = newcol; }
  int getRow() const noexcept {return toprow; }
  int getCol() const noexcept {return leftcol; }
  Loc getLoc() const {return Loc{toprow, leftcol};}
  virtual ~Translateable(){}
};

#endif

