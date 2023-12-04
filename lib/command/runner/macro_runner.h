#ifndef MACRO_RUNNER_H
#define MACRO_RUNNER_H

#include <vector>
#include "lib/command/runner/command_runner.h"
#include "lib/command/command_recorder.h"
#include "lib/command/runner/sequence_runner.h"
#include "lib/registers/macros.h"
#include "lib/window/window.h"

// takes a basic Macro command and runs it 
// i.e. starts, endes recordings, and plays back macros
class MacroRunner: public CommandRunner<Macro>{
  SequenceRunner& sequenceRunner;
  MacrosRegister& reg;
  CommandRecorder& recorder;

  // null for not recording anything, otherwise should be a-zA-Z0-9
  char currReg = 0; 
 public:
  MacroRunner(SequenceRunner& sequenceRunner, MacrosRegister& reg, CommandRecorder& recorder): 
    sequenceRunner{sequenceRunner}, reg{reg}, recorder{recorder} {}
  void run(const Macro* macro) {
    if (macro->type == 'q'){
      if (currReg != 0) {  // finish recording
        reg[currReg] = std::move(*recorder.getCommand());
        recorder.reset();
        recorder.setActive(false);
      } else {
        // start recording 
        recorder.setActive(true);
        currReg = macro->reg;
      }
    } else {
      // replay the macro
      sequenceRunner.run(&reg[currReg]);
    }
  }
};

#endif

