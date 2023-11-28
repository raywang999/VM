#ifndef KEYSTROKE_CONSUMER_H
#define KEYSTROKE_CONSUMER_H

#include "lib/keystroke/keystroke.h"
#include "lib/keystroke/keystroke_source.h"
#include "include/observer.h"
#include "include/subject.h"

// KeystrokeConsumers really do listen for keystrokes from an abstract source of keystroke
// contrary to normal Observer, Subject pattern
class KeystrokeConsumer: public Observer<Keystroke>{
 public: 
  virtual void consume(const Keystroke& keystroke) =0;
  void notify(const Subject<Keystroke>& source){
    consume(static_cast<const KeystrokeSource&>(source).getKeystroke());
  }
};

#endif

