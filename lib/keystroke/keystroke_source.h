#ifndef KEYSTROKE_SOURCE_H
#define KEYSTROKE_SOURCE_H

#include "lib/keystroke/keystroke.h"
#include "include/subject.h"

class KeystrokeSource: public Subject<Keystroke, KeystrokeSource> {
 public: 
  virtual Keystroke getKeystroke() const =0; 
  virtual ~KeystrokeSource(){}
};

#endif

