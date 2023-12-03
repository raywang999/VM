#ifndef EX_RUNNER_H
#define EX_RUNNER_H

#include "lib/command/runner/command_runner.h"

// clears the ExMode message when a subject notifies us
class ExClearer: public CommandRunner<Command>{
 public:
  void run(const Command*) override {};
  ExClearer(): {}
};

#endif

