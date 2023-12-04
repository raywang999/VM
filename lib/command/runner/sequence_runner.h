#ifndef SEQUENCE_RUNNER_H
#define SEQUENCE_RUNNER_H

#include "lib/command/runner/single_runner.h"

// runs a sequence of Commands using SingleRunner provided in construction
class SequenceRunner: CommandRunner<Sequence> {
  SingleRunner& singleRunner;
  
 public:
  void run(const Sequence* sequence){ 
    for (const auto& command: sequence->theSequence){
      if (auto seq = dynamic_cast<const Sequence*>(sequence)){
        run(seq);
      } else {
        singleRunner.run(seq);
      }
    }
  }
  SequenceRunner(SingleRunner& singleRunner): singleRunner{singleRunner} {}
};

#endif

