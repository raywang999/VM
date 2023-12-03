#ifndef MACRO_RUNNER_H
#define MACRO_RUNNER_H

#include <vector>
#include "lib/command/runner/command_runner.h"
#include "lib/registers/macros.h"
#include "lib/window/window.h"
#include "lib/keystroke/keystroke_recorder.h"
#include "lib/mode/mode_manager.h"

// takes a basic Macro command and runs it 
// i.e. starts, endes recordings, and plays back macros
class MacroRunner: public CommandRunner<Macro>{
  MacrosRegister& reg;
  KeystrokeRecorder& recorder;
  ModeManager& modeManager;

  // null for not recording anything, otherwise should be a-zA-Z0-9
  char currReg = 0; 
 public:
  MacroRunner(MacrosRegister& reg, KeystrokeRecorder& recorder, ModeManager& modeManager): 
    reg{reg}, recorder{recorder}, modeManager{modeManager} {}
  void run(const Macro* macro) {
    if (macro->type == 'q'){
      if (currReg != 0) {  // finish recording
        reg[currReg] = recorder.getKeystrokes();
        recorder.reset();
      } else {
        // start recording 
        recorder.setActive(true);
        currReg = macro->reg;
      }
    } else {
      // replay the macro
      for (auto key: reg[macro->reg]){
        modeManager.consume(key);
      }
    }
  }
  char getCurrReg() const noexcept {return currReg; }
};

#endif

