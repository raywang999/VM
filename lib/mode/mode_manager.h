#ifndef MODE_MANAGER_H
#define MODE_MANAGER_H

#include <vector>
#include <unordered_map>

#include "mode.h"
#include "modetype.h"
#include "lib/command/runner/command_runner.h"
#include "lib/keystroke/keystroke_consumer.h"

// manages currently active `Mode`
class ModeManager: virtual public KeystrokeConsumer, virtual public CommandRunner {
  ModeType currentMode{ModeType::Normal};
  std::unordered_map<ModeType, Mode*> modeMap;
  // watch for `SwitchMode` commands
  void notify(const Subject<Command*>& ) override; 
 public: 
  // forward the keystroke to the currently active mode 
  // listens for this Mode's setMode commands
  void consume(const Keystroke& keystroke) override;
  void attach(ModeType modetype, Mode* mode){
    modeMap[modetype]=mode;
    mode->attach_runner(this);
  }
};

inline void ModeManager::notify(const Subject<Command*>&) {
  const SetMode mode = *modeMap[currentMode]->getCommand();
  currentMode = mode.mode;
}

inline void ModeManager::consume(const Keystroke& keystroke) {
  modeMap[currentMode]->consume(keystroke);
}

#endif
