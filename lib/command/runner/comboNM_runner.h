#ifndef COMBONM_RUNNER_H
#define COMBONM_RUNNER_H


#include "lib/command/runner/command_runner.h"
#include "lib/window/window.h"
#include "lib/command/runner/movement_runner.h"
#include "lib/command/runner/normal_runner.h"
#include "lib/statusbar/root_status.h"
#include "lib/matcher/matcher_runner.h"
#include "lib/command/runner/semi_colon_repeater.h"

// takes a basic Normal mode Command and runs it
class ComboNMRunner: public CommandRunner<ComboNM>{
  Window*& activeWindow;
  Clipboard& clipboard;
  RootStatus& rootStatus;

  // helper runners
  MovementRunner& movementRunner;
  SemiColonRepeater& semiRunner;
  MatcherRunner& matcherRunner;
  NormalRunner normalRunner{activeWindow, clipboard, rootStatus};

 public:
  // the command must be one of a,i,o,s,A,I,O,R,S
  void run(const ComboNM* cmd); 
  ComboNMRunner(
    Window*& activeWindow, 
    Clipboard& clipboard,
    RootStatus& rootStatus,
    MovementRunner& movementRunner,
    SemiColonRepeater& semiRunner,
    MatcherRunner& matcherRunner
  ): 
    activeWindow{activeWindow}, 
    clipboard{clipboard}, 
    rootStatus{rootStatus},
    movementRunner{movementRunner},
    semiRunner{semiRunner},
    matcherRunner{matcherRunner}
  {}
};

#endif

