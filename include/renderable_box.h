#ifndef RENDERABLE_BOX_H
#define RENDERABLE_BOX_H

#include "include/resizeable.h"
#include "include/translateable.h"
#include "include/renderable.h"

class RenderableBox: 
  virtual public Renderable, 
  virtual public Resizeable, 
  virtual public Translateable 
{ };

#endif

