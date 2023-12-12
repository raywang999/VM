#include "dot_repeater.h"
#include "include/utility.h"

void DotRepeater::run(const SetMode* cmd){ 
  prevSetMode = std::make_unique<SetMode>(*cmd);
}
void DotRepeater::run(const Insert* cmd){ 
  prevInsert = *cmd;
  type = Type::Insert;
}
void DotRepeater::run(const Macro* cmd){
  prevMacro = *cmd;
  type = Type::Macro;
}
void DotRepeater::run(const Replace* cmd){}

void DotRepeater::run(const Normal* cmd){
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
      // prev normal command was the one that brought us into insert mode, so replay it
      // unless it is o or O
      if (tmp.mode != 'o' && tmp.mode != 'O'){
        setModeRunner.run(prevSetMode.get());
      }
      // then play the insert
      insertRunner.run(&tmp);
    } else if (type == Type::ComboNM){
      ComboNM tmp = prevComboNM;
      tmp.normal.count *= normalizeCount(cmd->count);
      comboNMRunner.run(&prevComboNM);
    }
  } else {
    // otherwise, record the command if it should be repeatable
    if (cmd->type != 'u'){
      prevNormal = *cmd;
      type = Type::Normal;
    }
  }
}

void DotRepeater::run(const ComboNM* cmd){
  if (cmd->normal.type != 'y'){
    type = Type::ComboNM; 
    prevComboNM = *cmd;
  }
}
