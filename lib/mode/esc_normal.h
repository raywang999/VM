#ifndef MODE_ESC_RESETTER_H
#define MODE_ESC_RESETTER_H

#include "include/resetable.h"
#include "mode_manager.h"

// when `Esc` is pressed, resets the attached parserGroup and enters Normal mode
class EscNormal: public KeystrokeConsumer {
  ModeManager& modeManager;
  ParserGroup& parserGroup;
 public: 
  EscNormal(ModeManager& manager, ParserGroup& parserGroup): 
    modeManager{manager}, parserGroup{parserGroup} {}
  void consume(const Keystroke& keystroke) override{
    if (keystroke.key == Key::Esc) {
      parserGroup.reset();
      modeManager.setMode(ModeType::Normal);
    }
  }
};
#endif
