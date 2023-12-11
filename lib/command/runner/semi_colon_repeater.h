#ifndef SEMI_COLON_REPEATER_H
#define SEMI_COLON_REPEATER_H

#include <memory>

#include "lib/command/runner/movement_runner.h"

// replays last f,F movement when movement parser gives a ';'
class SemiColonRepeater: 
  public CommandRunner<Movement>
{
  MovementRunner& movementRunner;
  std::unique_ptr<Movement> prevMovement;

 public:
  void run(const Movement* cmd) override; 
  SemiColonRepeater( MovementRunner& movementRunner): 
    movementRunner{movementRunner} {}
};


#endif

