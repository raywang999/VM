#ifndef KEYSTROKE_SOURCE_H
#define KEYSTROKE_SOURCE_H

#include "lib/keystroke/keystroke.h"
#include "include/subject.h"

class KeystrokeSource: private Subject<Keystroke, KeystrokeSource> {
 public: 
  // get the next keystroke. Don't notify  
  virtual void getNext() =0;
  virtual Keystroke getKeystroke() const =0; 
  using Subject<Keystroke, KeystrokeSource>::attach;
  void notifyAll(); 
  virtual ~KeystrokeSource(){}
};

#endif

