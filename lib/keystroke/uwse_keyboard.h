#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "keystroke.h"
#include "keystroke_source.h"

// UWSE = University of Waterloo Student Environment 
class UWSEKeyboard: public KeystrokeSource {
  int currInput;
 public:
  // converts currInput from ncurses keystroke into Keystroke
  Keystroke getState() const override; 
  void getNext() override;
};

#endif

