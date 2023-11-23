#ifndef KEYSTROKE_CONSUMER_H
#define KEYSTROKE_CONSUMER_H

#include "lib/keystroke/keystroke.h"
#include "include/observer.h"
#include "include/subject.h"

class KeystrokeConsumer: public Observer<Keystroke> {
  virtual void consume(const Keystroke& keystroke) =0;
 public: 
  void notify(const Subject<Keystroke>& source) override;
};

inline void KeystrokeConsumer::notify(const Subject<Keystroke>& source){
  consume(source.getState());
}

#endif

