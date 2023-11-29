#ifndef GENERAL_RUNNER_H
#define GENERAL_RUNNER_H

#include "lib/command/runner/normal_runner.h"
#include "lib/command/runner/insert_runner.h"
#include "lib/command/runner/movement_runner.h"

// runs a sequence of Commands using runners provided in construction
class GeneralRunner: CommandRunner<Command>{
  NormalRunner& normalRunner;
  InsertRunner& insertRunner;
  MovementRunner& movementRunner;
  
 public:
  void run(const Command* command) override {
    if (const Insert* insert = dynamic_cast<const Insert*>(command)){
      insertRunner.run(insert);
    } else if (const Normal* normal = dynamic_cast<const Normal*>(command)){
      normalRunner.run(normal);
    } else if (const Movement* movement = dynamic_cast<const Movement*>(command)){
      movementRunner.run(movement);
    }
  }
  GeneralRunner(
    NormalRunner& normalRunner, 
    InsertRunner& insertRunner, 
    MovementRunner& movementRunner
  ): 
    normalRunner{normalRunner}, 
    insertRunner{insertRunner}, 
    movementRunner{movementRunner} 
  {}
};

#endif

