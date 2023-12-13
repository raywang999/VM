#ifndef AT_MACRO_RUNNER_H
#define AT_MACRO_RUNNER_H

#include "lib/command/runner/command_runner.h"
#include "lib/registers/macros.h"
#include "lib/window/window.h"
#include "lib/keystroke/keystroke_recorder.h"
#include "lib/mode/mode_manager.h"

// takes a basic Macro command and runs it 
// i.e. starts, endes recordings, and plays back macros
// note: should attach this once before and once after the normal-group resetter 
class AtRunner: public CommandRunner<Macro>{
  MacrosRegister& reg;
  ModeManager& modeManager;

  // store reg of @ until the parsers are all properly reset
  char currReg = 0; 
  int count; // store count as well 
 public:
  AtRunner(
    MacrosRegister& reg, 
    ModeManager& modeManager
  ): 
    reg{reg}, 
    modeManager{modeManager}
  {}
  void run(const Macro* macro) {
    if (macro->type == '@'){
      if (!currReg){ // wait for reset
        currReg = macro->reg; 
        count = normalizeCount(macro->count);
        return;
      }
      // replay the macro count times
      for (int i=0;i < count; ++i){
        for (auto key: reg[macro->reg]){
          modeManager.consume(key);
        }
      }
      count = currReg = 0; // unset reg
    }
  }
};

#endif

