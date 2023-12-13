#ifndef JK_RECORDER_H
#define JK_RECORDER_H

#include "lib/command/runner/movement_runner.h"
#include "lib/command/runner/command_runner.h"

// unset movementRunner's usePrevCol whenever the command is not jk
class JKRecorder: 
  public CommandRunner<Movement>,
  public CommandRunner<Command>
{
  MovementRunner& movementRunner;

 public:
  JKRecorder(MovementRunner& movementRunner): 
    movementRunner{movementRunner} {}
  void run(const Movement* cmd) override { 
    if (cmd->type != 'j' && cmd->type != 'k') {
      movementRunner.unsetPrev();
    }
  }
  void run(const Command*) override { 
    movementRunner.unsetPrev();
  }
};

#endif