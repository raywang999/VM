#ifndef MESSAGE_RESETTER_H
#define MESSAGE_RESETTER_H


#include "lib/command/runner/normal_runner.h"
#include "lib/command/runner/movement_runner.h"
#include "lib/statusbar/root_status.h"

// listens to commands repeatable using . 
// replays the command when we receive a normal command with a '.' type
class MessageResetter: 
  public CommandRunner<Normal>,
  public CommandRunner<Movement>, 
  public CommandRunner<Command>
{
  RootStatus& rootStatus;
  void clearMessage() {rootStatus.reset(); }
 public:
  MessageResetter(RootStatus& rootStatus): rootStatus{rootStatus} {}
  // don't reset if basic normal mode Command like x, dd
  void run(const Normal* cmd) override; 
  // don't reset
  void run(const Movement* cmd) override {}; 
  void run(const Command* cmd) override; 
};
inline void MessageResetter::run(const Normal* cmd){ 
  if (std::find({}, cmd->type))
}
#endif

