#ifndef GENERAL_RUNNER_H
#define GENERAL_RUNNER_H

#include "lib/command/runner/sequence_runner.h"

// runs a sequence of Commands using runners provided in construction
class GeneralRunner: public CommandRunner<Command>{
  SingleRunner& singleRunner;
  SequenceRunner& sequenceRunner;
  
 public:
  void run(const Command* command) override {
    if (const Sequence* sequence = dynamic_cast<const Sequence*>(command)){
      sequenceRunner.run(sequence);
    } else {
      singleRunner.run(command);
    } 
  }
  GeneralRunner(
    SingleRunner& singleRunner, 
    SequenceRunner& sequenceRunner
  ): 
    singleRunner{singleRunner}, 
    sequenceRunner{sequenceRunner}
  {}
};

#endif

