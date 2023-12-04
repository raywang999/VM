#ifndef DOT_REPEATER_RUNNER_H
#define DOT_REPEATER_RUNNER_H


#include "include/utility.h"
#include "lib/command/runner/insert_runner.h"
#include "lib/command/runner/macro_runner.h"
#include "lib/command/runner/normal_runner.h"

// listens to commands repeatable using . 
// replays the command when we receive a normal command with a '.' type
class DotRepeater: 
  public CommandRunner<Normal>,
  public CommandRunner<Insert>,
  public CommandRunner<Macro>,
  public CommandRunner<Replace>
{
  InsertRunner& insertRunner;
  NormalRunner& normalRunner;
  MacroRunner& macroRunner;
  Insert prevInsert;
  Normal prevNormal;
  Macro prevMacro;
  enum class Type {Insert, Normal, Macro, None};
  Type type{Type::None};

 public:
  void run(const Normal* cmd) override; 
  void run(const Insert* cmd) override; 
  void run(const Macro* cmd) override; 
  void run(const Replace* cmd) override; 
  DotRepeater(
    InsertRunner& insertRunner,
    NormalRunner& normalRunner,
    MacroRunner& macroRunner
  ): 
    insertRunner{insertRunner},
    normalRunner{normalRunner},
    macroRunner{macroRunner}
  {}
};
inline void DotRepeater::run(const Insert* cmd){ 
  prevInsert = *cmd;
  type = Type::Insert;
}
inline void DotRepeater::run(const Macro* cmd){
  prevMacro = *cmd;
  type = Type::Macro;
}
inline void DotRepeater::run(const Replace* cmd){}

inline void DotRepeater::run(const Normal* cmd){
  if (cmd->type == '.'){
    // replay last command 
    if (type == Type::Macro){
      Macro tmp{normalizeCount(cmd->count, prevMacro.count), prevMacro.reg, '@'};
      macroRunner.run(&tmp);
    } else if (type == Type::Normal){
      Normal tmp{prevNormal};
      tmp.count = normalizeCount(cmd->count, prevNormal.count);
      normalRunner.run(&tmp);
    } else if (type == Type::Insert){
      Insert tmp{prevInsert};
      tmp.count = normalizeCount(cmd->count, prevInsert.count);
      if (tmp.mode == 'c') { // prev was a c_ command, use ComboNM runner

      }
      else if (tmp.mode != 'o' && tmp.mode != 'O'){
        // prev normal command was the one that brought us into insert mode, so replay it
        // unless it is o or O
        normalRunner.run(&prevNormal);
      }
      // then play the insert
      insertRunner.run(&tmp);
    }
  } else {
    // otherwise, record the command
    prevNormal = *cmd;
    type = Type::Normal;
  }
}

#endif

