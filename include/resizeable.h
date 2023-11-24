#ifndef RESIZEABLE_H
#define RESIZEABLE_H

class Resizeable{
  int height;
  int width; 
  // subclasses override this to control what happens when they resize
  virtual void doResize(){}
 public: 
  // set dimensions and call doResize()
  void resize(int newheight, int newwidth){ 
    height = newheight; width = newwidth;
    doResize();
  }
  int getHeight() const noexcept {return height;}
  int getWidth() const noexcept {return width;}
  virtual ~Resizeable(){}
};

#endif

