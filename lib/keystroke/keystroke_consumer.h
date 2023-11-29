#ifndef KEYSTROKE_CONSUMER_H
#define KEYSTROKE_CONSUMER_H

#include "include/observer.h"
#include "keystroke_source.h"

// KeystrokeConsumers really do listen for keystrokes from an abstract source of keystroke
// contrary to normal Observer, Subject pattern
template<>
class Observer<KeystrokeSource>{
 public: 
  // consume the keystroke
  virtual void consume(const Keystroke& keystroke) =0;
  void notify(const KeystrokeSource& source){ consume(source.getKeystroke()); }
};

using KeystrokeConsumer = Observer<KeystrokeSource>;

#endif

