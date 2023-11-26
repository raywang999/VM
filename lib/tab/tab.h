#ifndef TAB_H
#define TAB_H

#include "include/resizeable.h"
#include "include/translateable.h"
#include "include/renderable.h"
#include "lib/buffer/lined_filebuf.h"

class Tab: 
  virtual public Resizeable, 
  virtual public Translateable 
{ 
  LinedFilebuf<char>& filebuf;
 public:
  Tab(LinedFilebuf<char>& filebuf): filebuf{filebuf} {}
  const LinedFilebuf<char>& getFilebuf() const noexcept {return filebuf;}
  LinedFilebuf<char>& getFilebuf() noexcept {return filebuf;}
  size_t getTopLine() const noexcept {
    // TODO
    return 0;
  }
};

#endif

