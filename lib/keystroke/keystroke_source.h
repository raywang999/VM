#ifndef KEYSTROKE_SOURCE_H
#define KEYSTROKE_SOURCE_H

#include "lib/keystroke/keystroke.h"
#include "include/subject.h"

class KeystrokeSource: public Subject<Keystroke>{
 public: 
  // get the next keystroke 
  virtual void getNext() =0;
  // getState() will get the Current keystroke
};

#endif

