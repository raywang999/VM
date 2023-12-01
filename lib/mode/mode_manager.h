#ifndef MODE_MANAGER_H
#define MODE_MANAGER_H

#include <vector>
#include <unordered_map>

#include "mode.h"
#include "modetype.h"
#include "lib/command/runner/command_runner.h"
#include "lib/keystroke/keystroke_consumer.h"

// manages currently active `Mode`
class ModeManager: virtual public KeystrokeConsumer {
  ModeType currentMode{ModeType::Normal};
  std::unordered_map<ModeType, Mode*> modeMap;
 public: 
  ModeType getMode() const noexcept { return currentMode; }
  // forward the keystroke to the currently active mode 
  // listens for this Mode's setMode commands
  void consume(const Keystroke& keystroke) override;
  void attach(ModeType modetype, Mode* mode){
    modeMap[modetype]=mode;
  }
  void setMode(ModeType mode) noexcept {currentMode = mode;}
};

inline void ModeManager::consume(const Keystroke& keystroke) {
  modeMap[currentMode]->consume(keystroke);
}

#endif
