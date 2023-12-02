#ifndef MODE_ESC_NORMAL_H
#define MODE_ESC_NORMAL_H

#include "mode_manager.h"

// when `Esc` is pressed, switch modeManager to Normal mode
class EscNormal: public KeystrokeConsumer {
  ModeManager& modeManager;
 public: 
  EscNormal(ModeManager& manager): modeManager{manager} {}
  void consume(const Keystroke& keystroke) override{
    if (keystroke.key == Key::Esc) {
      modeManager.setMode(ModeType::Normal);
    }
  }
};
#endif
