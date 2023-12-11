#include "semi_colon_repeater.h"

void SemiColonRepeater::run(const Movement* cmd){
  if (cmd->type == ';'){
    auto movement = prevMovement.get();
    movement->count = normalizeCount(cmd->count);
    movementRunner.run(movement);
  } else if (cmd->type == 'f' || cmd->type == 'F'){
    prevMovement = std::make_unique<Movement>(*cmd);
  }
}
