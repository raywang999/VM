#ifndef SEQUENCE_RUNNER_H
#define SEQUENCE_RUNNER_H

#include "lib/command/runner/general_runner.h"

// runs a sequence of Commands using runners provided in construction
class SequenceRunner: CommandRunner<Sequence> {
  GeneralRunner& generalRunner;
  
 public:
  void run(const Sequence* sequence){ 
    for (auto command: sequence->theSequence){
      generalRunner.run(command);
    }
  }
  SequenceRunner( GeneralRunner& generalRunner): generalRunner{generalRunner} {}
};

#endif

