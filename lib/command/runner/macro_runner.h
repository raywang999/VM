#ifndef MACRO_RUNNER_H
#define MACRO_RUNNER_H

#include "lib/command/runner/command_runner.h"
#include "lib/command/runner/parser_group.h"
#include "lib/command/parser/macro_parser.h"
#include "lib/registers/macros.h"
#include "lib/window/window.h"
#include "lib/keystroke/keystroke_recorder.h"
#include "lib/history/history_recorder.h"
#include "lib/mode/mode_manager.h"

// takes a basic Macro command and runs it 
// i.e. starts, endes recordings, and plays back macros
// note: should attach this once before and once after the normal-group resetter 
class MacroRunner: public CommandRunner<Macro>{
  MacrosRegister& reg;
  KeystrokeRecorder& recorder;
  ModeManager& modeManager;
  MacroParser& macroParser;
  ParserGroup& normalGroup;
  HistoryRecorder& macroRecorder; // recorder for us
  HistoryRecorder& otherRecorder; // recorder for other commands

  // null for not recording anything, otherwise should be a-zA-Z0-9
  char currReg = 0; 
 public:
  MacroRunner(
    MacrosRegister& reg, 
    KeystrokeRecorder& recorder, 
    ModeManager& modeManager,
    MacroParser& macroParser,
    ParserGroup& normalGroup,
    HistoryRecorder& macroRecorder, 
    HistoryRecorder& otherRecorder 
  ): 
    reg{reg}, 
    recorder{recorder}, 
    modeManager{modeManager}, 
    macroParser{macroParser},
    normalGroup{normalGroup},
    macroRecorder{macroRecorder},
    otherRecorder{otherRecorder}
  {}
  void run(const Macro* macro) {
    if (macro->type == 'q'){
      if (currReg != 0) {  // finish recording
        reg[currReg] = recorder.getKeystrokes();
        reg[currReg].pop_back(); // last keystroke was 'q' to stop recording
        recorder.reset();
        currReg = 0;
        macroParser.setIsRecording(false);
      } else {
        // start recording 
        recorder.setActive(true);
        macroParser.setIsRecording(true);
        currReg = macro->reg;
      }
    } else { // replay keystrokes
      // store the command info, then reset the normal group 
      currReg = macro->reg;
      auto count = normalizeCount(macro->count);

      normalGroup.reset();
      // activate and decativate recorders
      macroRecorder.setActive(true);
      otherRecorder.setActive(false);
      // replay the macro count times
      for (int i=0;i < count; ++i){
        for (auto key: reg[currReg]){
          modeManager.consume(key);
        }
      }
      macroRecorder.setActive(false);
      otherRecorder.setActive(true);
      currReg = 0;
    }
  }
  char getCurrReg() const noexcept {return currReg; }
};

#endif

