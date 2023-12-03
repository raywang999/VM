#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include "include/resetable.h"
#include "lib/command/command_recorder.h"
#include "lib/command/runner/general_runner.h"

class HistoryManager: public Resetable {
  // the recorder we manage
  CommandRecorder& past;
  GeneralRunner& runner;
  // number of consecutive undos we have run 
  size_t undos=0;
  void doReset() {
    while (undos > 0){
      --undos;
      past.pop();
    }
  }
 public:
  HistoryManager(CommandRecorder& past, GeneralRunner& runner):
    past{past}, runner{runner} {}
  // undo most recent command 
  void undo() { 
    const auto& seq = past.getCommand()->theSequence;
    if (undos >= seq.size()) return; // do nothing if nothing to undo
    runner.run(seq[undos]);
  }
  // redo most recent command
  void redo() { 
    if (undos > 0 ) {
      --undos; 
      runner.run(past.getCommand()->theSequence[undos]);
    }
  }
};

#endif