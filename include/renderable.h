#ifndef RENDERABLE_H
#define RENDERABLE_H

class Renderable{
 public: 
  virtual void render() =0;
  virtual ~Renderable(){}
};

#endif

