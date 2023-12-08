#ifndef MODE_ESC_RESETTER_H
#define MODE_ESC_RESETTER_H

#include "mode_manager.h"

// when `Esc` is pressed, resets the attached parserGroup and enters Normal mode
class EscNormal: public KeystrokeConsumer {
  ModeManager& modeManager;
 public: 
  EscNormal(ModeManager& manager): 
    modeManager{manager}{}
  void consume(const Keystroke& keystroke) override{
    if (keystroke.key == Key::Esc) {
      modeManager.setMode(ModeType::Normal);
    }
  }
};
#endif
