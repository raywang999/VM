#ifndef UWSE_KEYBOARD_H
#define UWSE_KEYBOARD_H

#include "lib/keystroke/keystroke.h"
#include "lib/keystroke/keystroke_source.h"

// UWSE = University of Waterloo Student Environment 
class UWSEKeyboard: public KeystrokeSource {
  int currInput;
 public:
  // converts currInput from ncurses keystroke into Keystroke
  Keystroke getState() const override; 
  void getNext() override;
};

#endif

