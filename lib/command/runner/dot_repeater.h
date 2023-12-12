#ifndef DOT_REPEATER_RUNNER_H
#define DOT_REPEATER_RUNNER_H

#include <memory>

#include "include/utility.h"
#include "lib/command/runner/insert_runner.h"
#include "lib/command/runner/macro_runner.h"
#include "lib/command/runner/comboNM_runner.h"
#include "lib/command/runner/normal_runner.h"
#include "lib/command/runner/setmode_runner.h"

// listens to commands repeatable using . 
// replays the command when we receive a normal command with a '.' type
class DotRepeater: 
  public CommandRunner<Normal>,
  public CommandRunner<SetMode>,
  public CommandRunner<Insert>,
  public CommandRunner<ComboNM>,
  public CommandRunner<Macro>,
  public CommandRunner<Replace>
{
  InsertRunner& insertRunner;
  NormalRunner& normalRunner;
  MacroRunner& macroRunner;
  SetModeRunner& setModeRunner;
  ComboNMRunner& comboNMRunner;
  Insert prevInsert;
  Normal prevNormal;
  ComboNM prevComboNM;
  std::unique_ptr<SetMode> prevSetMode;
  Macro prevMacro;
  enum class Type {Insert, Replace, Normal, Macro, ComboNM, None};
  Type type{Type::None};

 public:
  void run(const Normal* cmd) override; 
  void run(const Insert* cmd) override; 
  void run(const Macro* cmd) override; 
  void run(const Replace* cmd) override; 
  void run(const SetMode* cmd) override; 
  void run(const ComboNM* cmd) override; 
  DotRepeater(
    InsertRunner& insertRunner,
    NormalRunner& normalRunner,
    MacroRunner& macroRunner, 
    SetModeRunner& setModeRunner,
    ComboNMRunner& comboNMRunner
  ): 
    insertRunner{insertRunner},
    normalRunner{normalRunner},
    macroRunner{macroRunner},
    setModeRunner{setModeRunner},
    comboNMRunner{comboNMRunner}
  {}
};


#endif

