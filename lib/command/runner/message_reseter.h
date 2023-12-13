#ifndef MESSAGE_RESETTER_H
#define MESSAGE_RESETTER_H


#include "lib/command/runner/normal_runner.h"
#include "lib/command/runner/movement_runner.h"
#include "lib/statusbar/root_status.h"

// listens to commands repeatable using . 
// replays the command when we receive a normal command with a '.' type
class MessageResetter: 
  public CommandRunner<SetMode>,
  public CommandRunner<Macro>,
  public CommandRunner<Normal>
{
  RootStatus& rootStatus;
  void clearMessage() {rootStatus.reset(); }
 public:
  MessageResetter(RootStatus& rootStatus): rootStatus{rootStatus} {}
  void run(const Macro*) override{clearMessage();}
  // reset when changing modes
  void run(const SetMode*) override{clearMessage();}
  // reset . 
  void run(const Normal* cmd) override{
    if (cmd->type == '.') clearMessage();
  }
};
#endif

